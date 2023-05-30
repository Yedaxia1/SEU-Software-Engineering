from django.conf import settings
import functools
import json

def calculateProb_MLE(querys, doc_lists, define_lamda=0.5):
    origin_dict = settings.SORTED_DICTIONARY
    vector_dict = settings.DOC_VECTOR
    Total_len = settings.TOTAL_LENGTH_COLLECTION

    scores = []
    
    for doc_id in doc_lists:
        doc_score = 0.0

        for term in querys:
            doc_score += (1 - define_lamda) * (origin_dict[term]["cf"] / Total_len)
            if term in vector_dict[doc_id]["tf"].keys():
                doc_score += define_lamda * (vector_dict[doc_id]["tf"][term] / vector_dict[doc_id]["Length"])
        
        scores.append(doc_score)
    
    ans = []

    for i in range(len(doc_lists)):
        ans.append((doc_lists[i], scores[i]))

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

    # P_R_records = {
    #     "query": querys,
    #     "P_R_list": {

    #     },
    #     "col_sum":[0]*10
    # }

    # for term in querys:
    #     p_r_s = []
    #     index = 0
    #     for doc_id in origin_dict[term]["tf"].keys():
    #         if index==10:
    #             break
    #         p_r_rate = (ans.index((doc_id, scores[doc_lists.index(doc_id)])) + 1) / (index+1)
    #         p_r_s.append(p_r_rate)
    #         P_R_records['col_sum'][index] += p_r_rate
    #         index += 1
        
    #     P_R_records['P_R_list'][term] = p_r_s



    # with open("./query_{}.json".format(settings.QUERY_NUMBER), "w+", encoding='UTF-8') as jsonFile:
    #     jsonFile.write(json.dumps(P_R_records, indent = 4, ensure_ascii=False))
    
    # settings.QUERY_NUMBER += 1

    return ans

#print(calculateProb_MLE(["行"], ["0"]))



