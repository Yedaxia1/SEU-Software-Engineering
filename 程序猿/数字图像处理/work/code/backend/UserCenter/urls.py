from django.urls import path

from UserCenter.views.login import login_view
from UserCenter.views import register_view
from UserCenter.views import change_user_name
from UserCenter.views import add_album
from UserCenter.views import delete_album
from UserCenter.views import change_user_name_view
from UserCenter.views import ChangeUserAvatarView
from UserCenter.views import getAllAlbumsInfo
from UserCenter.views import getAllStickersInfo
from UserCenter.views import getAllImagesInfo
from UserCenter.views import add_image
from UserCenter.views import add_sticker
from UserCenter.views import change_album_name
from UserCenter.views import delete_image
from UserCenter.views import delete_sticker
from UserCenter.views import get_image_base64
from UserCenter.views import change_password

urlpatterns = [
    path('register/', register_view.as_view(), name='register'),
    path('login/', login_view.as_view(), name='login'),
    path('change-user-name/', change_user_name.change_user_name_view.as_view(), name='change-user-name'),
    path('add-album/', add_album.as_view(), name='add-album'),
    path('delete-album/', delete_album.as_view(), name='delete-album'),
    path('change-user-name/', change_user_name_view.as_view(), name='change-user-name'),
    path('change-avatar/', ChangeUserAvatarView.as_view(), name='change-avatar'),
    path('getAllAlbumsInfo/', getAllAlbumsInfo.getAllAlbumsInfo.as_view(), name='getAllAlbumsInfo'),
    path('getAllStickersInfo/', getAllStickersInfo.getAllStickersInfo.as_view(), name='getAllStickersInfo'),
    path('getImagesInfo/', getAllImagesInfo.as_view(), name='getImagesInfo'),
    path('add-image/', add_image.as_view(), name='add-image'),
    path('add-sticker/', add_sticker.as_view(), name='add-sticker'),
    path('change-album-name/', change_album_name.as_view(), name='change-album-name'),
    path('delete-image/', delete_image.as_view(), name='delete-image'),
    path('delete-sticker/', delete_sticker.as_view(), name='delete-sticker'),
    path('get-image-base64/', get_image_base64.as_view(), name='get-image-base64'),
    path('change-password/', change_password.as_view(), name='change-password')
]
