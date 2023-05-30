
from sklearn.neural_network import MLPClassifier
import numpy as np
from dataloader import dataload
from joblib import dump
from sklearn.model_selection import cross_validate

mpl = MLPClassifier(hidden_layer_sizes=(35, 20), solver='lbfgs',activation='logistic')

x, y = dataload()
scores = cross_validate(mpl, x, y, cv=10)
# print(scores.keys())
print(scores['test_score'])
print("Average score = ", np.mean(scores['test_score']))

'''
mpl.fit(train_x, train_y)
print(mpl.predict(test_x))
print(test_y)
print('Score:\n',mpl.score(test_x, test_y))
dump(mpl, "MLP_model.m")
'''