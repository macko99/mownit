import matplotlib.pyplot as plt
import csv

frequency = []
spectrum = []

with open("frequencyData.txt", 'r') as file:
    lines = file.readlines()
    for line in lines:
        spectrum.append(float(line))

for i in range(len(spectrum)):
    frequency.append((i+1) / len(spectrum) * 6)


plt.clf()
plt.stem(frequency[:60], spectrum[:60], use_line_collection=True)
plt.ylim(0, 20000)

plt.title("Spectrum")
plt.xlabel('frequency')
plt.savefig("frequency.png")


samples = []
DFTtime = []
FFTtime = []

with open("timeData.txt", 'r') as csvfile:
    plots = csv.reader(csvfile, delimiter=',')
    for row in plots:
        samples.append(float(row[0]))
        DFTtime.append(float(row[1]))
        FFTtime.append(float(row[2]))

plt.clf()
line1, = plt.plot(samples, DFTtime)
line2, = plt.plot(samples, FFTtime)
plt.legend((line1, line2), ('DFT', 'FFT'))

plt.title("Time complexity")
plt.xlabel('data size')
plt.savefig("time.png")
