from django.db import models

def avatar_upload_path(instance, filename):
    return 'user_{0}/{1}'.format(instance.id, filename)

class QiaoQianUser(models.Model):
    user_name = models.CharField(max_length=15)
    user_mail = models.EmailField()
    user_avatar = models.ImageField(upload_to=avatar_upload_path)
    user_password = models.CharField(max_length=100)

    class Meta:
        app_label = 'UserCenter'
        db_table = 'qiaoqian_user'