#ifndef BLOCK_HEAP_H_
#define BLOCK_HEAP_H_

#include "api/common_types.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

/** Lemma 3.3のデータ構造。頂点の重複を許さない。READMEにあるように、ここでは単なるsetであり、論文中の計算量より劣る。 */
class BlockHeap {
    public:
        BlockHeap(int M, Length B);
        /** Nを要素数としたときO(log N) */
        void insert(Vertex v, Length l);
        /** Nを要素数としたときO(log N) */
        void batch_prepend(const std::vector<std::pair<Vertex, Length>>& L);
        /** Nを要素数としたときO(log N) */
        std::pair<Length ,std::vector<Vertex>> pull();
        /** 要素数がゼロかどうか返す。 */
        bool empty();

    private:
        int M_;
        Length B_;

        std::set<std::pair<Length, Vertex>> que_;
        std::unordered_map<Vertex, Length> d_;
};

#endif  // BLOCK_HEAP_H_