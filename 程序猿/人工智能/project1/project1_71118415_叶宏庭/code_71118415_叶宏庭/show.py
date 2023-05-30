
# -*- coding: utf-8 -*-
import matplotlib.pyplot as plt
 
name_list = ['DecideTree','MLP','SVM']
num_list = [0.86470, 0.81601, 0.86013]
plt.bar(range(len(num_list)), num_list,color='rgb',tick_label=name_list)
plt.title("Wine", y=-0.15)
plt.show()