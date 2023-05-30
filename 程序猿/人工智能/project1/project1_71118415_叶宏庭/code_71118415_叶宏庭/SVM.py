
import numpy as np
import sklearn.model_selection as ms
import sklearn.svm as svm
import sklearn.metrics as sm
import matplotlib.pyplot as mp
from dataloader import dataload
from sklearn.model_selection import cross_validate

model = svm.SVC(kernel='rbf', C=600)

x, y = dataload()
scores = cross_validate(model, x, y, cv=10)
# print(scores.keys())
print(scores['test_score'])
print("Average score = ", np.mean(scores['test_score']))
'''
model.fit(train_x, train_y)

pred_test_y = model.predict(test_x)

bg = sm.classification_report(test_y, pred_test_y)
print('分类报告：', bg, sep='\n')
'''