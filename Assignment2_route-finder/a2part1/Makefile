server: dijkstra.o server.o digraph.o
	g++ dijkstra.o server.o digraph.o -o server

server.o: server.cpp
	g++ -c server.cpp

dijkstra.o: dijkstra.cpp dijkstra.h  
	g++  -c dijkstra.cpp 

digraph.o: digraph.cpp digraph.h 
	g++ -c digraph.cpp 

clean:
	rm *.o server