# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 16:22:53 2020

@author: 涂晴昊
@information: 调和浮雕算法
"""

import cv2
import numpy as np

def filter_harmonic(img):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    border = 1
    for i in range(border,rows-border):
        for j in range(border,cols-border):
            for k in range(3):
                val = 4 * src[i,j][k] - src[i-1,j-1][k] - src[i-1,j+1][k] - src[i+1,j-1][k] - src[i+1,j+1][k]
                val = val + 156
                if(val<0):
                    val = 0
                if(val>255):
                    val = 255
                dst[i,j][k] = val
    return dst


def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_harmonic(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()
            