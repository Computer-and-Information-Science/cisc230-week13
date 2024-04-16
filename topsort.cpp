// Topological Sort
#include <iostream>
#include <string>
#include <map>
#include <queue>
#include "graph.h"
using namespace std;

int main () {
	DiGraph<string> g;
	g.add_edge("cisc115", "cisc125");
	g.add_edge("cisc125", "cisc225");
	g.add_edge("cisc125", "cisc230");
	g.add_edge("math180", "math181");
	g.add_edge("math180", "math202");

	// Initialize indegree of each vertex
	map<string, int> indegree;
	for (auto v : g.vertices())
		indegree[v] = g.degree_in(v);

	// Initialize queue and counter
	queue<string> q;
	int count = 0;

	// Place all vertices with indegree 0 into queue
	for (auto v : g.vertices())
		if (!indegree[v])
			q.push(v);

	// While queue is not empty, pop queue into ordering
	list<string> order;
	while (!q.empty()) {
		// Front of queue is next in vertex order, increment count
		string v = q.front();
		q.pop();
		order.push_back(v);
		count++;

		// For each neighbor of v, decrement indegree and, if 0, push to queue
		for (auto w : g.neighbors(v))
			if (!(--indegree[w]))
				q.push(w);
	}

	// If count does not match size of graph, cycle was found
	if (count != g.vertices().size())
		cout << "Cycle found. No possible ordering.\n";
	else {
		cout << "Vertex order:\n";
		for (auto v : order)
			cout << "  - " << v << endl;
	}

	return 0;
}
