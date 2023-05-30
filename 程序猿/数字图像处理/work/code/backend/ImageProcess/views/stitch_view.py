from django.utils.decorators import method_decorator
from django.views import View
from django.views.decorators.csrf import csrf_exempt
import base64
from ImageProcess.AiModels.AiProc.paranoma.stitch import stitch
import numpy as np
import cv2
from django.http import HttpResponse
import json


@method_decorator(csrf_exempt, name='dispatch')
class stitch_view(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1008,                    # 0 表示成功  1008 表示处理异常
            'img_proc_result': "xxx"
        }
        data = json.loads(request.body.decode())
        num_of_imgs = int(data['img_num'])
        images = []
        for i in range(num_of_imgs):
            # 获取base64编码
            img_base64 = data['editedImg'][i]
            # 获取图片格式
            # 获取图片编码
            img_base64 = img_base64.split('base64,')[1]
            # 转为图片string
            img_string = base64.b64decode(img_base64, '-_')
            # 转为opencv格式
            img_uint8 = np.fromstring(img_string, np.uint8)
            img = cv2.imdecode(img_uint8, cv2.IMREAD_COLOR)
            images.append(img)
        try:
            # 美白结果
            dst = stitch(num_of_imgs, images)
            # 转码base64
            back_img = cv2.imencode('.jpg', dst)[1]
            base64_data = 'data:image/jpeg;base64,' + str(base64.b64encode(back_img))[2:-1]
            # 结果
            msg['img_proc_result'] = base64_data
            msg['error_code'] = 0
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

        # back_img = cv2.imencode('.{0}'.format(img_format), img)[1]
        # base64_data = 'data:image/{0};base64,'.format(img_format) + str(base64.b64encode(back_img))[2:-1]


    def get(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")