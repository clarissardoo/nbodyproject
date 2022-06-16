import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import math


#Read File - this file only contains positions from first and last step

df=pd.read_csv('particles_128_1e6.csv',  skiprows = [0, -1], sep=',',header=None)

vals = df.values


plt.rcParams["font.family"] = "sans-serif"


#get Sun's position in case there is an offset
for i in range(len(vals)):
	if vals[i][1] == 0:
		sun_pos = np.sqrt((vals[i][3]**2 + vals[i][4]**2))


#Obtain Asteorid Positions at t = 2 Myr
r_list = []
for i in range(len(vals)):
	if vals[i][2] != 0:
		r = np.sqrt((vals[i][3]**2 + vals[i][4]**2)) - sun_pos
		r_list.append(r)


#Obtain Asteroid Positions at t = 0 
r_list_0 = []
for i in range(len(vals)):
	if vals[i][2] == 0:
		r = np.sqrt((vals[i][3]**2 + vals[i][4]**2)) 
		r_list_0.append(r)


# Filter for asteroids that were not ejected 

r_list_new = [r_list for r_list in r_list if 2.1 <= r_list <= 3.5]

r_list_0_new = [r_list_0 for r_list_0 in r_list_0 if 2.1 <= r_list_0 <= 3.5]

#plot histogram and resonances

fig, ax = plt.subplots()

#ax.hist(r_list_0_new, bins = 60, label = 't = 0', color = 'salmon')
ax.hist(r_list_new, bins = 85, label = 't = 2 Myr', color = 'salmon')
ax.axvline(x=2.52, label = "3:1", color = 'red')
ax.axvline(x=2.823, label = "5:2", color = 'deeppink')
ax.axvline(x=2.956, label = "7:3", color='purple')
ax.axvline(x=3.276, label = "2:1", color = 'darkgreen')


ax.set_ylabel('Number of asteroids')
ax.set_xlabel('Semi-Major Axis')
ax.set_title('Asteroid Distribution')
ax.legend()
#ax.set_xscale('log')
plt.show()