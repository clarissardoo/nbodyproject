import numpy as np
import matplotlib.pyplot as plt

plt.rcParams["font.family"] = "sans-serif"


#number of threads and run times for each amount of asteroids

n_threads = [1,2,4,8,16,32,64,128]

runtime_1000 = [8.954605, 4.480795, 2.400092, 1.373767, 0.727884, 0.474097, 0.391812, 0.405466]
runtime_2000 = [34.639706, 17.603343, 9.033113, 4.694992, 2.669678, 1.495741, 1.086254, 0.855600]
runtime_4000 = [137.690521, 69.625912, 35.372987, 18.222042, 9.678435, 5.159627, 3.191541, 2.507792]
runtime_8000 = [556.101212, 277.940662,  138.483914,  68.982689, 34.595984, 17.325500, 8.709683, 4.958965]
runtime_16000 = [2208.996708, 1105.129325, 552.183203, 275.928927, 138.143407,  69.219804, 34.625291, 24.543617]


#obtain speedups for each asteroid amount

runtime_1000new =[]
for i in runtime_1000:
	runtime_1000new.append(runtime_1000[0]/i)

runtime_2000new =[]
for i in runtime_2000:
	runtime_2000new.append(runtime_2000[0]/i)

runtime_4000new =[]
for i in runtime_4000:
	runtime_4000new.append(runtime_4000[0]/i)

runtime_8000new =[]
for i in runtime_8000:
	runtime_8000new.append(runtime_8000[0]/i)

runtime_16000new =[]
for i in runtime_16000:
	runtime_16000new.append(runtime_16000[0]/i)

#plot speedups and times
fig, ax = plt.subplots()
ax.plot(n_threads, runtime_1000new, 'o-', label = '1000 asteroids', color = 'blue')
ax.plot(n_threads, runtime_2000new, 'o-', label = '2000 asteroids', color = 'red')
ax.plot(n_threads, runtime_4000new, 'o-', label = '4000 asteroids', color = 'darkgreen')
ax.plot(n_threads, runtime_8000new, 'o-', label = '8000 asteroids', color = 'deeppink')
ax.plot(n_threads, runtime_16000new, 'o-', label = '16000 asteroids', color = 'purple')
ax.set_ylabel('Speed Up')
ax.set_xlabel('Number of Threads')
ax.grid(True)
ax.set_title('N-Body Speed Up')
#ax.set_xscale('log')
ax.set_yscale('log')
ax.legend()
plt.show()




fig, ax = plt.subplots()
ax.plot(n_threads, runtime_1000, 'o-', label = '1000 asteroids', color = 'blue')
ax.plot(n_threads, runtime_2000, 'o-', label = '2000 asteroids', color = 'red')
ax.plot(n_threads,runtime_4000, 'o-', label = '4000 asteroids', color = 'darkgreen')
ax.plot(n_threads,runtime_8000, 'o-', label = '8000 asteroids', color = 'deeppink')
ax.plot(n_threads, runtime_16000, 'o-', label = '16000 asteroids', color = 'purple')

ax.set_ylabel('Average Run Time (seconds)')
ax.set_xlabel('Number of Threads')
ax.grid(True)
ax.set_title('N-Body Run Time')
ax.set_yscale('log')
ax.legend()
plt.show()



# Plot Quadratic Fit for number of Asteroids

n_asteroids = np.array([1000, 2000, 4000, 8000, 16000])
asteroids_range = np.arange(500, 20000)

times_128 = np.array([0.405466, 0.855600, 2.507792, 4.958965, 24.543617])
times_1 = np.array([8.954605, 34.639706, 137.690521, 514.71, 2208.996708])

a, b, c = np.polyfit(n_asteroids, times_128, 2)
a_s, b_s, c_s = np.polyfit(n_asteroids, times_1, 2)


def poly(x, a,b,c):
	y = a*x**2 + b*x + c
	return y


fig, ax = plt.subplots()

ax.plot(n_asteroids, times_1, 'o', label = 'Time for 1 Core', color = 'darkgreen')
ax.plot(n_asteroids, times_128, 'o', label = 'Time for 128 Cores', color = 'deeppink')
ax.plot(asteroids_range, poly(asteroids_range,a,b,c), '-', label = 'Quadratic fit, 128', color = 'pink')
ax.plot(asteroids_range, poly(asteroids_range,a_s,b_s,c_s), '-', label = 'Quadratic fit, 1', color = 'lime')


ax.set_xlabel('Number of Asteroids')
ax.set_ylabel('Time (s)')

ax.legend() 
plt.show()