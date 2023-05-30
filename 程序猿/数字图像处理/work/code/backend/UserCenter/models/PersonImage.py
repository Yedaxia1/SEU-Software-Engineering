from django.db import models
from UserCenter.models import PersonType

class PersonImage(models.Model):
    person_type = models.ForeignKey(PersonType, on_delete=models.CASCADE)
    name = models.CharField(max_length=300)
    size = models.IntegerField()
    date = models.DateField(auto_now_add=True)
    url = models.CharField(max_length=300)
    class Meta:
        app_label = 'UserCenter'
        db_table = 'qiaoqian_personimage'
