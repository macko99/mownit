import matplotlib.pyplot as plt
import numpy as np
import csv

filename = "results/results"
extension = ".txt"
path = "plots/"
points = [2,3,5,7,10,12,15,20,30,40]
x = []
y = []

with open(filename + extension,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=' ')
    for row in plots:
        x.append(float(row[0]))
        y.append(float(row[1]))

for number in points:
    print('.', end='', flush=True)
    for kind in ["L", "LC", "N", "NC", "H", "HC"]:
        interpolationX = []
        interpolationY = []
        with open(filename + str(kind) + str(number) + extension,'r') as csvfile:
            plots = csv.reader(csvfile, delimiter=' ')
            for row in plots:
                interpolationX.append(float(row[0]))
                interpolationY.append(float(row[1]))
                
        plt.clf()
        plt.plot(x,y)
        plt.plot(interpolationX, interpolationY)
        plt.title(str(kind) + str(number))
        plt.ylabel('y')
        plt.xlabel('x')

        plt.savefig(path + str(kind) + str(number)+ ".png")
