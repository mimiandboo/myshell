myshell: myshell.o functions.o
	g++ -o myshell myshell.o functions.o

functions.o: functions.cpp general.h
	g++ -Wall -c functions.cpp

myshell.o: myshell.cpp general.h
	g++ -Wall -c myshell.cpp

cleanall:
	rm -f *.o
	rm myshell
	rm a.out
