from django.conf import settings
from . import term_freq, norm, document
import heapq
import functools

def cosine_sim(query_dict, query_type, doc_type):
    term_freq_func = term_freq.get_functions()
    norm_func = norm.get_functions()
    doc_func = document.get_functions()
    dic = settings.DICTIONARY
    doc_vector = settings.DOC_VECTOR
    N = settings.N
    score = {}
    length = {}
    query_trans = (term_freq_func[query_type[0]], doc_func[query_type[1]])
    doc_trans = (term_freq_func[doc_type[0]], doc_func[doc_type[1]], norm_func[doc_type[2]])
    word_list = query_dict['tf']
    for word in word_list:
        df = dic[word]['df']
        w_tq = query_trans[0](word, query_dict) * query_trans[1](N, df)
        for d in dic[word]['tf']:
            w_td = doc_trans[0](word, doc_vector[d]) * doc_trans[1](N, df)
            score[d] = score.get(d, 0) + (w_tq * w_td)
            length[d] = 0
    for doc in score:
        norm_factor = doc_trans[2](doc_vector[doc], doc_trans[0], doc_trans[1])
        score[doc] /= norm_factor
    # Top K
    return _top_k(score.items())

def _top_k(scores):
    def compare(o1, o2):
        if abs(o1[1] - o2[1]) <= 0.0000001:
            return int(o1[0]) - int(o2[0])
        if o1[1] < o2[1]:
            return -1
        if o1[1] > o2[1]:
            return 1
    return heapq.nlargest(10, scores, key=functools.cmp_to_key(compare))