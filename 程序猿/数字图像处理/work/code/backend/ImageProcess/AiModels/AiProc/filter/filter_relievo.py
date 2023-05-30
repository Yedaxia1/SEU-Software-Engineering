# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 20:05:36 2020

@author: 涂晴昊
@information: 浮雕效果滤镜
"""

import cv2
import numpy as np


def filter_relievo(img):
    # 获取图像的高度和宽度
    height, width = img.shape[:2]
    
    # 图像灰度处理
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    
    # 创建目标图像
    dstImg = np.zeros((height,width,1),np.uint8)
    
    # 卷积核方式
    # kernel = np.array([[-1,0,0],[0,1,0],[0,0,0]])
    # output = cv2.filter2D(src, -1, kernel)
    
    # 浮雕特效算法：newPixel = grayCurrentPixel - grayNextPixel + 150
    for i in range(0,height):
        for j in range(0,width-1):
            grayCurrentPixel = int(gray[i,j])
            grayNextPixel = int(gray[i,j+1])
            newPixel = grayCurrentPixel - grayNextPixel + 150
            if newPixel > 255:
                newPixel = 255
            if newPixel < 0:
                newPixel = 0
            dstImg[i,j] = newPixel
    return dstImg
        
def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_relievo(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()