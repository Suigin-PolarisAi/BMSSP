#ifndef BLOCK_HEAP_H_
#define BLOCK_HEAP_H_

#include "api/common_types.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

class BlockHeap {
    public:
        BlockHeap(int M, Length B);
        void insert(Vertex v, Length l);
        void batch_prepend(const std::vector<std::pair<Vertex, Length>>& L);
        std::pair<Length ,std::vector<Vertex>> pull();
        bool empty();

    private:
        int M_;
        Length B_;

        std::set<std::pair<Length, Vertex>> que_;
        std::unordered_map<Vertex, Length> d_;
};

#endif  // BLOCK_HEAP_H_