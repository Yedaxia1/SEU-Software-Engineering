from django.http import HttpResponse
import json
from myIR.common.read_data import read_data
from .ProbModel.process_input import process_input
from .ProbModel.getRSV import calculateRSV
from .ProbModel.calculateProb import calculateProb_MLE

# Create your views here.
def bim_query(request):
    respond = {
        'code': 200,
        'msg': '',
        'data': []
    }
    if request.method == 'GET' and request.GET:
        query_str = request.GET.get('query')
        try:
            term_list, doc_list = process_input(query_str)
            scores = calculateRSV(term_list, doc_list)
        except KeyError:
            respond['code'] = 400
            respond['msg'] = '抱歉，查询中有字典不包含的字符'
            return HttpResponse(json.dumps(respond, ensure_ascii=False))
        respond['data'] = read_data(scores)
        total = len(scores)
        respond['msg'] = '共查询到%d篇文档' % total
        return HttpResponse(json.dumps(respond, ensure_ascii=False))
    else:
        respond['code'] = 400
        respond['msg'] = '请求方法错误!'
        return HttpResponse(json.dumps(respond, ensure_ascii=False))

def mle_query(request):
    respond = {
        'code': 200,
        'msg': '',
        'data': []
    }
    if request.method == 'GET' and request.GET:
        query_str = request.GET.get('query')
        lam = float(request.GET.get('lambda'))
        try:
            term_list, doc_list = process_input(query_str)
            scores = calculateProb_MLE(term_list, doc_list, lam)
        except KeyError:
            respond['code'] = 400
            respond['msg'] = '抱歉，查询中有字典不包含的字符'
            return HttpResponse(json.dumps(respond, ensure_ascii=False))
        respond['data'] = read_data(scores)
        total = len(scores)
        respond['msg'] = '共查询到%d篇文档' % total
        return HttpResponse(json.dumps(respond, ensure_ascii=False))
    else:
        respond['code'] = 400
        respond['msg'] = '请求方法错误!'
        return HttpResponse(json.dumps(respond, ensure_ascii=False))
