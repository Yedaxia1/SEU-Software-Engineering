from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
import json
from UserCenter.models import QiaoQianUser
from django.views import View
from django.http import HttpResponse
from django.conf import settings
import os

@method_decorator(csrf_exempt, name='dispatch')
class ChangeUserAvatarView(View):
    def post(self, request, *args, **kwargs):
        user_id = request.POST.get('user_id')
        # TODO: test
        print(type(request.FILES))
        avatar = request.FILES.get('new_avatar')
        print(avatar.name)
        print(avatar.size)
        print(avatar)
        res = {}
        try:
            u = QiaoQianUser.objects.get(id = user_id)
            if str(u.user_avatar) != 'default/default_avatar.png':
                pth = str(u.user_avatar)
                os.remove('{0}/{1}'.format(settings.MEDIA_ROOT, pth))
        except Exception as e:
            print(e)
            res = {"error_code": 1006}
            return HttpResponse(json.dumps(res), content_type='application/json')
        u.user_avatar = avatar
        try:
            u.save()
            res = {'error_code': 0, "user_new_data": { "user_new_avatar_url": 'http://' + request.get_host() + '/media/' + str(u.user_avatar)}}
        except Exception as e:
            print(e)
            res = {"error_code": 1006}
            return HttpResponse(json.dumps(res), content_type='application/json')
        return HttpResponse(json.dumps(res), content_type='application/json')