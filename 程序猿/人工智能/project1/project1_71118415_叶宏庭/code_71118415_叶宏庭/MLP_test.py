# test part

import numpy as np
from sklearn.neural_network import MLPClassifier
from joblib import load
from dataloader import dataload
import sklearn.metrics as sm

train_x, train_y, test_x, test_y = dataload()

clf = load("MLP_model.m")
y_pred = clf.predict(test_x)

# np.savetxt("label_pred.txt", np.array(y_pred)) #save predict result
# print(y_pred)
test_score = clf.score(test_x, test_y)
test_error = 1 - test_score
print('test_score：%s' % test_score)
print('test_error：%s' % test_error)

bg = sm.classification_report(test_y, y_pred)
print('分类报告：', bg, sep='\n')