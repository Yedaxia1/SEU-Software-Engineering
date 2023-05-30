from django.db import models
from UserCenter.models import QiaoQianUser

def sticker_upload_path(instance, filename):
    user_id = instance.user.id
    return 'user_{0}/stickers/{1}'.format(user_id, filename)

class QiaoQianStickers(models.Model):
    sticker_name = models.CharField(max_length=300)
    sticker_size = models.IntegerField()
    create_date = models.DateField(auto_now_add=True)
    sticker_img = models.ImageField(upload_to=sticker_upload_path)
    user = models.ForeignKey(QiaoQianUser, on_delete=models.CASCADE)
    class Meta:
        app_label = 'UserCenter'
        db_table = 'qiaoqian_sticker'
