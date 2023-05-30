from django.contrib import admin
from UserCenter.models import QiaoQianAlbum, QiaoQianStickers, QiaoQianImages, QiaoQianUser
# Register your models here.
admin.site.register(QiaoQianUser)
admin.site.register(QiaoQianImages)
admin.site.register(QiaoQianStickers)
admin.site.register(QiaoQianAlbum)