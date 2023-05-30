# -*- coding: utf-8 -*-
"""
Created on Thu Jul 26 15:46:44 2020

@author: 涂晴昊
@information: 全景拼接功能，传回图片数目及图片tuple。
"""
from ImageProcess.AiModels.AiProc.paranoma.panorama import Panaroma
import imutils
import cv2


def change_size(filename):
    #    image=cv2.imread(filename,1) #读取图片
    img = cv2.medianBlur(filename, 5)  # 中值滤波，去除黑色边际中可能含有的噪声干扰
    b = cv2.threshold(img, 15, 255, cv2.THRESH_BINARY)  # 调整裁剪效果
    binary_image = b[1]  # 二值图--具有三通道
    binary_image = cv2.cvtColor(binary_image, cv2.COLOR_BGR2GRAY)
    print(binary_image.shape)  # 改为单通道

    x = binary_image.shape[0]
    y = binary_image.shape[1]
    edges_x = []
    edges_y = []
    for i in range(x):
        for j in range(y):
            if binary_image[i][j] == 255:
                edges_x.append(i)
                edges_y.append(j)

    left = min(edges_x)  # 左边界
    right = max(edges_x)  # 右边界
    width = right - left  # 宽度
    bottom = min(edges_y)  # 底部
    top = max(edges_y)  # 顶部
    height = top - bottom  # 高度

    pre1_picture = filename[left:left + width, bottom:bottom + height]  # 图片截取
    return pre1_picture  # 返回图片数据

def stitch(no_of_images, images):
#print("输入图片数目:")
#no_of_images = int(input())
#print("选择需要拼接的图片，图片顺序从左到右:")
##类似于a.jpg
#filename = []
#
## 此处需要修改到与前端兼容
#for i in range(no_of_images):
#    print("输入第 %d 张图片:" %(i+1))
#    filename.append(input())
    """
    images = []

    for i in range(no_of_images):
        images.append(cv2.imread(filename[i]))
    """
    # 修改图片尺寸到大小一致
    for i in range(no_of_images):
        images[i] = imutils.resize(images[i], width=400)
    
    for i in range(no_of_images):
        images[i] = imutils.resize(images[i], height=400)
    
    panaroma = Panaroma()
    if no_of_images == 2:
        (result, matched_points) = panaroma.image_stitch([images[0], images[1]], match_status=True)
    else:
        (result, matched_points) = panaroma.image_stitch([images[no_of_images-2], images[no_of_images-1]], match_status=True)
        for i in range(no_of_images - 2):
            (result, matched_points) = panaroma.image_stitch([images[no_of_images-i-3], result], match_status=True)
    result = change_size(result)
    return result
    """
    # 全景图及特征点
    for i in range(no_of_images):
        cv2.imshow("Image {k}".format(k=i+1), images[i])
    
    cv2.imshow("Keypoint Matches", matched_points)
    cv2.imshow("Panorama", result)
    
    # 存储图片
    cv2.imwrite("Matched_points.jpg",matched_points)
    cv2.imwrite("Panorama_image.jpg",result)
    
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    """
