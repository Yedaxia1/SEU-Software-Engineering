# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 20:16:16 2020

@author: 涂晴昊
@information: 褪色滤镜
"""

import cv2
import math
import numpy as np

def filter_colorFading(img):
    #获取图像行和列
    rows, cols = img.shape[:2]
    
    #新建目标图像
    dst = np.zeros((rows, cols, 3), dtype="uint8")
    
    #图像流年特效
    for i in range(rows):
        for j in range(cols):
            #B通道的数值开平方乘以参数12
            B = math.sqrt(img[i,j][0]) * 12
            G =  img[i,j][1]
            R =  img[i,j][2]
            if B>255:
                B = 255
            dst[i,j] = np.uint8((B, G, R))
    return dst
        
def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_colorFading(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()