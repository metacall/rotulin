from django.db import models
import time

class Document(models.Model):
	path = 'documents/%s/' % (time.strftime('%Y/%m/%d'))
	docfile = models.FileField(upload_to=path)
