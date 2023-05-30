# -*- coding: utf-8 -*-
"""
Created on Fri Jul 17 15:53:27 2020

@author: 叶宏庭
@information: OCR文字识别
"""

import cv2
import requests
import base64
import json

def OCR_proc(pimg):
    # 请求用户信息
    request_url = "https://aip.baidubce.com/rest/2.0/ocr/v1/accurate_basic"
    access_token = '24.4619ce7a341c9f6df7cdca876a9612ae.2592000.1597540971.282335-21419521'

    image = cv2.imencode('.jpg', pimg)[1]
    img = str(base64.b64encode(image))[2:-1]

    # 设置数据格式
    params = {"image": img}
    request_url = request_url + "?access_token=" + access_token
    headers = {'content-type': 'application/x-www-form-urlencoded'}

    # post请求
    response = requests.post(request_url, data=params, headers=headers)
    if response:
        result = {
            'words_result_num': response.json()['words_result_num'],
            'words_result': response.json()['words_result']
        }

        # with open('./ocrformat.json', 'w') as file_obj:
        #     json.dump(result, file_obj, indent=1)

        return result

# def main():
#     src = './ocrtest.jpg'
#     dsttext = OCR_proc(src)
#     # 显示图像
#     cv2.imshow('src',cv2.imread(src))
#     print(dsttext)
#     cv2.waitKey()
#     cv2.destroyAllWindows()
#
#
# if __name__ == '__main__':
#     main()