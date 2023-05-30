import math
from django.conf import settings
def get_tf_idf(item, doc_id, n):
    try:
        tf = item['tf'][doc_id]
        df = item['df']
        ret = tf * math.log10(float(n) / float(df))
    except KeyError:
        ret = 0
    return ret

def get_wf_idf(item, doc_id, n):
    try:
        tf = item['tf'][doc_id]
        df = item['df']
        wf = 0 if tf == 0 else 1 + math.log10(tf)
        ret = wf * math.log10(float(n) / float(df))
    except KeyError:
        ret = 0
    return ret

# 0代表tf_idf, 1代表wf_idf
def get_score(word_list, doc_id, query_type):
    dic = settings.DICTIONARY
    n = settings.N
    score = 0
    for word in word_list:
        if query_type == 0:
            score += get_tf_idf(dic[word], doc_id, n)
        else:
            score += get_wf_idf(dic[word], doc_id, n)
    return float(score)