from sklearn.datasets import load_iris
from sklearn.svm import LinearSVC
from sklearn.feature_selection import RFECV
def test_RFECV():
    '''
    test the method of RFECV
    :return:  None
    '''
    iris=load_iris()
    X=iris.data
    y=iris.target
    estimator=LinearSVC()
    selector=RFECV(estimator=estimator,cv=3)
    selector.fit(X,y)
    print("N_features %s"%selector.n_features_)
    print("Support is %s"%selector.support_)
    print("Ranking %s"%selector.ranking_)
    print("Grid Scores %s"%selector.grid_scores_)

test_RFECV()