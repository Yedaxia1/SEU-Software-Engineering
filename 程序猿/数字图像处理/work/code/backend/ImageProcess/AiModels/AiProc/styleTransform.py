# -*- coding: utf-8 -*-
"""
Created on Thu Jul 30 22:32:09 2020

@author: 涂晴昊
@information: 风格迁移，输入i为0~8.
            cartoon：卡通画风格
            pencil：铅笔风格
            color_pencil：彩色铅笔画风格
            warm：彩色糖块油画风格
            wave：神奈川冲浪里油画风格
            lavender：薰衣草油画风格
            mononoke：奇异油画风格
            scream：呐喊油画风格
            gothic：哥特油画风格
"""

# encoding:utf-8

import requests
import base64


def styleTransform(img_base64, i):
    style = ['cartoon','pencil','color_pencil','warm','wave','lavender','mononoke','scream','gothic']

#    # client_id 为官网获取的AK， client_secret 为官网获取的SK
#    host = 'https://aip.baidubce.com/oauth/2.0/token?grant_type=client_credentials&client_id=TrBEjKzysloEa9ec2hY74u2R&client_secret=u7lxgVEuvlFNzlFMlDaNx8c3bjKrRa1v'
#    response = requests.get(host)
##    if response:
##        print(response.json())
#    text = response.json()
#    access_token = text['access_token']

    request_url = "https://aip.baidubce.com/rest/2.0/image-process/v1/style_trans"
    
    params = {"image":img_base64, "option":style[i]}
    access_token = '24.5d8e9fffb3049f847137a856a6c08eac.2592000.1598713964.282335-21699626'
    request_url = request_url + "?access_token=" + access_token
    headers = {'content-type': 'application/x-www-form-urlencoded'}
    response = requests.post(request_url, data=params, headers=headers)
    if response:
        return response.json()['image']
    else:
        raise Exception('请求失败')
        # return styleTransform(img_base64, i)
#    if response:
#        print (response.json())
