from sklearn import datasets
import sklearn.tree as st
import sklearn.metrics as sm
from sklearn.model_selection import cross_validate
import numpy as np
from sklearn.neural_network import MLPClassifier
import sklearn.svm as svm

# iris：鸢尾花数据集：--> 用于分类
# 有150个数据集，共分为3类，每类50个样本。每个样本有4个特征。

# 加载数据集
digits = datasets.load_digits()  # 加载iris数据集

x, y = digits.data, digits.target
l = np.ndarray(10)
l = [0]*10
for i in y:
    l[i] += 1
print(l)