from django.urls import path
from . import views
urlpatterns = [
    path('bim/query/', views.bim_query, name='bim_query'),
    path('mle/query/', views.mle_query, name='mle_query')
]
