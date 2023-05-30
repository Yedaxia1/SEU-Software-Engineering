import os
from django.conf import settings
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
class delete_sticker(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006  # 0 表示成功  1006 表示数据库连接错误
        }
        # 获取表单数据
        user_id = request.POST.get('user_id')
        sticker_id = request.POST.get('sticker_id')

        try:
            isExist = QiaoQianStickers.objects.filter(
                id=sticker_id,
                user=QiaoQianUser.objects.get(id=user_id)
            ).count()
            if isExist == 1:
                pth = str(QiaoQianStickers.objects.get(id=sticker_id).sticker_img)
                QiaoQianStickers.objects.get(id=sticker_id).delete()

                os.remove('{0}/{1}'.format(settings.MEDIA_ROOT, pth))
                msg['error_code'] = 0
                return HttpResponse(json.dumps(msg, ensure_ascii=False))
            else:
                return HttpResponse("贴纸已不存在！！")
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        pass
