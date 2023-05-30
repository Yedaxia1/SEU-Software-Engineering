
import json

dictory = dict()
# title_dict = dict()
# author_dict = dict()
# content_dict = dict()


# {
#     '字': {
#         'df' : 3,
#         'cf' : 5,
#         'tf' : {
#             0 : 1,
#             1 : 2
#         }
#     }
# }

for i in range(0, 320):
    with open("../{}.txt".format(i), "r", encoding='UTF-8') as f:
        lines = f.readlines()
        for line in lines:
            for ch in line:
                if ch == '\r\n' or ch == '，' or ch == '/' or ch == '。' or ch == '（' or ch == '）' or ch == '〔' or ch == '〕' or ch == ' ' or ch == '\n':
                    continue
                if ch not in dictory.keys():
                    dictory[ch] = {
                        'df' : 0,
                        'cf' : 0,
                        'tf' : {}
                    }
                dictory[ch]['cf'] += 1
                if i not in dictory[ch]['tf'].keys():
                    dictory[ch]['tf'][i] = 0
                dictory[ch]['tf'][i] += 1

for key in dictory.keys():
    dictory[key]['df'] = len(dictory[key]['tf'].keys())



with open("dictory.json", "w+", encoding='UTF-8') as jsonFile:
    jsonFile.write(json.dumps(dictory, indent = 4))

# with open("./dictory/title_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(title_dict, indent = 4))

# with open("./dictory/author_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(author_dict, indent = 4))

# with open("./dictory/content_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(content_dict, indent = 4))



