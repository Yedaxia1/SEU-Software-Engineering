
import sklearn.tree as st
from dataloader import dataload
import sklearn.metrics as sm
from sklearn.model_selection import cross_validate
import numpy as np
# 创建决策树回归器模型  决策树的最大深度为7
model = st.DecisionTreeClassifier(max_depth=7)
# 训练模型
# train_x： 二维数组样本数据
# train_y： 训练集中对应每行样本的结果
x, y = dataload()
scores = cross_validate(model, x, y, cv=10)
# print(scores.keys())
print("Average score = ", np.mean(scores['test_score']))

'''

train_x, train_y, test_x, test_y = dataload()

model.fit(train_x, train_y)
# 测试模型
pred_test_y = model.predict(test_x)

# print(pred_test_y)
# print(test_y)

right = 0
sums = len(pred_test_y)
acc = 0.0

for i in range(pred_test_y.size):
    if pred_test_y[i] == test_y[i]:
        right += 1

print("right num = "+ str(right))
print("sums num = "+ str(sums))
print("acc rate = "+ str((float)(right/sums)))

bg = sm.classification_report(test_y, pred_test_y)
print('分类报告：', bg, sep='\n')
'''