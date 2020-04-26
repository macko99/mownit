import matplotlib.pyplot as plt
import numpy as np
import csv

start = 0
stop = 10
density = 1000

data = "results/results_"
extension = ".txt"
path = "plots/"

points = [5, 10, 20, 50, 100]
degrees = [4, 7, 10, 20]
fileNames = ["f1", "f2"]

for kind in fileNames:
    if kind == "f1":
        originX = np.linspace(start, stop, num=density)
        originY = np.exp(np.cos(originX))
    if kind == "f2":
        originX = np.linspace(start, stop, num=density)
        originY = np.sin(originX) * np.exp(-originX/np.pi)
    for number in points:
        x = []
        y = []
        with open(data + kind + "_" + str(number) + extension,'r') as csvfile:
            plots = csv.reader(csvfile, delimiter=' ')
            for row in plots:
                x.append(float(row[0]))
                y.append(float(row[1]))

        for degree in degrees:
            approximationX = np.linspace(start, stop, num=density)
            approximationY = []
            with open(data + kind + "P_" + str(number) + "_" + str(degree) + extension,'r') as csvfile:
                coeffs = csvfile.readlines()
                coeffs = [float(str(i[:-1])) for i in coeffs]
                coeffs.reverse()
            p = np.poly1d(coeffs)
            for i in range(density):
                approximationY.append(p(approximationX[i]))

            print('.', end='', flush=True)
            plt.clf()

            plt.plot(originX, originY)
            plt.scatter(x, y)
            plt.plot(approximationX, approximationY)

            plt.title(str(kind) + "| points: " + str(number) + " deg: " + str(degree))
            plt.ylabel('y')
            plt.xlabel('x')
            plt.savefig(path + str(kind) + "_" + str(number) + "_deg" + str(degree) + ".png")

