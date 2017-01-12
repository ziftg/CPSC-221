all: huftree
huftree: priorityQueue.o codetree.o huftree.o
	g++ -Wall -o huftree -g priorityQueue.o codetree.o huftree.o
huftree.o: priorityQueue.h huftree.cc
	g++ -Wall -c -g huftree.cc
codetree.o: priorityQueue.h codetree.h priorityQueue.o codetree.cc
	g++ -Wall -c -g codetree.cc
priorityQueue.o: priorityQueue.h priorityQueue.cc
	g++ -Wall -c -g priorityQueue.cc
clean :
	rm *.o
	rm huftree