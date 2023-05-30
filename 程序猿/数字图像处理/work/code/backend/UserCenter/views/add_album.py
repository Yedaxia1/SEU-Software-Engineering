# -*- coding: utf-8 -*-
import json
from django.utils.decorators import method_decorator
from django.shortcuts import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from UserCenter.models.UserModel import QiaoQianUser
from UserCenter.models.UserAlbum import QiaoQianAlbum
from django.views import View

# 前后端测试通过
@method_decorator(csrf_exempt, name='dispatch')
class add_album(View):
    default_cover_url = 'default/default_albumCover.png'

    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,      # (0 表示成功 1006 表示数据库连接错误)
            'album_info': {
                'id': 0,
                'name': "xxx",
                'date': "yy-mm-dd",
                'size': 0,
                'url': "xxx"
            }
        }
        # 读取表单数据
        user_id = request.POST.get('user_id')
        album_name = request.POST.get('album_name')

        try:
            isExist = QiaoQianAlbum.objects.filter(
                user=QiaoQianUser.objects.get(id=user_id),
                album_name=album_name).count()
            if isExist == 0:
                # 建立新的数据库记录
                new_album = QiaoQianAlbum(
                    album_name=album_name,
                    album_size=0,
                    cover_url=self.default_cover_url,
                    user=QiaoQianUser.objects.get(id=user_id)
                )
                # 新增记录
                new_album.save()
                msg['error_code'] = 0
                msg['album_info'] = {
                    'id': new_album.id,
                    'name': new_album.album_name,
                    'date': new_album.create_date.strftime('%Y-%m-%d'),
                    'size': 0,
                    'url': 'http://' + request.get_host() + '/media/' + new_album.cover_url
                }
                return HttpResponse(json.dumps(msg, ensure_ascii=False))
            else:
                return HttpResponse("用户id错误 or 相册重名，前端请检查！！")
        except Exception as e:
            print(e.args)
            msg['error_code'] = 1006
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")
