clear:
	rm -rf bin
	mkdir bin -p

mergesort:
	rm -f bin/mergesort
	g++ common_methods/arrays_methods.cpp sorting/merge_sort.cpp -o bin/mergesort