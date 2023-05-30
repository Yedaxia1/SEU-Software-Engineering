def tokenized(input_query):
    res = []
    for c in input_query:
        if c != ' ':
            res.append(c)
    return res

# - == & > |
def infix_to_postfix(query):
    res = []
    ops = []
    word_list = []
    for token in query:
        if token == '&' or token == '-':
            if len(ops) != 0 and (ops[-1] == '&' or ops[-1] == '-'):
                res.append(ops.pop())
            ops.append(token)
        elif token == '|':
            if len(ops) != 0 and ops[-1] != '(':
                res.append(ops.pop())
            ops.append(token)
        elif token == '(':
            ops.append(token)
        elif token == ')':
            while ops[-1] != '(':
                res.append(ops.pop())
            ops.pop()
        else:
            res.append(token)
            word_list.append(token)
    
    while len(ops) != 0:
        res.append(ops.pop())
    
    return res, word_list

def process_input(query_str):
    return infix_to_postfix(tokenized(query_str))


# s = input()
# r, l = process_input(s)
# print(r)
# print(l)