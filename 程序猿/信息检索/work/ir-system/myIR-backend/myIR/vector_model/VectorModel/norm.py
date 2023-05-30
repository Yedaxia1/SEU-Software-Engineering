from django.conf import settings
import math

def get_functions():
    return [_none, _l2_norm]

def _none(dic, tf_trans, doc_trans):
    return 1

def _l2_norm(dic, tf_trans, doc_trans):
    res = 0.0
    N = settings.N
    d = settings.DICTIONARY
    word_list = dic['tf']
    for word in word_list:
        w = tf_trans(word, dic) * doc_trans(N, d[word]['df'])
        res += float(w * w)
    return math.sqrt(res)