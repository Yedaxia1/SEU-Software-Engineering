
import json
import math

dictory_probablity = dict()
# title_dict = dict()
# author_dict = dict()
# content_dict = dict()

doc_tatal_num = 320

with open("./dictory.json", "r") as f:
    dictory = json.load(f) 

    for term in dictory.keys():
        if term == '\r\n' or term == '，' or term == '。' or term == '（' or term == '）' or term == '(' or term == ')' or term == ' ' or term == '\n' :
            continue
        if term == '唐' or term == '代':
            continue
        pi = dictory[term]["df"] / doc_tatal_num
        if pi==1:
            print(term) 
            break
        ri = 1 - pi
        ci = math.log((pi * (1 - ri)) / (ri * (1 - pi)), 2)
        dictory_probablity[term] = {
            "pi" : pi,
            "ri" : ri,
            "ci" : ci
        }


with open("dictory_probablity.json", "w+", encoding='UTF-8') as jsonFile:
    jsonFile.write(json.dumps(dictory_probablity, indent = 4))

# with open("./dictory/title_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(title_dict, indent = 4))

# with open("./dictory/author_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(author_dict, indent = 4))

# with open("./dictory/content_dict.json", "w+", encoding='UTF-8') as jsonFile:
#     jsonFile.write(json.dumps(content_dict, indent = 4))



