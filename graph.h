#pragma once
 
#include <iostream>
#include <list>
#include <map>
 
/**
 * @brief A directed graph, optionally weighted
 * 
 * @tparam T Data type of vertices
 */
template <typename T>
class DiGraph {
private:
	std::map<T, std::map<T, size_t> > adj;
public:
	/**
	 * @brief Add an edge to the graph
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * @param w Weight of the edge (optional)
	 * 
	 * Adds an edge from vertex v1 to vertex v2. If either of v1 or v2 are
	 * not already defined as edges, they are created automatically. For
	 * unweighted graphs, omit parameter w.
	 */
	void add_edge(const T& v1, const T& v2, size_t w = 1)
		{ if (!is_edge(v1, v2)) update_edge(v1, v2, w); }
 
	/**
	 * @brief Adds a vertext to the graph
	 * 
	 * @param v Vertex to be added
	 * 
	 * Adds the given vertex to the graph if it does not already exist as
	 * a vertex. The vertex, if added, will have no outgoing or incoming
	 * edges.
	 */
	void add_vertex(const T& v) { adj[v]; }
 
	/**
	 * @brief Get inward degree of vertex
	 * 
	 * @param v The vertex of interest
	 * @return size_t Number of inward edges
	 */
	size_t degree_in(const T& v) const { return neighbors_in(v).size(); }
 
	/**
	 * @brief get outward degree of vertex
	 * 
	 * @param v The vertex of interest
	 * @return size_t Number of outward edges
	 */
	size_t degree_out(const T& v) const { return adj.at(v).size(); }
 
	/**
	 * @brief Determine if edge exists from one vertex to another
	 * 
	 * @param v1 The vertex of interest to begin an edge
	 * @param v2 The vertex of interest to end an edge
	 * @return true An edge exists from v1 to v2
	 * @return false No edge exists from v1 to v2
	 */
	bool is_edge(const T& v1, const T& v2) const
		{ return is_vertex(v1) && adj.at(v1).find(v2) != adj.at(v1).end(); }
 

	/**
	 * @brief Determine if a vertex exists
	 * 
	 * @param v The vertex of interest
	 * @return true Vertex v exists in the graph
	 * @return false Vertex v does not exist in the graph
	 */
	bool is_vertex(const T& v) const { return adj.find(v) != adj.end(); }
 
	/**
	 * @brief Find all neighbors of a given vertex
	 * 
	 * @param v The vertex of interest
	 * @return std::list<T> List of vertices connected by a single outgoing edge
	 * 
	 * Returns a list of vertices that can be reached by traveling from vertex
	 * v along a single edge. For directed graphs, only outward edges are
	 * considered. If vertex v does not exist, returns an empty list.
	 */
    std::list<T> neighbors (const T& v) const;
 
	/**
	 * @brief Find all inward neighbors of a given vertex
	 * 
	 * @param v The vertex of interest
	 * @return std::list<T> List of vertices connected by a single incoming edge
	 * 
	 * Returns a list of vertices that can reach vertex v by traveling along
	 * a single edge. For directed graphs, only inward edges are considered.
	 * If vertex v does not exist, returns an empty list.
	 */
    std::list<T> neighbors_in (const T& v) const;
 
	/**
	 * @brief Remove a vertex from the graph
	 * 
	 * @param v The vertex to be removed
	 * 
	 * Removes vertex v from the graph. All edges connected to vertex v (both
	 * incoming and outgoing) are also removed. If v does not exist in the
	 * graph, does nothing.
	 */
    void remove (const T& v); // Remove a vertex
 
	/**
	 * @brief Remove an edge from the graph
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * 
	 * Removes the edge extending from vertex v1 to vertex v2. If the edge
	 * does not exist, or if either v1 or v2 does not exist, does nothing.
	 */
    void remove_edge (const T& v1, const T& v2) { adj[v1].erase(v2); }
 
	/**
	 * @brief Updates weight of an edge
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * @param w Weight of the edge
	 * 
	 * Updates the weight of the edge extending from v1 to v2. If no edge
	 * exists from v1 to v2, or if either v1 or v2 does not exist, the edge
	 * is added with the given weight.
	 */
	void update_edge(const T& v1, const T& v2, size_t w)
		{ add_vertex(v2);  adj[v1][v2] = w; }
 
