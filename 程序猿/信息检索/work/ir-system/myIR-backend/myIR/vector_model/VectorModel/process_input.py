# query dict
def process_input(query_str):
    res = {
        'Length': 0,
        'max_freq': {
            'term': [],
            'freq': 0
        },
        'tf': {}
    }
    for c in query_str:
        if c == ' ':
            continue
        res['tf'][c] = res['tf'].get(c, 0) + 1
        res['Length'] += 1
        res['max_freq']['freq'] = max(res['max_freq']['freq'], res['tf'][c])
    return res
