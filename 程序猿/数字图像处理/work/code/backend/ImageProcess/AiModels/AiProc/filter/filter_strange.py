# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 14:24:04 2020

@author: 涂晴昊
@information: 碧绿碧绿诡异诡异的滤镜。
"""

import cv2
import numpy as np

def filter_strange(img):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    
    for i in range(rows):
        for j in range(cols):
            b = src[i,j][0]
            g = src[i,j][1]
            r = src[i,j][2]
            R = r*r/255
            G = g*g/255
            B = b*b/255
            if(R>255):
                R=255
            if(R<0):
                R=0
            if(G>255):
                G=255
            if(G<0):
                G=0
            if(B>255):
                B=255
            if(B<0):
                B=0
            dst[i,j][0] = B
            dst[i,j][1] = G
            dst[i,j][2] = R
    return dst
        
def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_strange(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()