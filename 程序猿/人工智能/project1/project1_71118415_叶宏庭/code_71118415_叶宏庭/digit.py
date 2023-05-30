from sklearn import datasets
import sklearn.tree as st
import sklearn.metrics as sm
from sklearn.model_selection import cross_validate
import numpy as np
from sklearn.neural_network import MLPClassifier
import sklearn.svm as svm

# Digits：Digits数据集：--> 用于分类
# 有1797个数据集，共分10类，每类约180个样本。每个样本有64个特征。

# 加载数据集
digits = datasets.load_digits()  # 加载Digits数据集

x, y = digits.data, digits.target


# print("iris data :\n ",iris.data) # 样本数据（150,4）
# print("iris traget :\n ",iris.target) # 每隔样本对应的标签（150,1）

# 创建决策树回归器模型  决策树的最大深度为4
model = st.DecisionTreeClassifier(max_depth=65)
# 训练模型
# train_x： 二维数组样本数据
# train_y： 训练集中对应每行样本的结果
scores1 = cross_validate(model, x, y, cv=10)
# print(scores.keys())
# print("(DecideTree) Average score = ", np.mean(scores1['test_score']))



mpl = MLPClassifier(hidden_layer_sizes=(128, 64), solver='lbfgs',activation='logistic')
scores2 = cross_validate(mpl, x, y, cv=10)

# print("(MLP) Average score = ", np.mean(scores2['test_score']))



model = svm.SVC(kernel='rbf', C=600)

scores3 = cross_validate(model, x, y, cv=10)
# print(scores.keys())
# print("(SVM) Average score = ", np.mean(scores3['test_score']))

print("DecideTree Average accuracy = ", np.mean(scores1['test_score']))
print("MLP Average accuracy = ", np.mean(scores2['test_score']))
print("SVM Average accuracy = ", np.mean(scores3['test_score']))