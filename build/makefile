CXX = g++
LDLIBS = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

VecPath: main.o grid.o node.o
	$(CXX) -o VecPath $^ $(LDLIBS)

main.o: ../src/main.cpp ../src/grid.h
	$(CXX) -c ../src/main.cpp

grid.o: ../src/grid.cpp ../src/node.h
	$(CXX) -c ../src/grid.cpp 

node.o: ../src/node.cpp
	$(CXX) -c ../src/node.cpp
