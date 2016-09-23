import numpy as np
import matplotlib.pyplot as plt


cld = "PingPong-Large-Double-Node.4342248.comet-27-13.out"
cls = "PingPong-Large-Single-Node.4342220.comet-10-51.out"
csd = "PingPong-Small-Double-Node.4345654.comet-18-29.out"

sld = "PingPong-Large-Double-Node.7635285.c557-401.out"
sls = "PingPong-Large-Single-Node.7635263.c558-402.out"
ssd = "PingPong-Small-Double-Node.7635426.c557-502.out"

fname = "test.txt"
datacld= np.genfromtxt(cld,delimiter=",",usecols=(4,5),skip_header=2)
datacls= np.genfromtxt(cls,delimiter=",",usecols=(4,5),skip_header=2)
datacsd= np.genfromtxt(csd,delimiter=",",usecols=(4,5),skip_header=2)
datasld= np.genfromtxt(sld,delimiter=",",usecols=(4,5),skip_header=2)
datasls= np.genfromtxt(sls,delimiter=",",usecols=(4,5),skip_header=2)
datassd= np.genfromtxt(ssd,delimiter=",",usecols=(4,5),skip_header=2)

fig = plt.figure(figsize=(8,3))
datasls[:,1] = datasls[:,1] / ( 2 ** 10 )
datasls[:,0] = datasls[:,0] / ( 10 ** (-6) )
plt.plot(datasls[:,1],datasls[:,0])

plt.title("Stampede 2 Nodes 0kb - 4MB")
plt.xlabel('Message Size ( kb )')
plt.ylabel(r'Time ( $\mu s$ )')
plt.xlim((datasls[0,1],datasls[-1,1]))
plt.ticklabel_format(style='plain')
plt.xscale('log')
plt.yscale('log')

plt.savefig('sls.eps',bbox_inches='tight', dpi=300)
plt.show()
