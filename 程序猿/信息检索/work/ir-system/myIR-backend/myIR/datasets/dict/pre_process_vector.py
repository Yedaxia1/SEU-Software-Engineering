
import json

dictory_vector = dict()
# title_dict = dict()
# author_dict = dict()
# content_dict = dict()


# {
#     '1': {
#         'Length' : 3,
#         'max_freq' : {
#             "term" : ["马"],
#             "freq" : 2
#         },
#         'tf' : {
#             "行" : 1,
#             "马" : 2
#         }
#     }
# }

for i in range(0, 320):
    with open("../{}.txt".format(i), "r", encoding='UTF-8') as f:
        dictory_vector[i] = {
                    'Length' : 0,
                    'max_freq' : {
                        "term" : [],
                        "freq" : 0 
                    },
                    'tf' : {
                    }
                }
        lines = f.readlines()
        for line in lines[:3]:
            for ch in line:
                if ch == '\r\n' or ch == '，' or ch == '/' or ch == '。' or ch == '（' or ch == '）' or ch == '〔' or ch == '〕' or ch == ' ' or ch == '\n':
                    continue
                dictory_vector[i]['Length'] += 1
                if ch not in dictory_vector[i]['tf'].keys():
                    dictory_vector[i]['tf'][ch] = 0
                dictory_vector[i]['tf'][ch] += 1
                if dictory_vector[i]['tf'][ch] > dictory_vector[i]['max_freq']['freq']:
                    dictory_vector[i]['max_freq']['term'].clear()
                    dictory_vector[i]['max_freq']['term'].append(ch)
                    dictory_vector[i]['max_freq']['freq'] = dictory_vector[i]['tf'][ch] 
                elif dictory_vector[i]['tf'][ch] == dictory_vector[i]['max_freq']['freq']:
                    dictory_vector[i]['max_freq']['term'].append(ch)
                

with open("dictory_vector.json", "w+", encoding='UTF-8') as jsonFile:
    jsonFile.write(json.dumps(dictory_vector, indent = 4))

# with open("./dictory/title_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(title_dict, indent = 4))

# with open("./dictory/author_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(author_dict, indent = 4))

# with open("./dictory/content_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(content_dict, indent = 4))



