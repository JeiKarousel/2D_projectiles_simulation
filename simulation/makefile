
CXX = g++
CXXFLAGS = -Wall -g

LIB = -lraylib -lopengl32 -lgdi32 -lwinmm

main: main.o
	$(CXX) $(CXXFLAGS) main.o -o main $(LIB)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

clean:
	rm -f *.o main.exe main
