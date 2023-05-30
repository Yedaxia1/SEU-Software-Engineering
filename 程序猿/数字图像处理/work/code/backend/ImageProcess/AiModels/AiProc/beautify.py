# -*- coding: utf-8 -*-
"""
Created on Sat Jul 18 9:44:37 2020

@author: 叶宏庭
@information: 磨皮美白效果
"""
import numpy as np
from PIL import Image
import cv2  
import copy
import time


class Beauty():
    # 内部调用函数（识别人体皮肤）
    def generate_skin(self, img):
        """genrate skin table"""
        rows, cols, channels = img.shape
        current_img = copy.deepcopy(img)  # get img data
        current_img = cv2.edgePreservingFilter(img, flags=1, sigma_s=50, sigma_r=0.5)
        skin_table = np.ones(img.shape, np.uint8)  # get data is 0 matrix
        # self.skin_table = copy.deepcopy(self.current_img)
        # Skin is identified by pixels
        for r in range(rows):  
            for c in range(cols):  
                # get pixel value         
                B = img.item(r, c, 0)
                G = img.item(r, c, 1)
                R = img.item(r, c, 2)
                # non-skin area if skin equals 0, skin area equals 1.         
                if (abs(R - G) > 15) and (R > G) and (R > B):  
                    if (R > 95) and (G > 40) and (B > 20) and (max(R,G,B) - min(R,G,B) > 15):
                        pass
                    elif (R > 220) and (G > 210) and (B > 170):  
                        pass
                else:
                    skin_table.itemset((r, c, 2), 0)
                    skin_table.itemset((r, c, 1), 0)
                    skin_table.itemset((r, c, 0), 0)
        
        return skin_table

    
    def buffing(self, img, grade=3):
        '''
            磨皮效果     参数fname：图片路径    grade：磨皮程度（默认值=3）
        '''
        # 生成皮肤
        skin_table = self.generate_skin(img)

        # buffing
        value = grade * 0.05
        current_img = cv2.edgePreservingFilter(img, flags=1, sigma_s=50, sigma_r=value)
        imgskin_c = np.uint8(-(skin_table - 1))
        skin = current_img * skin_table
        
        dst = np.uint8(img * imgskin_c + skin)
        
        return dst

    def white_skin(self, img, power=5):
        '''
            美白效果    fname：图片路径     power : 0 ~ 100
        '''
        # 生成皮肤
        skin_table = self.generate_skin(img)

        skin = img * skin_table
        power = power / 100.0
        rows,cols,channels = skin.shape
        for r in range(rows):  
            for c in range(cols):  
                B = skin.item(r, c, 0)
                G = skin.item(r, c, 1)
                R = skin.item(r, c, 2)
                max_value = max([R, G, B])
                degree = 255 - max_value - int(max_value*power)
                if degree >= 0: degree = int(max_value*power)
                else: degree = 255 - max_value
                skin.itemset((r, c, 0), B + degree)
                skin.itemset((r, c, 1), G + degree)
                skin.itemset((r, c, 2), R + degree)
        
        imgskin_c = np.uint8(-(skin_table - 1))
        dst = np.uint8(img * imgskin_c + skin)
        
        return dst

def main():
    b = Beauty()
    img = cv2.imread('./22.png')
    img1 = b.buffing('./22.png')
    img2 = b.white_skin('./22.png')

    cv2.imshow('img', img)
    cv2.imshow('img1', img1)
    cv2.imshow('img2', img2)
    cv2.waitKey(0)

if __name__ == '__main__':
    main()