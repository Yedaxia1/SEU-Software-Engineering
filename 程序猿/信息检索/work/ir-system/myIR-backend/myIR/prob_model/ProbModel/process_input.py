from boolean_model.BooleanModel.logic_process import multi_or_ops
from django.conf import settings

def process_input(query_str):
    d = settings.DICTIONARY
    term_list = []
    d_lists = []
    for term in query_str:
        if term == ' ':
            continue
        d_lists.append(list(d[term]['tf'].keys()))
        term_list.append(term)
    doc_list = multi_or_ops(d_lists)
    return term_list, doc_list