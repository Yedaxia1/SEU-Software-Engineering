from django.db import models
from UserCenter.models import QiaoQianUser

class PersonType(models.Model):
    type_name = models.CharField(max_length=30)
    cover_url = models.CharField(max_length=300)
    user = models.ForeignKey(QiaoQianUser, on_delete=models.CASCADE)
    class Meta:
        app_label = 'UserCenter'
        db_table = 'qiaoqian_persontype'
