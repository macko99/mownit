import matplotlib.pyplot as plt
import csv

file = "results/results_"
fileNames = ["f1", "f2"]
extension = ".txt"
path = "plots/"
points = [5, 10, 20]
degrees = [4, 10]

for kind in fileNames:
    filename = file + kind
    for number in points:
        x = []
        y = []
        with open(filename + "_" + str(number) + extension,'r') as csvfile:
            plots = csv.reader(csvfile, delimiter=' ')
            for row in plots:
                x.append(float(row[0]))
                y.append(float(row[1]))

        for degree in degrees:
            approximationX = []
            approximationY = []
            with open(filename + "P_" + str(number) + "_" + str(degree) + extension,'r') as csvfile:
                plots = csv.reader(csvfile, delimiter=' ')
                for row in plots:
                    approximationX.append(float(row[0]))
                    approximationY.append(float(row[1]))

            print('.', end='', flush=True)
            plt.clf()
            plt.plot(x, y)
            plt.plot(approximationX, approximationY)
            plt.title(str(kind) + ": " + str(number) + " deg: " + str(degree))
            plt.ylabel('y')
            plt.xlabel('x')

            plt.savefig(path + str(kind) + "_" + str(number) + "_deg" + str(degree) + ".png")

