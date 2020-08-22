#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <stack>

#include "dijkstra.h"

using namespace std;
struct Point{
	long long lat; // latitiude
	long long lon; // longtitude
};

long long manhattan(const Point &pt1, const Point &pt2){
	// calculates manhattan distance between two points
	long long x, y;
	//cout << pt1.lat << " - " << pt2.lat << endl;
	
	y = pt1.lat - pt2.lat;

	y = abs(y);
	//cout << y << endl;
	x = pt1.lon - pt2.lon;
	
	x = abs(x);

	return x + y;
}

int findClosest(const Point& vertex, unordered_map <int, Point> points){
	// finds closest vertex
	int ans;
	long long dist, min_dist;
	
	ans = points.begin()->first;

	//cout << points[start].lat << endl;
	
	min_dist = manhattan(points[ans], vertex);

	// cout << min_dist << endl;

    for(auto i = points.begin(); i != points.end(); ++i){
    	dist = manhattan(i->second, vertex);
    	if(min_dist > dist){
    		min_dist = dist;
    		ans = i->first;
    	}
    }
    // cout << min_dist << endl;
    // cout << points[ans].lat << ", " << points[ans].lon << endl;
    return ans;
}

void readGraph(string filename, WDigraph& graph, unordered_map <int, Point> &points){
	// reads a txt file and cretes a graph with vertices and edges
	Point p;
	double dlat, dlon;
	long long llat, llon;
	string input, temp, temp1, temp2;
	int pos0, pos1, len, id;
	ifstream file;
	int i = 0;

	file.open(filename);
	if(file.is_open()){

		while(getline(file, input)){
			pos0 = input.find(",") + 1;
			
			if(input[0] == 'V'){

				input = input.substr(pos0);

				pos1 = input.find(",");

				len = pos1 + 2;

				id = stoi(input.substr(0, len));

				// if(i == 1000){
				// 	cout << id << endl;
				// 	i = 0;
				// }
				// i++;

				graph.addVertex(id);

				pos0 = 0;

				input = input.substr(pos1 + 1);

				pos1 = input.find(",");

				len = pos1;
				
				dlat = stod(input.substr(pos0, len));
				//cout << dlat << endl;
				input = input.substr(pos1);
				//cout << input.substr(1) << endl;

				dlon = stod(input.substr(1)) ;
				//cout << dlon << endl;
				llat = static_cast <long long> (dlat * 100000);

				llon = static_cast <long long> (dlon * 100000);

				p.lat = llat;
				p.lon = llon;

				// cout << "id: " << id << endl;
				//cout << "lat: " << p.lat << ", " << "lon: " << p.lon << endl;

				points.insert({id, p});

				//cout << p.lat << ", " << p.lon << endl;

			}
			else if(input[0] == 'E'){
				temp = input.substr(pos0);

	        	pos1 = temp.find(",");

	        	len = pos1 + 2;

	        	temp1 = temp.substr(0, len); // first ID

	        	temp2 = temp.substr(pos1 + 1);
	        	
	        	pos0 = 0;	// position of where second ID starts

	        	pos1 = temp2.find(","); // position of where second ID ends

	        	int a = stoi(temp1);

	        	int b = stoi(temp2.substr(pos0, pos1 + 1));
	        	       	
	        	graph.addEdge(a, b, manhattan(points.find(a)->second, points.find(b)->second));

			}
			
		}

	}
	file.close();

}

void routeFinder(int start, int end, unordered_map<int, PIL> &tree, unordered_map <int, Point> &points){
	// Finds the closest route from the beginning of a tree to the end of it
	stack <int> route;
	char cm;
	int p;
	auto it = tree.find(end);
	if(it != tree.end()){
		route.push(end);
		while(it->second.first != start){
			route.push(it->second.first);
			it = tree.find(it->second.first);
		}
	}
	route.push(start);

	cout << "N " << route.size() << endl;

	while(route.size() > 0){
		cin >> cm; 

		if(cm == 'A'){
			p = route.top(); // point to be accessed from the points unordered map
			route.pop(); // removing that point from the stack
			auto coord = points.find(p);
			cout << "W " << coord->second.lat << " " << coord->second.lon << endl;
		}
	}

	cout << "E" << endl;

}


int main(){
	
	string input, output;
    char cm;
    // given start and end points on the map
    Point start, end;

    WDigraph graph;

    unordered_map <int, Point> points;

    unordered_map<int, PIL> tree;

    int startVertex, endVertex;

    readGraph("edmonton-roads-2.0.1.txt", graph, points);
    // reading the edmonton vertices and edges

    cin >> cm >> start.lat >> start.lon >> end.lat >> end.lon;
    // start and end point

    // closest vertices
    startVertex = findClosest(start, points);

    endVertex = findClosest(end, points);

    dijkstra(graph, startVertex, tree);

    routeFinder(startVertex, endVertex, tree, points);
    
}