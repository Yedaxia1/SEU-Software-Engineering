# -*- coding: utf-8 -*-
import json
import os
from django.conf import settings
from django.utils.decorators import method_decorator
from django.shortcuts import HttpResponse
from django.views.decorators.csrf import csrf_exempt
from UserCenter.models.UserModel import QiaoQianUser
from UserCenter.models.UserAlbum import QiaoQianAlbum
from django.views import View
from UserCenter.utils import del_file


@method_decorator(csrf_exempt, name='dispatch')
class delete_album(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,      # (0 表示成功 1006 表示数据库连接错误)
        }
        # 读取表单数据
        user_id = request.POST.get('user_id')
        album_name = request.POST.get('album_name')

        try:
            isExist = QiaoQianAlbum.objects.filter(
                user=QiaoQianUser.objects.get(id=user_id),
                album_name=album_name).count()
            if isExist == 1:
                try:
                    del_album = QiaoQianAlbum.objects.get(
                        user=QiaoQianUser.objects.get(id=user_id),
                        album_name=album_name)
                    album_id = del_album.id
                    size = del_album.album_size
                    # 删除相册记录
                    del_album.delete()
                    if size != 0:
                        path = os.path.join(settings.MEDIA_ROOT,
                                            'user_{0}/pictures/album_{1}'.format(user_id, album_id))
                        del_file(path)
                        print(path)
                except Exception as e:
                    print(e.args)
                    msg['error_code'] = 1006
                    return HttpResponse(json.dumps(msg, ensure_ascii=False))
                msg['error_code'] = 0
                return HttpResponse(json.dumps(msg, ensure_ascii=False))
            else:
                return HttpResponse("相册已不存在！！")
        except Exception as e:
            print(e.args)
            msg['error_code'] = 1006
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")
