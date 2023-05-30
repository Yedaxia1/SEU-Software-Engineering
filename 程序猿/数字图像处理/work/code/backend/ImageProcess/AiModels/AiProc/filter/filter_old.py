# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 20:13:15 2020

@author: 涂晴昊
@information: 怀旧效果滤镜
"""

import cv2
import numpy as np

def filter_old(img):
    #获取图像行和列
    rows, cols = img.shape[:2]
    
    #新建目标图像
    dst = np.zeros((rows, cols, 3), dtype="uint8")
    
    #图像怀旧特效
    for i in range(rows):
        for j in range(cols):
            B = 0.272*img[i,j][2] + 0.534*img[i,j][1] + 0.131*img[i,j][0]
            G = 0.349*img[i,j][2] + 0.686*img[i,j][1] + 0.168*img[i,j][0]
            R = 0.393*img[i,j][2] + 0.769*img[i,j][1] + 0.189*img[i,j][0]
            if B>255:
                B = 255
            if G>255:
                G = 255
            if R>255:
                R = 255
            dst[i,j] = np.uint8((B, G, R))
    return dst
        
def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_old(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()
