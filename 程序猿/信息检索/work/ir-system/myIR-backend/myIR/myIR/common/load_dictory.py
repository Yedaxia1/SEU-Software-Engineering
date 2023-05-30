import json
from django.conf import settings
def load_dict():
    with open("%s/datasets/dict/dictory.json" % settings.BASE_DIR, "r") as f:
        return json.load(f)

def load_sorted_dict():
    with open("%s/datasets/dict/resort_dict.json" % settings.BASE_DIR, "r") as f:
        return json.load(f)

def load_dict_vector():
    with open("%s/datasets/dict/dictory_vector.json" % settings.BASE_DIR, "r") as f:
        return json.load(f)

def load_dict_probability():
    with open("%s/datasets/dict/dictory_probablity.json" % settings.BASE_DIR, "r") as f:
        return json.load(f)

# def load_title_dict():
#     with open("./dictory/title_dict.json", "r") as f:
#         return json.load(f)
#
# def load_content_dict():
#     with open("./dictory/content_dict.json", "r") as f:
#         return json.load(f)
#
# def load_author_dict():
#     with open("./dictory/author_dict.json", "r") as f:
#         return json.load(f)
