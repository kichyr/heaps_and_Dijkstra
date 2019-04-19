#include "storage.h"


void DijkstraStorage::init_DijkstraStorage(int n_vertex, int _type_heap, int start_vert){
    type_heap = _type_heap;
    heap_array.resize(n_vertex); 
    vertex_to_heap.resize(n_vertex);
    heap_to_vertex.resize(n_vertex);
    height = static_cast<int>(std::ceil(std::log2(n_vertex*(type_heap-1)+1)/log2(type_heap)));
    heap_size = n_vertex;

    for(int i = 0; i < heap_size; i++) {
        heap_array[i] = inf;
        vertex_to_heap[i] = i;
        heap_to_vertex[i] = i;
    }
    //print_heap();
    heap_array[start_vert] = 0;
    build_max_heap();
}

int DijkstraStorage::parent(int i) {
    return i/type_heap;
}

int DijkstraStorage::child(int p, int num_child) {
    return (p+1) * type_heap+num_child-type_heap+1;
}


int DijkstraStorage::left_on_level(int level){
    if(level == 0)
        return 0;
    return(static_cast<int>((pow(type_heap, level))/(type_heap-1))-1);
}

void DijkstraStorage::max_heapify(int i) {
    int level_i = child(i, 0);//
    if(level_i >= heap_size) return;

    auto min_itr = std::min_element(heap_array.begin()+level_i,
        (heap_array.begin()+ std::min(level_i+type_heap, heap_size)));

    std::cout << "MIN:" << *min_itr;
    int new_i = distance(heap_array.begin(), min_itr);

    if(heap_array[i] > *min_itr) {
        std::swap(heap_array[i], *min_itr);
        std::swap(heap_to_vertex[i], heap_to_vertex[new_i]);
        std::swap(vertex_to_heap[heap_to_vertex[i]], vertex_to_heap[heap_to_vertex[new_i]]);
        std::cout << "///\n\n";
    for(int i = 0; i < 3; i++)
			std::cout << vertex_to_heap[i] ;
    std::cout << "///\n\n";
        if(child(new_i, 0) < heap_size)
            max_heapify(new_i);
    }
}

void DijkstraStorage::build_max_heap() {
    for(int i = static_cast<int>(pow(type_heap, height-1))-1; i >= 0; i--)
        max_heapify(i);
}

void DijkstraStorage::print_heap() {
    std::cout << "size: " << heap_size << std::endl;
    std::cout << "height: " << height << std::endl;
    rec_print(0);
}

void DijkstraStorage::rec_print(int level) {
   //int spaces = pow(type_heap, height-1)/pow(type_heap, level+1);
    for(int i = 0; i < static_cast<int>(pow(type_heap, level)); i++) {
        //for(int j = 0; j < spaces; j++)
        //    std::cout << " ";
        if(left_on_level(level)+i >= heap_size)
            break;
        std::cout << "(" << heap_to_vertex[left_on_level(level)+i] << 
            " " << heap_array[left_on_level(level)+i] << "); ";
    }

    std::cout << std::endl;
    if(level+1 < height)
        rec_print(level+1);
}

//---------------------------------------------------

int DijkstraStorage::RemoveMin() {
    std::swap(heap_array[0], heap_array[heap_size-1]);
    std::swap(heap_to_vertex[0], heap_to_vertex[heap_size-1]);
    std::swap(vertex_to_heap[heap_to_vertex[0]], vertex_to_heap[heap_to_vertex[heap_size-1]]);
    heap_size--;
    height = static_cast<int>(std::ceil(std::log2(heap_size*(type_heap-1)+1)/log2(type_heap)));
    max_heapify(0);
    std::cout << "ok" << "\n";
    for(int i = 0; i < 3; i++)
			std::cout << vertex_to_heap[i] ;
    return heap_to_vertex[heap_size];
}

int64_t DijkstraStorage::GetDistanceToVertex(int vertex_index) const{
    return heap_array[vertex_to_heap[vertex_index]];
}

void DijkstraStorage::SetDistance(int vertex_index, int64_t distance) {
    heap_array[vertex_to_heap[vertex_index]] = distance;
    std::swap(heap_array[0], heap_array[vertex_to_heap[vertex_index]]);
    int k = vertex_to_heap[vertex_index];
    std::swap(vertex_to_heap[heap_to_vertex[0]], vertex_to_heap[vertex_index]);
    std::swap(heap_to_vertex[0], heap_to_vertex[k]);
    std::cout << "///lol\n\n";
    for(int i = 0; i < 3; i++)
			std::cout << vertex_to_heap[i] ;
    std::cout << "///\n\n";
    max_heapify(0);
}

int DijkstraStorage::get_heap_size(){
    return heap_size;
}

