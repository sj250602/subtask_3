import matplotlib.pyplot as plt
import numpy as np

queue =[]
dynamic = []
frame = []

queue1 =[]
dynamic1 = []
frame1 = []

aa = input("Enter the file: ")
f = open(aa, "r")
g = open("3.txt", "r")
for x in f:
  x1 = x.split("\t")
  dyn = float(x1[2])
  dynamic.append(dyn)
  qu = float(x1[1])
  queue.append(qu)
  tm = float(x1[0])
  frame.append(tm)

for x in g:
  x1 = x.split("\t")
  dyn = float(x1[2])
  dynamic1.append(dyn)
  qu = float(x1[1])
  queue1.append(qu)
  tm = float(x1[0])
  frame1.append(tm)
  
qued = []
k = 0
for i in range(len(frame1)):
    j = frame1[i]
    m1 = np.interp(j,frame,queue)
    m2 = np.interp(j,frame1,queue1)
    qued.append(abs(m1-m2))
    k += abs(m1-m2)
    
for i in range(len(frame1)):
    j = frame1[i]
    m1 = np.interp(j,frame,dynamic)
    m2 = np.interp(j,frame1,dynamic1)
    qued.append(abs(m1-m2))
    k += abs(m1-m2)
print("Utility: ",k/len(frame1))    
 

#plt.plot( frame , queue , label = "Queue density",color='b')

#plt.plot( frame , dynamic , label = "Dynamic density",color='g')

#plt.xlabel('time(in seconds)')

#plt.ylabel('density')

#plt.title('Traffic Density Curve')

#plt.legend()

#plt.show()