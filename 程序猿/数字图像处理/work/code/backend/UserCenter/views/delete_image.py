import os
from django.conf import settings
from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
import json
from UserCenter.models import QiaoQianUser
from UserCenter.models import QiaoQianAlbum
from UserCenter.models import QiaoQianImages
from django.views import View
from django.http import HttpResponse

@method_decorator(csrf_exempt, name='dispatch')
class delete_image(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,              # 0 表示成功  1006 表示数据库连接错误
            'album_cover_url': "xxx"
        }
        
        # 获取表单数据
        user_id = request.POST.get('user_id')
        album_id = request.POST.get('album_id')
        image_id = request.POST.get('image_id')

        try:
            isExist = QiaoQianImages.objects.filter(
                id=image_id,
                album=QiaoQianAlbum.objects.get(
                    id=album_id,
                    user=QiaoQianUser.objects.get(id=user_id)
                )
            ).count()

            msg['album_cover_url'] = 'http://' + request.get_host() + '/media/'\
                                     + str(QiaoQianAlbum.objects.get(id=album_id).cover_url)

            if isExist == 1:
                pth = str(QiaoQianImages.objects.get(id = image_id).image)
                QiaoQianImages.objects.get(id=image_id).delete()
                album = QiaoQianAlbum.objects.get(id=album_id)
                album.album_size -= 1
                if album.album_size > 0:
                    print(QiaoQianImages.objects.filter(album=album))
                    album.cover_url = str(QiaoQianImages.objects.filter(album=album).last().image)
                else:
                    album.cover_url = 'default/default_albumCover.png'

                album.save()
                os.remove('{0}/{1}'.format(settings.MEDIA_ROOT, pth))
                msg['error_code'] = 0
                msg['album_cover_url'] = 'http://' + request.get_host() + '/media/' + str(album.cover_url)
                return HttpResponse(json.dumps(msg, ensure_ascii=False))
            else:
                return HttpResponse("图片已不存在！！")
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        pass
