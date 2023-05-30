from django.core.handlers.wsgi import WSGIRequest
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
from UserCenter.models import QiaoQianUser
from django.views import View
from django.core.cache import cache
from django.http import HttpResponse
import json
from django.conf import settings
from django.core.mail import EmailMultiAlternatives
from UserCenter.utils import get_verify_code



@method_decorator(csrf_exempt, name='dispatch')
class register_view(View):
    default_avatar_url = 'default/default_avatar.png'
    # get verify code via e-mail
    def get(self, request: WSGIRequest, *args, **kwargs):
        print('get verify code start!')
        mail = request.GET.get('user_mail')

        print('user email:{}'.format(mail))
        isRegister = QiaoQianUser.objects.filter(user_mail=mail).count()
        res = {}
        if isRegister == 1:
            res = {'error_code': 1004}
        else:
            from_email = settings.EMAIL_HOST_USER
            verify_code = get_verify_code(5)
            print('verify code:{}'.format(verify_code))
            content = '<h1>欢迎使用巧倩美颜！</h1><p>您的验证码是{}，五分钟内有效，请您尽快填写。</p>'.format(verify_code)
            address = [mail]
            msg = EmailMultiAlternatives('巧倩美颜用户注册', content, from_email, address)
            msg.content_subtype = 'html'
            try:
                cache.set(mail, verify_code, 300)
                print('verify code{0}'.format(verify_code))
                msg.send(fail_silently=False)
                res = {'error_code': 0}
            except Exception as e:
                print(e.args)
                res = {'error_code': 1005}
        return HttpResponse(json.dumps(res), content_type='application/json')

    def post(self, request: WSGIRequest, *args, **kwargs):
        user_mail = request.POST.get('user_mail')
        verify_code = request.POST.get('verify_code')
        user_name = request.POST.get('user_name')
        user_password = request.POST.get('user_password')
        correct_verify_code = cache.get(user_mail)
        print('user email:{}'.format(user_mail))
        print('correct verify code {}'.format(correct_verify_code))
        res = {}
        if correct_verify_code is None:
            res = {'error_code': 1007}
            return HttpResponse(json.dumps(res), content_type='application/json')
        if verify_code == correct_verify_code:
            print("验证码正确")
            new_user = QiaoQianUser(user_name=user_name, user_mail=user_mail,
                                    user_password=user_password,
                                    user_avatar=self.default_avatar_url)
            try:
                new_user.save()
                res = {'error_code': 0}
            except Exception as e:
                print(e.args)
                res = {'error_code': 1006}
        else:
            res = {'error_code': 1003}
        return HttpResponse(json.dumps(res), content_type='application/json')

