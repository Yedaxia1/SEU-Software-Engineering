from django.shortcuts import render

# Create your views here.
from django.conf import settings
from django.http import HttpResponse
import json
from .BooleanModel import process_input
from .BooleanModel.logic_process import *
from .BooleanModel.scores_calculate import get_score
from myIR.common.read_data import read_data

def query(request):
    dic = settings.DICTIONARY
    respond = {
        'code': 200,
        'msg': '',
        'data': []
    }
    if request.method == 'GET' and request.GET:
        query_str = request.GET.get('query')
        query_type = int(request.GET.get('type')) # 0 tf_idf, 1 wf_idf
        post_exp, word_list = process_input.process_input(query_str)
        stack = []
        for item in post_exp:
            if item == '&':
                l1 = stack.pop()
                l2 = stack.pop()
                res = and_ops(l1, l2)
                stack.append(res)
            elif item == '|':
                l1 = stack.pop()
                l2 = stack.pop()
                res = or_ops(l1, l2)
                stack.append(res)
            elif item == '-':
                l1 = stack.pop()
                l2 = stack.pop()
                res = and_not_ops(l1, l2)
                stack.append(res)
            else:
                try:
                    l = dic[item]['tf'].keys()
                    stack.append(l)
                except KeyError:
                    respond['code'] = 400
                    respond['msg'] = '抱歉，查询中有字典不包含的字符'
                    return HttpResponse(json.dumps(respond, ensure_ascii=False))

        res = stack.pop()
        rank = []
        for doc_id in res:
            score = get_score(word_list, doc_id, query_type)
            rank.append((doc_id, score))

        rank.sort(key=lambda a: a[1], reverse=True)

        respond['data'] = read_data(rank)

        total = len(rank)
        if total == 0:
            respond['msg'] = '无结果'
        else:
            respond['msg'] = '共查询到%d条结果' % total
        return HttpResponse(json.dumps(respond, ensure_ascii=False))
    else:
        respond['code'] = 400
        respond['msg'] = '请求方法错误!'
        return HttpResponse(json.dumps(respond, ensure_ascii=False))


