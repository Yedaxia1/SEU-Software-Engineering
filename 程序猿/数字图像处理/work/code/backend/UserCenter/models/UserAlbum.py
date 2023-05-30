from django.db import models
from UserCenter.models import QiaoQianUser

class QiaoQianAlbum(models.Model):
    album_name = models.CharField(max_length=30)
    create_date = models.DateField(auto_now_add=True)
    album_size = models.PositiveSmallIntegerField()
    cover_url = models.CharField(max_length=300)
    user = models.ForeignKey(QiaoQianUser, on_delete=models.CASCADE)
    class Meta:
        app_label = 'UserCenter'
        db_table = 'qiaoqian_album'
