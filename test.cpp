#include"graph.cpp"

using namespace std;
int main() {
    DijkstraStorage storage;
    Graph_Generator generator;
    Dijkstra_Graph G = generator.get_random_graph(3, 4);
    G.print();
    G.Alg_Dijkstra(0, 2);
    G.print_min_distanses(); 
    //storage.init_DijkstraStorage(4, 2, 2);
    /* storage.print_heap();

    cout << "\n-------------------\n";
		for(int i = 0; i < storage.heap_size; i++)
			cout << storage.heap_to_vertex[i] ;

		cout << "\n";
		for(int i = 0; i < storage.heap_size; i++)
			cout << storage.vertex_to_heap[i]; */
}