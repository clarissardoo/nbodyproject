import numpy as np
from rebound.interruptible_pool import InterruptiblePool
import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
import time
from orbitize import results
import math
import itertools as it
import imageio


#df=pd.read_csv('particles.csv', skiprows = [0], sep=',',header=None) - for parallel version of code

#READ DATA
df=pd.read_csv('particles.csv', sep=',',header=None) # for serial version of code

vals = df.values


#CREATE X AND Y LISTS FOR EACH BODY
g = globals()
n_bodies = 5
for i in range(n_bodies):
   g['x_pos_body{0}'.format(i+1)] = []
   g['y_pos_body{0}'.format(i+1)] = []


#POPULATE LIST
for i in range(n_bodies):  
   for j in range(int(len(vals))):
      if vals[j][1] == i:
         print(vals[j])
         g['x_pos_body{0}'.format(i+1)].append(vals[j][3])
         g['y_pos_body{0}'.format(i+1)].append(vals[j][4])




print('plotting now')

#PLOT ALL BODIES
for i in range(len(x_pos_body1)):
   fig = plt.figure()

   #INNER SOLAR SYSTEM
   plt.plot(x_pos_body1[i],y_pos_body1[i], 'o', label ='Sun', color = 'gold')
   plt.plot(x_pos_body2[i],y_pos_body2[i], 'o', label = 'Mercury', color = 'gray')
   plt.plot(x_pos_body3[i],y_pos_body3[i], 'o', label ='Venus', color = 'darkorange')
   plt.plot(x_pos_body4[i],y_pos_body4[i], 'o', label ='Earth', color = 'skyblue')
   plt.plot(x_pos_body5[i],y_pos_body5[i], 'o', label ='Mars', color = 'firebrick')

   # OUTER SOLAR SYSTEM

  # plt.plot(x_pos_body6[i],y_pos_body6[i], 'o', label ='Jupiter', color = 'orange')
   #plt.plot(x_pos_body2[i],y_pos_body2[i], 'o', label ='Jupiter', color = 'orange')
   #plt.plot(x_pos_body3[i],y_pos_body3[i], 'o', label ='Saturn', color = 'tan')
   #plt.plot(x_pos_body4[i],y_pos_body4[i], 'o', label ='Uranus', color = 'paleturquoise')
  # plt.plot(x_pos_body5[i],y_pos_body5[i], 'o', label ='Neptune', color = 'dodgerblue')

  # ASTEROIDS
  # for j in range(1,n_bodies):
   #   plt.plot(g['x_pos_body{0}'.format(j)][i],g['y_pos_body{0}'.format(j)][i], '.', color = 'black')



   #SET LIMIT IN AU
   plt.xlim(-3, +3)
   plt.ylim(-3, +3)
   plt.title('Timestep = ' + str(0.01*i) + 'years')
   #plt.axis('equal')
   plt.xlabel('x [AU]')
   plt.ylabel('y [AU]')
  # plt.xscale('log')
  # plt.yscale('log')
   plt.legend()
   #plt.show()
   plt.savefig('timestep_new'+str(i)+'.png')

#CREATE GIF ANIMATION

rhos_list =[]
for i in range(len(x_pos_body1)):
   rhos_list.append('timestep_new'+str(i)+'.png')

with imageio.get_writer('solarsystem_inner.gif', mode='I') as writer:
    for filename in rhos_list:
        image = imageio.imread(filename)
        writer.append_data(image)

