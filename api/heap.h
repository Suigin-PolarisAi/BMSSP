#ifndef HEAP_H_
#define HEAP_H_

#include "api/common_types.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

class Heap {
    public:
        void push(Vertex v, Length l);
        std::pair<Vertex, Length> top();
        void pop();
        bool empty();

    private:
        int M_;
        Length B_;

        std::set<std::pair<Length, Vertex>> que_;
        std::unordered_map<Vertex, Length> d_;
};

#endif  // HEAP_H_