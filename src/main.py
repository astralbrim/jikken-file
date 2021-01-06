import subprocess as sub
import matplotlib.pyplot as plt
from  mpl_toolkits.mplot3d import Axes3D
import numpy as np

comand = result = '' # Initializing

# Setting figure
fig = plt.figure()
ax = fig.gca(projection='3d')
x = np.arange(100)
y = np.arange(100)
x, y = np.meshgrid(x, y)
z = np.empty((100,100), float)
ax.set_xlabel('alpha')
ax.set_ylabel('beta')
ax.set_zlabel('Recognition accuracy')

# start simrecog
for xi in range(100):
    for yi in range(100):
        command = './simrecog 18317 {} {}'.format(float(xi), float(yi))
        result = sub.run(command, shell = True, stdout = sub.PIPE, check = True).stdout
        result = result.decode('utf-8').split(" ")
        result = float(result[-1])
        z[xi][yi] = result

# calculate coordinates from one-dimensional coordinates
max_index = z.argmax()
max_index_alpha = int(max_index / 100)
max_index_beta = max_index % 100
max_value = np.max(z)

# show 
print(f"MaxIndex:alpha {max_index_alpha}, beta {max_index_beta}")
print(f"Maxvalue:{max_value}")
ax.plot_wireframe(x, y, z, color='red', linewidth=0.3)
plt.show()

