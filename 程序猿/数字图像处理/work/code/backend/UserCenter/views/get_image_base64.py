from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
from django.views import View
from UserCenter.models import QiaoQianImages
from django.conf import settings
from django.http import HttpResponse
import json
import base64

class get_image_base64(View):
    def get(self, request, *args, **kwargs):
        msg = {
            'error_code': 1006,
            'image': ''
        }
        try:
            image_id = request.GET.get('image_id')
            img = QiaoQianImages.objects.get(id=image_id)
            suffix = str(img.image).split('.')[1]
            print('{0}/{1}'.format(settings.MEDIA_ROOT, str(img.image)))
            with open('{0}/{1}'.format(settings.MEDIA_ROOT, str(img.image)), 'rb') as f:
                b64_data = base64.b64encode(f.read())
                b64_data = 'data:image/{0};base64,'.format(suffix) + str(b64_data, 'utf8')
                msg['error_code'] = 0
                msg['image'] = b64_data
                f.close()
            return HttpResponse(json.dumps(msg), content_type='application/json')
        except Exception as e:
            print(e.args)
            msg['error_code'] = 1006
            return HttpResponse(json.dumps(msg), content_type='application/json')
