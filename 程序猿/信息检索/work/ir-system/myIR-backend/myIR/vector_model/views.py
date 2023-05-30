from django.http import HttpResponse
import json
from .VectorModel.process_input import process_input
from .VectorModel.search import cosine_sim
from myIR.common.read_data import read_data

# Create your views here.
def query(request):
    respond = {
        'code': 200,
        'msg': '',
        'data': []
    }
    if request.method == 'GET' and request.GET:
        query_str = request.GET.get('query')
        query_tf_type = int(request.GET.get('queryTfType'))
        query_doc_type = int(request.GET.get('queryDocType'))
        doc_tf_type = int(request.GET.get('docTfType'))
        doc_doc_type = int(request.GET.get('docDocType'))
        doc_norm_type = int(request.GET.get('docNormType'))
        try:
            ret = cosine_sim(process_input(query_str), (query_tf_type, query_doc_type), (doc_tf_type, doc_doc_type, doc_norm_type))
        except KeyError:
            respond['code'] = 400
            respond['msg'] = '抱歉，查询中有字典不包含的字符'
            return HttpResponse(json.dumps(respond, ensure_ascii=False))

        respond['data'] = read_data(ret)

        total = len(ret)
        respond['msg'] = '得分前%d的文档为' % total
        return HttpResponse(json.dumps(respond, ensure_ascii=False))
    else:
        respond['code'] = 400
        respond['msg'] = '请求方法错误!'
        return HttpResponse(json.dumps(respond, ensure_ascii=False))
