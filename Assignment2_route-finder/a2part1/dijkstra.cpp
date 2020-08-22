#include <iostream>
#include <list>
#include <utility> // for pair()
// pair is a simple container of two heterogeneous objects
// which can be accessed by dot operator followed by 
// first or second keyword

#include <unordered_map>
#include "dijkstra.h"


using namespace std;


void dijkstra(const WDigraph& graph, int startVertex, 
    unordered_map<int, PIL>& searchTree) {
	// this function creates a search tree based on dijkstra algorithm
	//Point p;

	HeapItem <pair<int, int>, long long> heapItem; // (u,v), time

	BinaryHeap <pair<int, int>, long long> events = {}; // same format as item but it is class

	events.insert(make_pair(startVertex, startVertex), 0ll);
	
	while(events.size() > 0){

		heapItem = events.min(); // the last vertex

		events.popMin(); // removing the last vertex
		// case: v is not in the tree
		if(searchTree.find(heapItem.item.second) == searchTree.end()){
			// insert (v,u), time
			searchTree[heapItem.item.second] = make_pair(heapItem.item.first, heapItem.key);
		
			//cout << "test" << endl;
		
			for(auto i = graph.neighbours(heapItem.item.second); i != graph.endIterator(heapItem.item.second); i++){

				events.insert(make_pair(heapItem.item.second, *i), heapItem.key + graph.getCost(heapItem.item.second, *i));
			}
	}
	}
}

