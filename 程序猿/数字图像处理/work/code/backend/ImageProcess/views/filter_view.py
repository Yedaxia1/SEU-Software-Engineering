from django.utils.decorators import method_decorator
from django.views import View
from django.views.decorators.csrf import csrf_exempt
import base64
from ImageProcess.AiModels.AiProc.filter.filter_blurredGlass import filter_blurredGlass
from ImageProcess.AiModels.AiProc.filter.filter_ColorClot import filter_ColorClot
from ImageProcess.AiModels.AiProc.filter.filter_colorFading import filter_colorFading
from ImageProcess.AiModels.AiProc.filter.filter_defog import filter_defog
from ImageProcess.AiModels.AiProc.filter.filter_harmonic import filter_harmonic
from ImageProcess.AiModels.AiProc.filter.filter_old import filter_old
from ImageProcess.AiModels.AiProc.filter.filter_painter import filter_painter
from ImageProcess.AiModels.AiProc.filter.filter_PaperCutArt import filter_PaperCutArt
from ImageProcess.AiModels.AiProc.filter.filter_relievo import filter_relievo
from ImageProcess.AiModels.AiProc.filter.filter_strange import filter_strange
import numpy as np
import cv2
from django.http import HttpResponse
import json


@method_decorator(csrf_exempt, name='dispatch')
class filter_view(View):
    def post(self, request, *args, **kwargs):
        # 定义返回数据格式
        msg = {
            'error_code': 1008,                    # 0 表示成功  1008 表示处理异常
            'ocr_result': {}
        }
        operation = (int)(request.POST.get('operation'))
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
            # 滤镜处理
            if operation == 0:
                img = filter_blurredGlass(img)
            elif operation == 1:
                img = filter_ColorClot(img)
            elif operation == 2:
                img = filter_colorFading(img)
            elif operation == 3:
                img = filter_defog(img)
            elif operation == 4:
                img = filter_harmonic(img)
            elif operation == 5:
                img = filter_old(img)
            elif operation == 6:
                img = filter_painter(img)
            elif operation == 7:
                img = filter_PaperCutArt(img)
            elif operation == 8:
                img = filter_relievo(img)
            elif operation == 9:
                img = filter_strange(img)
            else:
                return HttpResponse("请求操作码错误！！")
            # 转码base64
            back_img = cv2.imencode('.{0}'.format(img_format), img)[1]
            base64_data = 'data:image/{0};base64,'.format(img_format) + str(base64.b64encode(back_img))[2:-1]
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