from django.utils.decorators import method_decorator
from django.views.decorators.csrf import csrf_exempt
import json
from UserCenter.models import QiaoQianUser
from UserCenter.models import QiaoQianAlbum
from django.views import View
from django.http import HttpResponse

@method_decorator(csrf_exempt, name='dispatch')
class change_album_name(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1006,
            'AlbumInfo': {}
        }
        # 获取表单数据
        user_id = request.POST.get('user_id')
        album_id = request.POST.get('album_id')
        album_name = request.POST.get('album_name')
        album_new_name = request.POST.get('album_new_name')

        try:
            # 查询相册
            isExist = QiaoQianAlbum.objects.filter(
                id=album_id,
                album_name=album_name,
                user=QiaoQianUser.objects.get(id=user_id)
            ).count()

            # 相册存在
            if isExist == 1:
                album = QiaoQianAlbum.objects.get(id=album_id)
                album.album_name = album_new_name
                album.save()

                # 读取相册信息
                msg['error_code'] = 0
                msg['AlbumInfo'] = {
                    'id': album.id,
                    'name': album.album_name,
                    'date': album.create_date.strftime('%Y-%m-%d'),
                    'size': album.album_size,
                    'url': 'http://' + request.get_host() + '/media/' + album.cover_url
                }

                return HttpResponse(json.dumps(msg, ensure_ascii=False))
            else:
                return HttpResponse("相册已经不存在！！")
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

    def get(self, request, *args, **kwargs):
        pass