

import functools

def trans_str2int(list1, list2):
    list_1 = []
    list_2 = []
    for docID in list1:
        list_1.append(int(docID))
    for docID in list2:
        list_2.append(int(docID))
    
    return list_1, list_2

def trans_int2str(lists):
    _list = []
    for docID in lists:
        _list.append(str(docID))
    
    return _list



def and_ops(list1, list2):
    list1, list2 = trans_str2int(list1, list2)
    index_1 = 0
    index_2 = 0
    ans = []
    while(index_1 < len(list1) and index_2 < len(list2)):
        if(list1[index_1] == list2[index_2]):
            ans.append(list1[index_1])
            index_1 += 1
            index_2 += 1
        elif list1[index_1] < list2[index_2]:
            index_1 += 1
        else: index_2 += 1

    return trans_int2str(ans)



def or_ops(list1, list2):
    list1, list2 = trans_str2int(list1, list2)
    index_1 = 0
    index_2 = 0
    ans = []
    while(index_1 < len(list1) and index_2 < len(list2)):
        if(list1[index_1] == list2[index_2]):
            ans.append(list1[index_1])
            index_1 += 1
            index_2 += 1
        elif list1[index_1] < list2[index_2]:
            ans.append(list1[index_1])
            index_1 += 1
        else:
            ans.append(list2[index_2])
            index_2 += 1
    if index_1==len(list1) and index_2 == len(list2):
        return trans_int2str(ans)
    
    if index_1==len(list1):
        for docID in list2[index_2:]:
            ans.append(docID)
        return trans_int2str(ans)
    
    if index_2==len(list2):
        for docID in list1[index_1:]:
            ans.append(docID)
        return trans_int2str(ans)

def and_not_ops(list1, list2):
    list1, list2 = trans_str2int(list1, list2)
    index_1 = 0
    index_2 = 0
    ans = []
    while(index_1 < len(list1) and index_2 < len(list2)):
        if(list1[index_1] == list2[index_2]):
            index_1 += 1
            index_2 += 1
        elif list1[index_1] < list2[index_2]:
            ans.append(list1[index_1])
            index_1 += 1
        else:
            index_2 += 1

    if index_2 == len(list2) and index_1 != len(list1):
        for docID in list1[index_1:]:
            ans.append(docID)

    return trans_int2str(ans)


def compare(x, y):
    if len(x) < len(y):
        return -1
    else: return 1


def multi_and_ops(lists):
    lists.sort(key = functools.cmp_to_key(compare))
    ans = lists[0]

    for i in range(1, len(lists)):
        ans = and_ops(ans, lists[i])
    
    return ans

def multi_or_ops(lists):
    lists.sort(key = functools.cmp_to_key(compare), reverse = True)
    ans = lists[0]

    for i in range(1, len(lists)):
        ans = or_ops(ans, lists[i])
    
    return ans










