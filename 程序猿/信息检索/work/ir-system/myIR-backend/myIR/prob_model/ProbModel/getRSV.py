from django.conf import settings
import functools
import json
import math

def calculateRSV(query_terms, doc_list):
    doc_total_num = settings.N
    term_dict = settings.DICTIONARY
    doc_probability = settings.DOC_PROBABILITY

    score = dict()
    for doc_id in doc_list:
        score[doc_id] = 0
    
    for term in query_terms:
        for doc_id in term_dict[term]["tf"].keys():
            if doc_id in score.keys():
                score[doc_id] += math.exp(doc_probability[term]["ci"])
    
    ans = []

    for doc_id in score.keys():
        ans.append((doc_id, score[doc_id]))
    
    def my_compare(x, y):
        if x[1] > y[1]:
            return -1
        elif x[1] < y[1]: return 1
        else:
            if int(x[0]) < int(y[0]):
                return -1
            else: return 1
        return 0

    ans.sort(key=functools.cmp_to_key(my_compare))

    return ans


#print(calculateRSV(["元","行", "一"], ["0","1","2","3","4","5"]))







