#ifndef _STORAGE_H_
#define _STORAGE_H_
#include <vector>
#include <limits>
#include <cstdint>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>

/*
При реализации алгоритма Дейкстры редко используется фибоначчиева куча, дающая асимптотику O(E + V \log V),
из-за большой контанты. Реально же используются кучи, у которых 2, 4 или 8 потомков. Обычно 8-кучи оказываются
самыми эффективными из-за того, что запрашиваемые из памяти данные достаточно локальны.

Реализуйте структуру-хранилище очередь с приоритетами, интерфейс которой описан ниже.
*/


class DijkstraStorage {
public:
    int64_t inf = std::numeric_limits<int>::max();


    // Инициализирует структуру для графа на n_vertex вершинах
    // Type_heap 2,4,8 куча

    void init_DijkstraStorage(int n_vertex, int type_heap, int start_vert);

    // Возвращает текущее найденное расстояние до вершины. Если оно еще не найдено - возвращается
    // std::numeric_limits<int64_t>::max();
    int64_t GetDistanceToVertex(int vertex_index) const;

    // Сообщает о том, что некоторый путь до вершины уже найден, но он еще не оптимален
    // Это означает, что vertex_index на данный момент распологается в очереди (на краю волнового фронта)
    bool IsActive(int vertex_index) const;

    // Делает вершину активной и возвращает true, если вершина уже была активной возвращается false
    bool MakeVertexActive(int vertex_index);

    // Делает вершину не активной и возвращает true если вершина была активной, иначе возвращается false
    bool MakeVertexInactive(int vertex_index);

    // Изменяет текущее расстояние до вершины, вершина может быть как активной так и не активной
    void SetDistance(int vertex_index, int64_t distance);

    // Возвращает номер активной вершины, расстояние до которой минимально
    int GetMinIndex() const;

    // Возвращает номер активной вершины, расстояние до которой минимально и делает ее неактивной
    int RemoveMin();

    // true если не осталось активных вершин
    bool Empty() const;

    //выводит кучу
    void print_heap();

    int get_heap_size();

public:
    int heap_size;
    int height;
    std::vector<int64_t> heap_array; //расстояния
    std::vector<int> vertex_to_heap; //соответсвующие номера вершин
    std::vector<int> heap_to_vertex;
    
    int type_heap;

    int parent(int i);
    int child(int p, int num_child);
    void rec_print();
    int left_on_level(int level);

    void max_heapify(int level);
    void build_max_heap();

    void shift_up(int i);

    void rec_print(int level);
};
#endif //_STORAGE_H_

// С использованием описанной выше структуры реализуйте алгоритм Дейкстры. Сгенерируйте случайные
// большие графы и оцените скорость работы на них при использовании 2, 4 и 8 - кучи.
// Отдельно рассмотрите случаи плотных и разреженных графов.

// Используйте интерфейс графа, описанный в первом бонусном задании или напишите свой.
