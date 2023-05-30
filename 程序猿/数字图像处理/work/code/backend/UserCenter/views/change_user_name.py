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

class change_user_name_view(View):
    def post(self, request, *args, **kwargs):
        # 定义数据返回格式
        msg = {
            'error_code': 1006,       # 0表示成功，1006表示失败（未知错误，可能由于数据库）
            'user_new_data': {
                'user_new_name': "xxx"
            }
        }
        # 获取数据
        user_id = request.POST.get('user_id')
        new_name = request.POST.get('user_new_name')

        try:
            # 验证是否存在该用户
            isValid = QiaoQianUser.objects.filter(id=user_id).count()
            if isValid == 1:
                # 更新用户信息
                QiaoQianUser.objects.filter(id=user_id).update(user_name=new_name)
                msg['error_code'] = 0
                msg['user_new_data'] = {
                    'user_new_name': new_name
                }
                return HttpResponse(json.dumps(msg, ensure_ascii=False))
            else:
                # user_id不存在
                return HttpResponse(json.dumps({'error_code':1006}), content_type='application/json')
        except Exception as e:
            # 数据库连接出现错误
            print(e.args)
            msg['error_code'] = 1006
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        return HttpResponse("请求方法出现错误！！")


