FROM python:3.7-buster

RUN sed -i 's#http://deb.debian.org#https://mirrors.163.com#g' /etc/apt/sources.list

RUN apt-get update
RUN apt-get upgrade
RUN apt-get install -y python3-dev default-libmysqlclient-dev build-essential default-mysql-client python-tk zlib1g-dev cmake

ENV PYTHONUNBUFFERED 1
WORKDIR /qiaoqian-backend
COPY ./requirements.txt /qiaoqian-backend/requirements.txt
COPY ./dlib-19.20.0-cp37-cp37m-linux_x86_64.whl /qiaoqian-backend/dlib-19.20.0-cp37-cp37m-linux_x86_64.whl
RUN pip install dlib-19.20.0-cp37-cp37m-linux_x86_64.whl
RUN pip install -r requirements.txt -i https://mirrors.aliyun.com/pypi/simple/ 
COPY ./local/start.sh /start.sh
RUN sed -i 's/\r//' /start.sh
RUN chmod +x /start.sh
