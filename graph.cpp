
#include <vector>
#include <cstdint>
#include <iostream>
#include <cmath>
#include <ctime>
#include <utility>
#include "storage.h"

using namespace std;

class Graph {
public:
	int size;
	vector<vector<pair<int, int64_t>>> g_list; // Номер вершины и вес соответсвующего ребра
	Graph(){}

    Graph(int n_vertex) {
		g_list.resize(n_vertex);
		size = n_vertex;
	}
	
	~Graph(){};

	void print(){
		for(size_t i = 0; i < size; i++){
			cout << i << ": ";
			for(size_t j = 0; j < g_list[i].size(); j++){
				std::cout << "(" << g_list[i][j].first <<", " << g_list[i][j].second << "),  ";
			}
			cout << endl;
		}
	}
    void AddEdge(size_t from, size_t to, int64_t weight){
			g_list[from].push_back(std::make_pair(to, weight));
			g_list[to].push_back(std::make_pair(from, weight));
	}
};

class Dijkstra_Graph : public Graph {
private:
	int heap_type;
	DijkstraStorage heap;

	void relax(int u, int w, int64_t weight) {
		if(heap.GetDistanceToVertex(u) < heap.inf && heap.GetDistanceToVertex(w) > heap.GetDistanceToVertex(u) + weight) {
			heap.SetDistance(w, heap.GetDistanceToVertex(u) + weight);
		}
	}

public:

	Dijkstra_Graph(int n_vertex): Graph(n_vertex){};
	
	void Alg_Dijkstra(int start_vertex, int _heap_type)	{
		
		heap_type = _heap_type;
		heap.init_DijkstraStorage(size, heap_type, start_vertex);
		
		int u;
		while (heap.get_heap_size() != 0) {
			u = heap.RemoveMin();
			for(int i = 0; i < g_list[u].size(); i++)
				relax(u, g_list[u][i].first, g_list[u][i].second);
		}
	}


	void print_min_distanses() {
		for(int i = 0; i < size; i++)
			std::cout << "(to " << i <<", distance " << heap.GetDistanceToVertex(i) << ")" << std::endl;
		heap.print_heap();
	}
};


class Graph_Generator {
public:
    Dijkstra_Graph get_random_graph(int size, int64_t max_weight) {
        Dijkstra_Graph g(size);
        srand(time(NULL));
        for(uint i = 0 ; i < size; i++)
            for(uint j = i+1; j < size; j++) {
                if(rand()%2 == 1)
                    g.AddEdge(i, j, rand()%max_weight);
            }
        return g;
    }
    

	Dijkstra_Graph get_simple_graph() {
		Dijkstra_Graph g(3);
		g.AddEdge(0,1, 9);
		return g;
	}

	Dijkstra_Graph get_hand_test() {
		Dijkstra_Graph g(6);
		g.AddEdge(0, 5, 14);
		g.AddEdge(5, 4, 9);
		g.AddEdge(4, 3, 6);
		g.AddEdge(0, 1, 7);
		g.AddEdge(1, 3, 15);
		g.AddEdge(0, 2, 9);
		g.AddEdge(5, 2, 2);
		g.AddEdge(1, 2, 10);
		g.AddEdge(2, 3, 11);
		return g;
	}	

    Dijkstra_Graph get_dense_graph() {
		int64_t max_weight = 50;
        size_t n_vertices = 100;
        Dijkstra_Graph result(n_vertices);
        for (uint i = 0; i < n_vertices; ++i) {
            for (uint j = 0; j < n_vertices; ++j) {
                if (i >= j) {
                    continue;
                }
                if ((i < 5) && (j > 90)) {
                    continue;
                } else {
                    result.AddEdge(i, j, rand()%max_weight+5);
                }
            }
        }
        return result;
    }


	 Dijkstra_Graph get_rarefied_graph() {
		int64_t max_weight = 50;
        size_t n_vertices = 100;
        Dijkstra_Graph result(n_vertices);
        for (uint i = 0; i < n_vertices; ++i) {
            for (uint j = 0; j < n_vertices; ++j) {
                if (i >= j) {
                    continue;
                }
                if ((i < 47) && (j > 53)) {
                    continue;
                } else {
                    result.AddEdge(i, j, rand()%max_weight+5);
                }
            }
        }
        return result;
    }


};