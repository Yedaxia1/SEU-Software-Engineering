#!/bin/sh

python manage.py makemigrations
python manage.py migrate
gunicorn backend.wsgi:application -w 4 -k gthread -b 0.0.0.0:8000 --chdir=/qiaoqianbackend --access-logfile /qiaoqianbackend/log/access.log --error-logfile /qiaoqianbackend/log/error.log