	/**
	 * @brief Get list of vertices in the graph
	 * 
	 * @return std::list<T> A list of vertices
	 */
	std::list<T> vertices() const;
 
	/**
	 * @brief Get weight of a edge
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * @return size_t Weight of the edge
	 * 
	 * Returns the weight of the edge extending from v1 to v2. If the edge
	 * does not exist, or if either v1 or v2 does not exist, returns zero.
	 */
    size_t weight (const T& v1, const T& v2) const
		{ return is_vertex(v1) && is_edge(v1, v2) ? adj.at(v1).at(v2) : 0; }
};
 
/**
 * @brief An undrected graph, optionall weighted
 * 
 * @tparam T Data type of vertices
 */
template <typename T>
class Graph : public DiGraph<T> {
public:

	/**
	 * @brief Add an edge to the graph
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * @param w Weight of the edge (optional)
	 * 
	 * Adds an edge between vertex v1 and vertex v2. If either of v1 or v2 are
	 * not already defined as edges, they are created automatically. For
	 * unweighted graphs, omit parameter w.
	 */
    void add_edge (const T& v1, const T& v2, size_t w=1) {
        DiGraph<T>::add_edge(v1, v2, w);
        DiGraph<T>::add_edge(v2, v1, w);
    }

	/**
	 * @brief Get degree of vertex
	 * 
	 * @param v The vertex of interest
	 * @return size_t Number of edges attached to v
	 */
    size_t degree (const T& v) const { return DiGraph<T>::degree_out(v); }

	/**
	 * @brief Remove an edge from the graph
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * 
	 * Removes the edge between vertex v1 and vertex v2. If the edge
	 * does not exist, or if either v1 or v2 does not exist, does nothing.
	 */
    void remove_edge (const T& v1, const T& v2) {
        DiGraph<T>::remove_edge(v1, v2);
        DiGraph<T>::remove_edge(v2, v1);
    }

	/**
	 * @brief Updates weight of an edge
	 * 
	 * @param v1 Vertex at which edge begins
	 * @param v2 Vertex at which edge ends
	 * @param w Weight of the edge
	 * 
	 * Updates the weight of the edge between vertices v1 to v2. If no edge
	 * exists between v1 and v2, or if either v1 or v2 does not exist, the edge
	 * is added with the given weight.
	 */
    void update_edge (const T& v1, const T& v2, size_t w) {
        DiGraph<T>::update_edge(v1, v2, w);
        DiGraph<T>::update_edge(v2, v1, w);
    }
};

template <typename T>
std::list<T> DiGraph<T>::neighbors(const T& v) const {
	std::list<T> l;
	if (is_vertex(v)) {
		for (const auto& p : adj.at(v))
			l.push_back(p.first);
	}
	return l;
}

template <typename T>
std::list<T> DiGraph<T>::neighbors_in(const T& v) const {
	std::list<T> l;
	for (const auto& p : adj) {
		if (p.second.find(v) != p.second.end())
			l.push_back(p.first);
	}
	return l;
}

template <typename T>
std::list<T> DiGraph<T>::vertices() const {
	std::list<T> l;
	for (const auto& p : adj)
		l.push_back(p.first);
	return l;
}

template <typename T>
void DiGraph<T>::remove (const T& v) {
	for (auto& p : adj)
		p.second.erase(v);
	adj.erase(v);
}

/**
 * @brief Support for output of Graph and DiGraph objects
 * 
 * @tparam T Date type of vertices
 * @param os The output object
 * @param g The graph to be output
 * @return std::ostream& For chaining the output object
 * 
 * Sends a text-based version of the graph to the given ostream object. The
 * output consists of multiple lines. The first line lists the count of
 * vertices. This is followed by one line for each vertex that includes the
 * vertex and all vertices with weights connected by a single edge.
 */
template <typename T>
std::ostream& operator<< (std::ostream& os, const DiGraph<T>& g) {
	std::list<T> vlist = g.vertices();
	os << "Vertex count: " << vlist.size() << std::endl;
	for (const auto& v1 : vlist) {
		os << v1 << ":";
		for (const auto& v2 : vlist) {
			if (g.is_edge(v1, v2))
				os << " " << v2 << "(" << g.weight(v1, v2) << ")";
		}
		os << std::endl;
	}
    return os;
}
