# -*- coding: utf-8 -*-
import json

from django.core import serializers
from django.http import HttpResponse
from django.utils.decorators import method_decorator
from UserCenter.models.UserModel import QiaoQianUser
from UserCenter.models.UserAlbum import QiaoQianAlbum
from UserCenter.models.UserImage import QiaoQianImages
from django.shortcuts import HttpResponse
from django.http import HttpRequest
from django.views.decorators.csrf import csrf_exempt
from django.views import View


@method_decorator(csrf_exempt, name='dispatch')
class getAllImagesInfo(View):
    def post(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")

    def get(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,            # 0 表示成功  1006 表述数据库连接错误
            'ImagesNum': 0,
            'ImagesInfo': []
        }
        # 获取user_id, album_id
        user_id = request.GET.get('user_id')
        album_id = request.GET.get('album_id')

        try:

            QuerySet = QiaoQianImages.objects.filter(
                    album=QiaoQianAlbum.objects.get(
                        id=album_id,
                        user=QiaoQianUser.objects.get(id=user_id)
                    )
                )

            msg['error_code'] = 0
            msg['ImagesNum'] = QuerySet.count()

            # 加入图片信息
            for image in QuerySet:
                size = ''
                if image.image_size / 1024 / 1024 > 1:
                    size = '%.1fMB' % (image.image_size / 1024 / 1024)
                else:
                    size = '%.1fKB' % (image.image_size / 1024)
                data = {
                    'id': image.id,
                    'name': image.image_name,
                    'date': image.image_date.strftime('%Y-%m-%d'),  # date格式化，才能进行json序列化
                    'size': size,
                    'url': 'http://' + request.get_host() + '/media/' + str(image.image)
                }
                msg['ImagesInfo'].insert(0, data)

            # 返回数据
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
