// shortest-path.cpp - Find shortest path from source vertex to destination
//	vertex in a weighted graph using a backtracking approach.

#include "graph.h"
#include <algorithm>
#include <climits>
#include <iostream>
#include <list>
#include <utility>
using namespace std;

// Path - Represents a path through a graph. This class keeps a list of
//	vertices and a list of weights between vertices. The list of vertices
//	should always contain one more entry than the list of weights.
class Path {
private:
	list<int> vertices; // Vertices along the path
	list<int> weights; // Weights between vertices
	int total_weight; // Total of all weights
public:
	// Constructor requires the starting vertex
	Path (int s) { vertices.push_back(s); total_weight = 0; }

	// Returns the path of vertices
	list<int> path () const { return vertices; }

	// Returns the total weight along the path, except when the path contains
	//	only one vertex in which case INT_MAX is returned (indicating that
	//	any path of two or more vertices is a better solution that a path
	//	with only the starting vertex).
	int weight() const { return weights.size() ? total_weight : INT_MAX; }

	// Adds a vertex to the path. Requires the vertex and the weight from
	//	the previous (end) vertex.
	void push (int v, int w) {
		vertices.push_back(v);
		weights.push_back(w);
		total_weight += w;
	}

	// Removes the last vertex from the path (for backtracking).
	void pop () {
		total_weight -= weights.back();
		vertices.pop_back();
		weights.pop_back();
	}

	// Returns the last vertex on the path.
	int back () const { return vertices.back(); }

	// Determines if the given vertex is currently in the path.
	bool has_vertex (int v) const
		{ return count(vertices.begin(), vertices.end(), v) > 0; }
};

void extend_path(const Graph<int> g, Path& cur, Path& best, int t) {
	if (cur.back() == t) {
		if (cur.weight() < best.weight())
			best = cur;
		return;
	}
	for (int v: g.neighbors(cur.back())) {
		if (!cur.has_vertex(v)) {
			cur.push(v, g.weight(cur.back(), v));
			extend_path(g, cur, best, t);
			cur.pop();
		}
	}
}

Path find_path(const Graph<int> g, int s, int t) {
	Path cur(s), best(s);
	extend_path(g, cur, best, t);
	return best;
}

int main() {
	// A sample weighted graph with 10 vertices.
	Graph<int> g1;
	g1.add_edge(1, 2, 1);
	g1.add_edge(1, 3, 2);
	g1.add_edge(2, 4, 2);
	g1.add_edge(2, 5, 1);
	g1.add_edge(3, 4, 1);
	g1.add_edge(3, 6, 4);
	g1.add_edge(4, 7, 3);
	g1.add_edge(5, 7, 2);
	g1.add_edge(5, 8, 3);
	g1.add_edge(6, 7, 1);
	g1.add_edge(6, 9, 3);
	g1.add_edge(7, 8, 2);
	g1.add_edge(7, 9, 2);
	g1.add_edge(8, 10, 2);
	g1.add_edge(9, 10, 1);

	cout << g1 << endl;

	// Call find_path to find a path from source to destination. The function
	//	returns a Path object.
	Path p = find_path(g1, 1, 10);

	// Output the vertices along the shortest path.
	cout << "Shortest path:";
	for (auto v: p.path())
		cout << " " << v;
	cout << " - " << "Total weight: " << p.weight() << endl;
#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
