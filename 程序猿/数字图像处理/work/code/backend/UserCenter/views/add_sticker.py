from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
import json
from UserCenter.models import QiaoQianUser
from UserCenter.models import QiaoQianAlbum
from UserCenter.models import QiaoQianImages
from UserCenter.models import QiaoQianStickers
from django.views import View
from django.http import HttpResponse

@method_decorator(csrf_exempt, name='dispatch')
class add_sticker(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,
            'stickerInfo': {}
        }

        # 读取请求信息
        user_id = request.POST.get('user_id')
        sticker = request.FILES.get('image')
        sticker_name = sticker.name
        sticker_size = sticker.size

        # 查询对应相册
        try:
            sticker_db = QiaoQianStickers(
                sticker_name=sticker_name,
                sticker_size=sticker_size,
                sticker_img=sticker,
                user=QiaoQianUser.objects.get(id=user_id)
            )
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        try:
            # 保存数据
            sticker_db.save()

            size = ''
            if sticker_db.sticker_size / 1024 / 1024 > 1:
                size = '%.1fMB' % (sticker_db.sticker_size / 1024 / 1024)
            else:
                size = '%.1fKB' % (sticker_db.sticker_size / 1024)
            # 返回数据
            msg['error_code'] = 0
            msg['stickerInfo'] = {
                'id': sticker_db.id,
                'name': sticker_db.sticker_name,
                'date': sticker_db.create_date.strftime('%Y-%m-%d'),
                'size': size,
                'url': 'http://' + request.get_host() + '/media/' + str(sticker_db.sticker_img)
            }
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        pass

    def get(self, request, *args, **kwargs):
        pass