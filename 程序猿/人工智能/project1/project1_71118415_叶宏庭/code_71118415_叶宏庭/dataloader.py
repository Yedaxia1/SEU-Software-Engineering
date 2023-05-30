
from sklearn import preprocessing
import numpy as np
from sklearn.model_selection import train_test_split

def preprocess_car(data1, data2):
    tar = preprocessing.LabelEncoder().fit(['unacc', 'acc', 'good', 'vgood'])
    arr = preprocessing.OrdinalEncoder().fit([
        ['vhigh', 'vhigh', '2', '2', 'small', 'low'],
        ['high', 'high', '3', '4', 'med', 'med'],
        ['med', 'med', '4', 'more', 'big', 'high'],
        ['low', 'low', '5more', 'more', 'big', 'high']
    ])
    # print(tar.transform(['unacc', 'acc', 'good', 'vgood']))
    re_data1 = arr.transform(data1)
    re_data2 = tar.transform(data2).reshape([len(data1), 1])
    # print(re_data1[0:2])
    # print(re_data2[0:2])
    re_data = np.concatenate([re_data1, re_data2], axis=1)
    # print(re_data[1155:1165])
    # print(re_data[0:5])
    
    return re_data

def dataload():

    train_x = []
    train_y = []

    test_x = []
    test_y = []

    all_data1 = []
    all_data2 = []
    
    with open("./dataset/car_data.txt", "r", encoding='utf-8') as f:
        reader = f.readlines()
        # print(reader)
        for i in reader:
            i = i.replace("\n", "")
            
            arrs = i.split(",")

            all_data1.append(arrs[:-1])
            all_data2.append(arrs[-1])

    redata = preprocess_car(all_data1, all_data2)

    x = redata[:, :-1]
    y = redata[:, -1:]

    return x, y
    train_x, test_x, train_y, test_y = train_test_split(x, y, test_size = 0.1)

    # print(len(train_x), train_y)
    return train_x, train_y, test_x, test_y

# dataload()