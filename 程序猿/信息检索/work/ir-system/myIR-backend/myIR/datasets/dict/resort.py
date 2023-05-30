import json
import functools

with open('dictory.json', 'r') as f:
    d = dict(json.load(f))
    for key in d.keys():
        d[key]['tf'] = dict(sorted(d[key]['tf'].items(), key=functools.cmp_to_key(lambda o1, o2: int(o1[0]) - int(o2[0]) if o1[1] == o2[1] else o1[1] - o2[1]), reverse=True))
    with open('resort_dict.json', 'w', encoding='UTF-8') as w:
        json.dump(d, w, indent=4)
        w.close()
    f.close()

