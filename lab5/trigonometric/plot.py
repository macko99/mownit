import matplotlib.pyplot as plt
import numpy as np
import csv

def helper(x, coeffCOS, coeffSIN):
    result = coeffCOS[0] / 2
    for i in range(1, len(coeffCOS)):
        result += (coeffCOS[i]*np.cos(i*x) +  coeffSIN[i]*np.sin(i*x))
    return result

start = 0
stop = 6
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
            with open(data + kind + "P_" + str(number) + "_" + str(degree) + "_COS" + extension,'r') as csvfile:
                coeffsCOS = csvfile.readlines()
                coeffsCOS = [float(str(i[:-1])) for i in coeffsCOS]
            with open(data + kind + "P_" + str(number) + "_" + str(degree) + "_SIN" + extension,'r') as csvfile:
                coeffsSIN = csvfile.readlines()
                coeffsSIN = [float(str(i[:-1])) for i in coeffsSIN]
            for item in approximationX:
                approximationY.append(helper(item, coeffsCOS, coeffsSIN))

            print('.', end='', flush=True)
            plt.clf()

            plt.plot(originX, originY)
            plt.scatter(x, y)
            plt.plot(approximationX, approximationY)

            plt.title(str(kind) + "| points: " + str(number) + " deg: " + str(degree))
            plt.ylabel('y')
            plt.xlabel('x')
            plt.savefig(path + str(kind) + "_" + str(number) + "_deg" + str(degree) + ".png")
