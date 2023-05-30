# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 14:09:59 2020

@author: 涂晴昊
@information: 中国剪纸艺术
"""

import cv2
import numpy as np

def filter_PaperCutArt(img):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    
    gray = cv2.cvtColor(src,cv2.COLOR_BGR2GRAY)
    avg = np.mean(gray)
    
    for i in range(rows):
        for j in range(cols):
            if gray[i,j] < avg:
                dst[i,j][0] = 0
                dst[i,j][1] = 0
                dst[i,j][2] = 139
            else:
                dst[i,j][0] = 255
                dst[i,j][1] = 255
                dst[i,j][2] = 255
    return dst

def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_PaperCutArt(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()