from django.conf.urls import url
from frontend.uploader.views import list

urlpatterns = [
    url(r'^list/$', list, name='list')
]
