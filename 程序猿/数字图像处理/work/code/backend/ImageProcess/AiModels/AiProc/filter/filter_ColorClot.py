# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 16:52:10 2020

@author: 涂晴昊
@information: 效果类似于儿童蜡笔画
"""

import cv2
import numpy as np


def filter_ColorClot(img):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    border = 2
    for i in range(border,rows-border):
        for j in range(border,cols-border):
            for k in range(3):
                val = src[i,j][k]
                for x in range(-border,border+1):
                    for y in range(-border,border+1):
                        val = min(val, src[i+x,j+y][k])
                dst[i,j][k] = val
    return dst


def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_ColorClot(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()