from django.db import models
from UserCenter.models import QiaoQianAlbum

def image_upload_path(instance, filename):
    return 'user_{0}/pictures/album_{1}/{2}'.format(instance.album.user.id, instance.album.id, filename)

class QiaoQianImages(models.Model):
    image_name = models.CharField(max_length=300)
    image_size = models.IntegerField()
    image_date = models.DateField(auto_now_add=True)
    image = models.ImageField(upload_to=image_upload_path)
    album = models.ForeignKey(QiaoQianAlbum, on_delete=models.CASCADE)
    class Meta:
        app_label = 'UserCenter'
        db_table = 'qiaoqian_images'
