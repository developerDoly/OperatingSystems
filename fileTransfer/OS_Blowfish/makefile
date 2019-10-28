all: main clean

main: main.o blowfish.o
	g++ -o main main.o blowfish.o

main.o:
	g++ -c main.cpp

blowfish.o:
	g++ -c blowfish.cpp

clean:
	rm -f *~
	rm -f *.o