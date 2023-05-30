# -*- coding: utf-8 -*-
"""
Created on Sat Jul 18 11:45:28 2020

@author: 涂晴昊
@information: 基本完成，导入系统默认贴纸和自定义贴纸的时候图片背景需要是黑色。
            可同时为多个人脸贴图。
            demo形态，贴纸位置可能需优化。
"""

import face_recognition
import cv2

def face_hat(img,h):
    # 加载图片，格式cv2可用，RGB三通道
#    image = face_recognition.load_image_file("7.jpg")
#    image = cv2.cvtColor(image,cv2.COLOR_RGB2BGR)
    image = img.copy()
#    hat = cv2.imread("hat.png") 
    hat = h.copy()
    
    face_locations = face_recognition.face_locations(image)
    
    print(len(face_locations))
    #grayHat = cv2.cvtColor(hat, cv2.COLOR_RGB2GRAY)
    #cv2.imshow("hat",hat)
    
    # 可同时为多个人脸贴图
    if len(face_locations):
        for (top, right, bottom, left) in face_locations:
            print(top, right, bottom, left)
            sp = hat.shape
            hatSizeH = int(sp[0]/sp[1]*(right-left))
            if hatSizeH>(top-20):
                hatSizeH = top-20
            hatSize = cv2.resize(hat,(right-left,hatSizeH),interpolation=cv2.INTER_NEAREST)
            hatTop = top-hatSizeH-20
            if hatTop<=0:
                hatTop = 0
            rows, cols,channels = hatSize.shape
            #找到帽子放置位置roi
            roi = image[hatTop:hatTop+rows,left:left+cols]
            
            #给出两个相反的mask
            grayHat = cv2.cvtColor(hatSize, cv2.COLOR_RGB2GRAY)
            ret, mask = cv2.threshold(grayHat,10,255,cv2.THRESH_BINARY)
            mask_inv = cv2.bitwise_not(mask)
            
            #黑化ROI中帽子所在的地方
            img_bg = cv2.bitwise_and(roi,roi,mask = mask_inv)
            
            #提取帽子
            img_fg = cv2.bitwise_and(hatSize,hatSize,mask = mask)
            
            dst = cv2.add(img_bg,img_fg)
    #        dst = cv2.addWeighted(roi,0.5,hat,0.5,0)
            image[hatTop:hatTop+rows,left:left+cols] = dst
    return image
    #cv2.imshow("roi",roi)
    #cv2.imshow("bg",img_bg)
    #cv2.imshow("fg",img_fg)
#    cv2.imshow("test",image)
#    cv2.waitKey(0)   
#    cv2.destroyAllWindows()