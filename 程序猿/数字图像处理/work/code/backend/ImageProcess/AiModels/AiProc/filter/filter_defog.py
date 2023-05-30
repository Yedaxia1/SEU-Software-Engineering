# -*- coding: utf-8 -*-
"""
Created on Thu Jul 16 15:53:27 2020

@author: 叶宏庭
@information: 去雾效果滤镜
"""

import numpy as np
import cv2

def filter_defog(img):
    # 图片三通道分割
    b, g, r = cv2.split(img)

    # 设置参数
    clahe = cv2.createCLAHE(clipLimit=2.0, tileGridSize=(8,8))

    # 三通道各自均衡化
    cl1 = clahe.apply(b)
    cl2 = clahe.apply(g)
    cl3 = clahe.apply(r)

    # 合并三通道
    dst = cv2.merge([cl1, cl2, cl3])
    return dst

def main():
    src = './defogtest.png'
    dst = filter_defog(src)
    # 显示图像
    cv2.imshow('src',cv2.imread(src))
    cv2.imshow('dst',dst)
    cv2.waitKey()
    cv2.destroyAllWindows()


if __name__ == '__main__':
    main()
