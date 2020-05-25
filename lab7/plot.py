import matplotlib.pyplot as plt
import numpy as np
import csv
import math

functions = ["linear", "quadratic", "cubic", "exponential", "sinusoidal"]
realResult = [200, 2920.0/3, 3050, pow(math.e, 10) - 1, pow(math.sin(10), 2)/2]
methods = ["rectangle", "trapezium", "simpson", "monteCarlo"]
inPath = "results/"
extension = ".txt"
outPath = "plots/"

i = 0

for function in functions:
    X = []
    Y1 = []
    Y2 = []
    Y3 = []
    Y4 = []
    with open(inPath + function + "_rectangle" + extension, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
            X.append(float(row[0]))
            Y1.append(float(row[1]))
    with open(inPath + function + "_trapezium" + extension, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
            Y2.append(float(row[1]))
    with open(inPath + function + "_simpson" + extension, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
            Y3.append(float(row[1]))
    with open(inPath + function + "_monteCarlo" + extension, 'r') as csvfile:
        plots = csv.reader(csvfile, delimiter=' ')
        for row in plots:
            Y4.append(float(row[1]))

    print('.', end='', flush=True)
    plt.clf()

    value = [realResult[i]]*len(X)
    i += 1

    line1 = plt.scatter(X, Y1, label="rectangle")
    line2 = plt.scatter(X, Y2, label="trapezium")
    line3 = plt.scatter(X, Y3, label="simpson")
    line4 = plt.scatter(X, Y4, label="monteCarlo")
    line5 = plt.plot(X, value, label ="real")
    plt.legend(handles=[line1, line2, line3, line4])

    plt.title("functions: " + function)
    plt.xlabel('iterations')
    plt.savefig(outPath + function + ".png")

X = []
Y = []

with open(inPath + "PI_monteCarlo" + extension, 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=' ')
    for row in plots:
        X.append(float(row[0]))
        Y.append(float(row[1]))

    value = [math.pi]*len(X)
    print('.', end='', flush=True)
    plt.clf()
    plt.scatter(X, Y)
    plt.plot(X, value)

    plt.title("PI - Monte Carlo Method")
    plt.xlabel('iterations')
    plt.savefig(outPath + "PI" + ".png")
