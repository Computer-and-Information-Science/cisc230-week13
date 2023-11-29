// An implementation of the maximum flow algorithm

#include "graph.h"
#include <algorithm>
#include <climits>
#include <iostream>
using namespace std;

void augment (DiGraph<char>& g, const list<char>& path, int w);
list<char> find_path (const DiGraph<char>& g, char v1, char v2);
int maxflow (const DiGraph<char>& g, char s, char t);
int weight (const DiGraph<char>& g, const list<char>& path);

int main () {
	DiGraph<char> g;
	g.add_edge('s', 'a', 4);
	g.add_edge('s', 'b', 2);
	g.add_edge('a', 'b', 1);
	g.add_edge('a', 'd', 4);
	g.add_edge('a', 'c', 2);
	g.add_edge('b', 'd', 2);
	g.add_edge('c', 't', 3);
	g.add_edge('d', 't', 3);
	cout << g;

	cout << "Max flow is " << maxflow(g, 's', 't') << endl;
}

void augment (DiGraph<char>& g, const list<char>& path, int w) {
	// Adjusts the weights of the edges along the path by subtracting weight w.
	auto v1 = path.front(); // first vertex
	for (auto v2: path) { // for each vertex in the path
		if (v2 != path.front()) { // if not first vertex in the path
			// Update the weight of edge from v1 to v2
			g.update_edge(v1, v2, g.weight(v1, v2) - w);
			v1 = v2; // update vertex for next edge
		}
	}
}

list<char> find_path (const DiGraph<char>& g, char v1, char v2) {
	// Find a path through the graph along edges of non-zero weight

	if (v1 == v2) // if path is a single vertex
		return list<char>(1, v1); // return list of single vertex

	// Iterate through the neighbors of v1
	for (auto v: g.neighbors(v1)) {
		if (g.weight(v1, v)) { // if edge has non-zero weight
			// Find a path from neighbor to v2
			list<char> path = find_path(g, v, v2);
			// If path found, push v1 onto front and return the path
			if (path.size()) {
				path.push_front(v1);
				return path;
			}
		}
	}

	// No path was found, return an empty list
	return list<char>();
}

int maxflow (const DiGraph<char>& g, char s, char t) {
	// Determine maximum from from source s to sink t

	DiGraph<char> g1(g); // make copy of the given graph
	int flow = 0; // initialize flow to zero

	// Find paths from s to t until no path can be found
	for (list<char> path = find_path(g1, s, t); path.size();
			path = find_path(g1, s, t)) {
		int w = weight(g1, path); // Get weight of the path
		flow += w; // Add weight to flow
		augment(g1, path, w); // Augment the path to remove weight from edges
	}

	return flow;
}

int weight (const DiGraph<char>& g, const list<char>& path) {
	// Find the weight of the path. This is the minumum edge weight among all
	// edges in the path.
	size_t w = INT_MAX; // initialize weight to a big number
	auto v1 = path.front(); // get first vertex in path
	for (auto v2: path) {
		if (v2 != path.front()) { // if not first vertex
			w = min(w, g.weight(v1, v2)); // lesser of w or edge weight
			v1 = v2; // update vertex for next edge
		}
	}
	return w;
}
