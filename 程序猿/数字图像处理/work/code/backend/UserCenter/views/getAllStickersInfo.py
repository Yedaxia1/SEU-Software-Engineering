# -*- coding: utf-8 -*-
import json

from django.core import serializers
from django.http import HttpResponse
from django.utils.decorators import method_decorator
from UserCenter.models.UserModel import QiaoQianUser
from UserCenter.models.UserAlbum import QiaoQianAlbum
from UserCenter.models.UserStickers import QiaoQianStickers
from django.shortcuts import HttpResponse
from django.http import HttpRequest
from django.views.decorators.csrf import csrf_exempt
from django.views import View


@method_decorator(csrf_exempt, name='dispatch')
class getAllStickersInfo(View):
    def post(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")

    def get(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,            # 0 表示成功  1006 表述数据库连接错误
            'StickersNum': 0,
            'StickersInfo': []
        }
        # 获取user_id
        user_id = request.GET.get('user_id')

        try:
            # 查询结果JSON格式化
            QuerySet = QiaoQianStickers.objects.filter(user=QiaoQianUser.objects.get(id=user_id))

            msg['error_code'] = 0
            msg['StickersNum'] = QuerySet.count()

            # 加入贴纸信息
            for sticker in QuerySet:
                size = ''
                if sticker.sticker_size / 1024 / 1024 > 1:
                    size = '%.1fMB' % (sticker.sticker_size / 1024 / 1024)
                else:
                    size = '%.1fKB' % (sticker.sticker_size / 1024)
                data = {
                    'id': sticker.id,
                    'name': sticker.sticker_name,
                    'date': sticker.create_date.strftime('%Y-%m-%d'),  # date格式化，才能进行json序列化
                    'size': size,
                    'url': 'http://' + request.get_host() + '/media/' + str(sticker.sticker_img)
                }
                msg['StickersInfo'].insert(0, data)

            # 返回结果
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
