from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
import json
from UserCenter.models import QiaoQianUser
from django.views import View
from django.http import HttpResponse

@method_decorator(csrf_exempt, name='dispatch')
class change_password(View):
    def post(self, request, *args, **kwargs):
        user_id = request.POST.get('user_id')
        old_password = request.POST.get('old_password')
        new_password = request.POST.get('new_password')
        msg = {}
        try:
            user = QiaoQianUser.objects.get(id=user_id)
            if old_password == user.user_password:
                user.user_password = new_password
                user.save()
                msg['error_code'] = 0
            else:
                msg['error_code'] = 1002
            return HttpResponse(json.dumps(msg), content_type='application/json')
        except Exception as e:
            print(e.args)
            msg['error_code'] = 1006
            return HttpResponse(json.dumps(msg), content_type='application/json')

