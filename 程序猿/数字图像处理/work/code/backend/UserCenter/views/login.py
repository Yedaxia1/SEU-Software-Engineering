# -*- coding: utf-8 -*-
import json

from django.http import HttpResponse
from django.utils.decorators import method_decorator
from UserCenter.models.UserModel import QiaoQianUser
from django.shortcuts import HttpResponse
from django.http import HttpRequest
from django.views.decorators.csrf import csrf_exempt
from django.views import View


@method_decorator(csrf_exempt, name='dispatch')

class login_view(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1001,  # (0 表示成功 1001表示邮箱不存在 1002表示密码错误 1006 表示数据库连接错误)
            'user_data': {
                'user_name': "xxx",
                'id': "xxx",
                'user_mail': "xxx@xxx.xxx",
                'user_avatar_url': "xxx"
            }
        }
        # 获取表单数据
        mail = request.POST.get('user_mail')
        password = request.POST.get('user_password')
        # 查询用户信息
        try:
            isExist = QiaoQianUser.objects.filter(user_mail=mail).count()
            if isExist == 0:
                msg['error_code'] = 1001
                return HttpResponse(json.dumps(msg, ensure_ascii=False))
        except Exception as e:
            print(e.args)
            msg['error_code'] = 1006
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        # 密码判断
        user = QiaoQianUser.objects.get(user_mail=mail)
        if user.user_password == password:  # 密码正确
            msg['error_code'] = 0
            msg['user_data'] = {
                'user_name': user.user_name,
                'id': user.id,
                'user_mail': user.user_mail,
                'user_avatar_url': 'http://' + request.get_host() + '/media/' + str(user.user_avatar)
            }
        else:  # 密码错误
            msg['error_code'] = 1002
        return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        return HttpResponse("请求方法出现错误！！")


