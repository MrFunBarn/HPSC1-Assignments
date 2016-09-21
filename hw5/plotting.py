import numpy as np
import matplotlib.pyplot as plt

data = np.genfromtxt("test.txt",delimiter=",",usecols=(4,5),skip_header=2)

plt.plot(data[:,1],data[:,0])
plt.show()
