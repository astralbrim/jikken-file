import subprocess as sub
import matplotlib.pyplot as plt
from  mpl_toolkits.mplot3d import Axes3D
import numpy as np

comand = result = ''
fig = plt.figure()
ax = fig.gca(projection='3d')
x = np.arange(100)
y = np.arange(100)
x, y = np.meshgrid(x, y)
z = np.empty((100,100), float)
for xi in range(100):
    for yi in range(100):
        command = './simrecog 18317 {} {}'.format(float(xi), float(yi))
        result = sub.run(command, shell = True, stdout = sub.PIPE, check = True).stdout
        result = result.decode('utf-8').split(" ")
        result = float(result[-1])
        z[xi][yi] = result

ax.set_xlabel('alpha')
ax.set_ylabel('beta')
ax.set_zlabel('Recognition accuracy')
# ax.plot_surface(x, y, z, rstride=1, cmap='hsv', linewidth=0.3)
ax.plot_wireframe(x, y, z, color='red', linewidth=0.3)
plt.show()

