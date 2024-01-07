all: bucketSort countingSort heapSort insertionSort mergeSort quickSort radixSort

bucketSort: bucketSort.o
	g++ -o bucketSort -std=c++11 bucketSort.o
bucketSort.o: bucketSort.cpp
	g++ -c -std=c++11 bucketSort.cpp

countingSort: countingSort.o
	g++ -o countingSort -std=c++11 countingSort.o
countingSort.o: countingSort.cpp
	g++ -c -std=c++11 countingSort.cpp

heapSort: heapSort.o
	g++ -o heapSort -std=c++11 heapSort.o
heapSort.o: heapSort.cpp
	g++ -c -std=c++11 heapSort.cpp

insertionSort: insertionSort.o
	g++ -o insertionSort -std=c++11 insertionSort.o
insertionSort.o: insertionSort.cpp
	g++ -c -std=c++11 insertionSort.cpp

mergeSort: mergeSort.o
	g++ -o mergeSort -std=c++11 mergeSort.o
mergeSort.o: mergeSort.cpp
	g++ -c -std=c++11 mergeSort.cpp

quickSort: quickSort.o
	g++ -o quickSort -std=c++11 quickSort.o
quickSort.o: quickSort.cpp
	g++ -c -std=c++11 quickSort.cpp

radixSort: radixSort.o
	g++ -o radixSort -std=c++11 radixSort.o
radixSort.o: radixSort.cpp
	g++ -c -std=c++11 radixSort.cpp


clean:
	rm *.o bucketSort countingSort heapSort insertionSort mergeSort quickSort radixSort