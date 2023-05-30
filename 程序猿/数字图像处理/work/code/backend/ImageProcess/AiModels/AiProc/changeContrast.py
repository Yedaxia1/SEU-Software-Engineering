# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 15:33:18 2020

@author: 涂晴昊
@information: 修改对比度，参数-100~100
"""

import cv2
import numpy as np

def changeContrast(img,degree):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    if (degree < -100): 
        degree = -100
    if (degree > 100): 
        degree = 100
    contrast = (100.0 + degree) / 100.0
    contrast = contrast**2
    
    for i in range(rows):
        for j in range(cols):
            for k in range(3):
                val = int(((1.0*src[i,j][k]/255.0-0.5)*contrast+0.5)*255.0)
                if(val<0):
                    val = 0
                if(val>255):
                    val = 255
                dst[i,j][k] = val
    return dst

def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = changeContrast(src,50)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()
            