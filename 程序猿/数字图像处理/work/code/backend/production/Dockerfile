# FROM python:3.7

# RUN sed -i 's/dl-cdn.alpinelinux.org/mirrors.tuna.tsinghua.edu.cn/g' /etc/apk/repositories

# ENV PYTHONUNBUFFERED 1
# WORKDIR /qiaoqian-backend
# COPY . /qiaoqian-backend/
# RUN pip install -r requirements.txt -i https://mirrors.aliyun.com/pypi/simple/
# COPY ./production/start.sh /start.sh
# RUN sed -i 's/\r//' /start.sh
# RUN chmod +x /start.sh
FROM python:3.7-buster

RUN sed -i 's#http://deb.debian.org#https://mirrors.163.com#g' /etc/apt/sources.list

RUN apt-get update
RUN apt-get upgrade
RUN apt-get install -y python3-dev default-libmysqlclient-dev build-essential default-mysql-client python-tk zlib1g-dev cmake

ENV PYTHONUNBUFFERED 1
WORKDIR /qiaoqianbackend
# COPY ./requirements.txt /qiaoqianbackend/requirements.txt
# COPY ./dlib-19.20.0-cp37-cp37m-linux_x86_64.whl /qiaoqianbackend/dlib-19.20.0-cp37-cp37m-linux_x86_64.whl
ADD . /qiaoqianbackend
RUN pip install dlib-19.20.0-cp37-cp37m-linux_x86_64.whl
RUN pip install -r requirements.txt -i https://mirrors.aliyun.com/pypi/simple/ 
COPY ./production/start.sh /start.sh
RUN sed -i 's/\r//' /start.sh
RUN chmod +x /start.sh
