# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 16:29:34 2020

@author: 涂晴昊
@information: 挤压图片,传参范围未测试
"""

import cv2
import numpy as np
import math

def Pince(img, degree):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    if (degree < 1): 
        degree = 1
    if (degree > 32): 
        degree = 32
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    midX = int(cols/2)
    midY = int(rows/2)
    for i in range(rows):
        for j in range(cols):
            offsetX = j - midX
            offsetY = i - midY
            radian = math.atan2(float(offsetY),float(offsetX))
            radius = math.sqrt(float(offsetX * offsetX + offsetY * offsetY))
            radius = math.sqrt(radius) * degree
            X = int((radius * math.cos(radian)) + midX)
            Y = int((radius * math.sin(radian)) + midY)
            if (X < 0): 
                X = 0
            if (X >= cols): 
                X = cols - 1
            if (Y < 0): 
                Y = 0
            if (Y >= rows):
                Y = rows - 1
            for k in range(3):
                dst[i,j][k] = src[Y,X][k]
    return dst


def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = Pince(src,20)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()
            