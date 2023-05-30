from django.urls import path
from ImageProcess.views import OCR_proc_view
from ImageProcess.views import waterMark_view
from ImageProcess.views import changeContrast_view
from ImageProcess.views import changeSharp_view
from ImageProcess.views import beautify_white_view
from ImageProcess.views import beautify_buffering_view
from ImageProcess.views import picScanner_view
from ImageProcess.views import face_makeup_view
from ImageProcess.views import faceswap_view
from ImageProcess.views import stitch_view
from ImageProcess.views import pince_view
from ImageProcess.views import filter_view
from ImageProcess.views import face_thin_view
from ImageProcess.views import styleTransform_view

urlpatterns = [
    path('ocr-proc/', OCR_proc_view.OCR_proc_view.as_view(), name='ocr-proc'),
    path('waterMark/', waterMark_view.waterMark_view.as_view(), name='waterMark'),
    path('changeContrast/', changeContrast_view.changeContrast_view.as_view(), name='changeContrast'),
    path('changeSharp/', changeSharp_view.changeSharp_view.as_view(), name='changeSharp'),
    path('beautify_white/', beautify_white_view.beautify_white_view.as_view(), name='beautify_white'),
    path('beautify_buffering/', beautify_buffering_view.beautify_buffering_view.as_view(), name='beautify_buffering'),
    path('picScanner/', picScanner_view.picScanner_view.as_view(), name='picScanner'),
    path('face_makeup/', face_makeup_view.face_makeup_view.as_view(), name='face_makeup'),
    path('faceswap/', faceswap_view.faceswap_view.as_view(), name='faceswap'),
    path('stitch/', stitch_view.stitch_view.as_view(), name='stitch'),
    path('pince/', pince_view.pince_view.as_view(), name='pince'),
    path('filter/', filter_view.filter_view.as_view(), name='filter'),
    path('face_thin/', face_thin_view.face_thin_view.as_view(), name='face_thin'),
    path('styleTransform/', styleTransform_view.styleTransform_view.as_view(), name='styleTransform')
]
