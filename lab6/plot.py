import matplotlib.pyplot as plt
import numpy as np
import csv

iterations = "20"
it = 20
testCases = ["1", "2", "3", "4", "5"]
methods = ["J", "GS", "SOR"]
data = "results/"
extension = ".txt"
path = "plots/"

for testCase in testCases:
    X = [*range(1, it+1, 1)]
    originY = []
    with open(data + testCase + "_" + iterations + extension,'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
            originY.append(float(row[0]))
    originY = [sum(originY) / len(originY) ]*it

    for method in methods:
        Y = []
        with open(data + method + "_" + testCase + "_" + iterations + extension,'r') as csvfile:
            plots = csv.reader(csvfile, delimiter=' ')
            for row in plots:
                Y.append(float(row[0]))

        print('.', end='', flush=True)
        plt.clf()

        plt.plot(X, originY)
        plt.scatter(X, Y)
        plt.xticks(np.arange(0, 21, step=2))
        plt.title("funkcja: " + testCase +  " | metoda: " + method)
        plt.xlabel('iterations')
        plt.savefig(path + method + "_" + testCase + "_" + iterations + ".png")
