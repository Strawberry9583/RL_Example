
import matplotlib.pyplot as plt
import matplotlib as mpl
import numpy as np
from matplotlib.font_manager import FontProperties
import matplotlib as mpl
mpl.rcParams['font.family'] = 'sans-serif'
mpl.rcParams['font.sans-serif'] = 'NSimSun,Times New Roman'
 
 
x, y = np.loadtxt('q_learning_cliff_walking.txt', delimiter='  ', unpack=True)
x=x[100:]
y=y[100:]
x1, y1 = np.loadtxt('sarsa_cliff_walking.txt', delimiter='  ', unpack=True)
x1=x1[100:]
y1=y1[100:]
plt.plot(x,y,'x',color='black')
plt.plot(x1,y1,'o',color='red')
 
plt.xlabel('episode')
plt.ylabel('return')
plt.show()
