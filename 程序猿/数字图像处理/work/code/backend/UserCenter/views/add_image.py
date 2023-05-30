from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
import json
from UserCenter.models import QiaoQianUser
from UserCenter.models import QiaoQianAlbum
from UserCenter.models import QiaoQianImages
from django.views import View
from django.http import HttpResponse

@method_decorator(csrf_exempt, name='dispatch')
class add_image(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,
            'imageInfo': {}
        }

        # 读取请求信息
        user_id = request.POST.get('user_id')
        album_id = request.POST.get('album_id')
        image = request.FILES.get('image')
        image_name = image.name
        image_size = image.size
        # 查询对应相册
        try:
            img_db = QiaoQianImages(
                image_name=image_name,
                image_size=image_size,
                image=image,
                album=QiaoQianAlbum.objects.get(
                    id=album_id,
                    user=QiaoQianUser.objects.get(id=user_id)
                )
            )
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        try:
            # 保存数据
            img_db.save()

            img_db.album.cover_url = str(img_db.image)
            img_db.album.album_size += 1
            img_db.album.save()

            size = img_db.image_size
            if size / 1024 / 1024 > 1:
                size = '%.1fMB' % (size / 1024 /1024)
            else:
                size = '%.1fKB' % (size / 1024)
            # 返回数据
            msg['error_code'] = 0
            msg['imageInfo'] = {
                'id': img_db.id,
                'name': img_db.image_name,
                'date': img_db.image_date.strftime('%Y-%m-%d'),
                'size': img_db.image_size,
                'url': 'http://' + request.get_host() + '/media/' + str(img_db.image)
            }
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        pass

    def get(self, request, *args, **kwargs):
        pass