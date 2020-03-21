import matplotlib.pyplot as plt
import numpy as np
import csv

x = []
y = []

with open('results.txt','r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        x.append(int(row[0])/25000)
        y.append(float(row[1]))

plt.plot(x,y)
plt.title('relative error')
plt.ylabel('%')
plt.xlabel('*25000')

plt.show()