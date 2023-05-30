# -*- coding: utf-8 -*-
"""
Created on Tue Jul 14 20:00:27 2020

@author: 涂晴昊
@information: 毛玻璃效果滤镜
"""

import cv2
import numpy as np

def filter_blurredGlass(img):
    #读取原始图像
    src = img
    
    #新建目标图像
    dst = np.zeros_like(src)
    
    #获取图像行和列
    rows, cols = src.shape[:2]
    
    #定义偏移量和随机数
    offsets = 5
    random_num = 0
    
    #毛玻璃效果: 像素点邻域内随机像素点的颜色替代当前像素点的颜色
    for y in range(rows - offsets):
        for x in range(cols - offsets):
            random_num = np.random.randint(0,offsets)
            dst[y,x] = src[y + random_num,x + random_num]
    return dst

def main():
    src = 'C:/Users/76785/Desktop/20190412092022105.png'
    dst = filter_blurredGlass(src)
    #显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()
    
    
if __name__ == '__main__':
    main()
    
    
    
    
    