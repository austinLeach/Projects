import matplotlib.pyplot as pyplot

fileName = input("What is the file name: ")

file = open(fileName, "r")

string = file.read()
array = string.split(",")

for i in range(0, len(array)):
    array[i] = float(array[i])


xAxis = ["10", "50", "100", "500", "1000", "5000", "10000", "50000", "100000", "500000", "1000000"]
pyplot.plot(xAxis, array)
pyplot.title(fileName)
pyplot.show()