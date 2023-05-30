from django.conf import settings

def read_data(scores):
    ret = []
    for doc in scores:
        with open('%s/datasets/%s.txt' % (settings.BASE_DIR, doc[0]), 'r', encoding='utf-8') as f:
            lines = f.readlines()
            d = {'title': lines[0].strip(), 'author': lines[1].strip(), 'body': lines[2].strip(),
                 'url': lines[3].strip(), 'score': doc[1]}
            ret.append(d)
            f.close()
    return ret
