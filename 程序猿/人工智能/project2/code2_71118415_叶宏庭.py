from sklearn import datasets
from sklearn import svm
from sklearn import preprocessing
from sklearn.feature_selection import RFECV
from sklearn.svm import LinearSVC
from sklearn.metrics import f1_score
from sklearn.metrics import make_scorer
import numpy as np

# 数据预处理
def preprocess_x(x):

    # 标准化(0-1)
    scaler = preprocessing.MinMaxScaler()
    data_standardized = scaler.fit_transform(x)
    
    return data_standardized

def preprocess_y(y):
    resu = []

    for i in y:
        resu.append(int(i))
    
    resu = np.array(resu)
    return resu


data_sa_heart = datasets.fetch_openml(name='sa-heart')
data_breast_tissue = datasets.fetch_openml(name='breast-tissue', version=2)
data_xd6 = datasets.fetch_openml(name='xd6')


data_sa_heart_x = preprocess_x(data_sa_heart.data)
data_sa_heart_y = preprocess_y(data_sa_heart.target.values)

data_breast_tissue_x = preprocess_x(data_breast_tissue.data)
data_breast_tissue_y = preprocess_y(data_breast_tissue.target.values)


data_xd6_x = preprocess_x(data_xd6.data)
data_xd6_y = preprocess_y(data_xd6.target.values)

sa_model = RFECV(LinearSVC(), step=1, scoring=make_scorer(f1_score))
sa_model = sa_model.fit(data_sa_heart_x, data_sa_heart_y)
print(f1_score(sa_model.predict(data_sa_heart_x), data_sa_heart_y))
print(sa_model.n_features_)
print(sa_model.support_)

breast_tissue_model = RFECV(LinearSVC(), step=1, scoring=make_scorer(f1_score, average='micro'))
breast_tissue_model = breast_tissue_model.fit(data_breast_tissue_x, data_breast_tissue_y)
print(f1_score(breast_tissue_model.predict(data_breast_tissue_x), data_breast_tissue_y, average='micro'))
print(breast_tissue_model.n_features_)
print(breast_tissue_model.support_)


data_xd6_model = RFECV(LinearSVC(), step=1, scoring=make_scorer(f1_score))
data_xd6_model = data_xd6_model.fit(data_xd6_x, data_xd6_y)
print(f1_score(data_xd6_model.predict(data_xd6_x), data_xd6_y))
print(data_xd6_model.n_features_)
print(data_xd6_model.support_)




