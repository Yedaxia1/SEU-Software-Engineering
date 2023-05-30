# -*- coding: utf-8 -*-
import json

from django.core import serializers
from django.http import HttpResponse
from django.utils.decorators import method_decorator
from UserCenter.models.UserModel import QiaoQianUser
from UserCenter.models.UserAlbum import QiaoQianAlbum
from django.shortcuts import HttpResponse
from django.http import HttpRequest
from django.views.decorators.csrf import csrf_exempt
from django.views import View


@method_decorator(csrf_exempt, name='dispatch')
class getAllAlbumsInfo(View):
    def post(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")

    def get(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,            # 0 表示成功  1006 表述数据库连接错误
            'AlbumsNum': 0,
            'AlbumsInfo': []
        }
        # 获取user_id
        user_id = request.GET.get('user_id')

        try:
            # 查询用户相册
            QuerySet = QiaoQianAlbum.objects.filter(user=QiaoQianUser.objects.get(id=user_id))

            msg['error_code'] = 0
            msg['AlbumsNum'] = QuerySet.count()

            # 加入相册信息
            for album in QuerySet:
                data = {
                    'id': album.id,
                    'name': album.album_name,
                    'date': album.create_date.strftime('%Y-%m-%d'),                # date格式化，才能进行json序列化
                    'size': album.album_size,
                    'url': 'http://' + request.get_host() + '/media/' + album.cover_url
                }
                msg['AlbumsInfo'].insert(0, data)

            # 返回结果
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
