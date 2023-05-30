

from load_dictory import load_dict, load_title_dict, load_author_dict, load_content_dict
from logic_process import _and, _or, _and_not, _multi_and, _multi_or


a = [1, 2, 3, 5, 7]
b = [2, 4, 6, 7]
c = [2, 4, 5]
d = [9, 10, 12]



print(_and(a, b))
print(_or(a, b))
print(_and_not(b, c))
print(_multi_and([a,b,c]))
print(_multi_or([a,b,c,d]))