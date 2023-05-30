# -*- coding: utf-8 -*-
"""
Created on Sat Jul 18 10:34:32 2020

@author: 涂晴昊
@information: 功能基本完成，接口没写。
            可提供服务：用户第一次导入人像图片时，可选择为该人物命名；
            则在下一次导入同一个人的照片时，系统可自动为该照片中的人物标识人脸区域并命名。
            适用于人脸带有方向的场景。
"""

import face_recognition
from PIL import Image, ImageDraw
import numpy as np

# 加载已知人脸
yht_image = face_recognition.load_image_file("6.jpg")
yht_face_encoding = face_recognition.face_encodings(obama_image)[0]
#
#biden_image = face_recognition.load_image_file("biden.jpg")
#biden_face_encoding = face_recognition.face_encodings(biden_image)[0]
#
## 已知人脸编码及标识
#known_face_encodings = [
#    obama_face_encoding,
#    biden_face_encoding
#]
#known_face_names = [
#    "Barack Obama",
#    "Joe Biden"
#]

# 加载图片，RGB三通道
unknown_image = face_recognition.load_image_file("7.jpg")

# 定位输入图片的所有人脸，并编码
face_locations = face_recognition.face_locations(unknown_image)
face_encodings = face_recognition.face_encodings(unknown_image, face_locations)

# 转PIL图片
pil_image = Image.fromarray(unknown_image)
# 显示底图
draw = ImageDraw.Draw(pil_image)

# 可对图片中多张人脸进行标识
for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):
#    #看是否与已知人脸匹配
#    matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
#
#    name = "Unknown"
#
#    # 如果匹配到已知人脸，直接标识
#    # if True in matches:
#    #     first_match_index = matches.index(True)
#    #     name = known_face_names[first_match_index]
#
#    # 如果未匹配到已知人脸，可选1.标为最有可能的已知人脸；2.让用户为未知人脸取名
#    face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
#    best_match_index = np.argmin(face_distances)
#    if matches[best_match_index]:
#        name = known_face_names[best_match_index]

    # 定位人脸位置（box）
    draw.rectangle(((left, top), (right, bottom)), outline=(0, 0, 255))
    name = "Unknown"
    # 标识人脸信息
#    text_width, text_height = draw.textsize(name)
#    draw.rectangle(((left, bottom - text_height - 10), (right, bottom)), fill=(0, 0, 255), outline=(0, 0, 255))
#    draw.text((left + 6, bottom - text_height - 5), name, fill=(255, 255, 255, 255))

# del
del draw

# 显示图片
pil_image.show()

# 可下载图片
# pil_image.save("image_with_boxes.jpg")