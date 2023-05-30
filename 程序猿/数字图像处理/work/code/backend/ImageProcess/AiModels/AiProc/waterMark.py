# -*- coding: utf-8 -*-
"""
Created on Mon Jul 20 9:44:37 2020

@author: 叶宏庭
@information: 水印效果
"""
import cv2
import numpy as np
from PIL import Image, ImageDraw, ImageFont, ImageFilter
from django.conf import settings


def gen_img(text, dsize):
    """
        根据文本生成对应的水印背景
    """
    width, height = dsize[:2]
    image = Image.new('RGB', (width, height), (0, 0, 0))
    
    draw = ImageDraw.Draw(image)
    text = text
    img_fraction = 0.5
    fontsize = 25
    font = ImageFont.truetype(settings.BASE_DIR + '/ImageProcess/AiModels/resource/fontt.ttf', size=fontsize)
    while font.getsize(text)[0] < img_fraction * image.size[0]:
        fontsize += 1
        font = ImageFont.truetype(settings.BASE_DIR + "/ImageProcess/AiModels/resource/fontt.ttf", fontsize)
    
    position = (width - font.getsize(text)[0], height - font.getsize(text)[1])
    draw.text(position, text, fill=(252, 157, 154), font=font, spacing=0, align='left')

    return image

def waterMark(img, text='@QiaoQian', transparency=0.5):
    """
        生成水印   fname：图片路径  text：水印文本  transparency：透明度
    """
    src = img
    b_rows, b_cols, b_channels = src.shape
    mask = cv2.cvtColor(np.asarray(gen_img(text, ((int)(b_rows/2), (int)(b_cols/6)))), cv2.COLOR_RGB2BGR)
    m_rows, m_cols, m_channels = mask.shape
    mask = np.floor(mask.astype(np.float32) * transparency).astype(np.uint8)
    partdst = cv2.add(src[b_rows-m_rows:b_rows, b_cols-m_cols:b_cols, ], mask)
    partdst = partdst * (partdst <= 255) + 255 * (partdst > 255)
    partdst = partdst.astype(np.uint8)
    dst = src
    dst[b_rows-m_rows:b_rows, b_cols-m_cols:b_cols, ] = partdst
    
    return dst

def main():
    waterMark('./yht.jpg', '@QiaoQian')


if __name__ == '__main__':
    main()

