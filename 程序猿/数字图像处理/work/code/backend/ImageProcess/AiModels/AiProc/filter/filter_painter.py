# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 20:10:37 2020

@author: 涂晴昊
@information: 素描效果滤镜
"""

import cv2
import numpy as np

def filter_painter(img):
    #读取原始图像
    src = img
    
    #图像灰度处理
    gray = cv2.cvtColor(src,cv2.COLOR_BGR2GRAY)
    
    #自定义卷积核
    kernel = np.array([[-1,-1,-1],[-1,10,-1],[-1,-1,-1]])
    
    #图像油漆效果
    output = cv2.filter2D(gray, -1, kernel)
    return output

def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_painter(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()