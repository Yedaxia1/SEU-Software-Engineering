from django.utils.decorators import method_decorator
from django.views import View
from django.views.decorators.csrf import csrf_exempt
import base64
from ImageProcess.AiModels.AiProc import OCR_proc
import numpy as np
import cv2
from django.http import HttpResponse
import json


@method_decorator(csrf_exempt, name='dispatch')
class OCR_proc_view(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1008,                    # 0 表示成功  1008 表示处理异常
            'ocr_result': {}
        }
        # 获取base64编码
        img_base64 = request.POST.get('editedImg')
        # 获取图片格式
        img_format = img_base64.split(';')[0].split('/')[1]
        # 获取图片编码
        img_base64 = img_base64.split('base64,')[1]
        # 转为图片string
        img_string = base64.b64decode(img_base64, '-_')
        # 转为opencv格式
        img_uint8 = np.fromstring(img_string, np.uint8)
        img = cv2.imdecode(img_uint8, cv2.IMREAD_COLOR)
        try:
            # OCR识别结果
            result = OCR_proc.OCR_proc(img)
            msg['ocr_result'] = result
            msg['error_code'] = 0
            return HttpResponse(json.dumps(msg, ensure_ascii=False))
        except Exception as e:
            print(e.args)
            return HttpResponse(json.dumps(msg, ensure_ascii=False))

        # back_img = cv2.imencode('.{0}'.format(img_format), img)[1]
        # base64_data = 'data:image/{0};base64,'.format(img_format) + str(base64.b64encode(back_img))[2:-1]


    def get(self, request, *args, **kwargs):
        return HttpResponse("请求方法错误！！")