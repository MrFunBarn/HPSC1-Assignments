import numpy as np
import matplotlib.pyplot as plt


#fname = "PingPong-Large-Double-Node.4342248.comet-27-13.out"
fname = "test.txt"
data = np.genfromtxt(fname,delimiter=",",usecols=(4,5),skip_header=2)


plt.plot(data[:,1],data[:,0])
plt.xscale('log')
plt.yscale('log')
plt.show()
