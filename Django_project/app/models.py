from django.db import models


# Create your models here.

class Stuff(models.Model):
    img = models.ImageField()
    name = models.CharField(max_length=20)
    price = models.IntegerField()