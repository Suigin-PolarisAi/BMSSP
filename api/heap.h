#ifndef HEAP_H_
#define HEAP_H_

#include "api/common_types.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

/** Base Case (Algorithm 2)で使われるヒープ。頂点の重複を許さない。 */
class Heap {
    public:
        /** Key(頂点)とValue(最短距離)の組を新たに足す */
        void push(Vertex v, Length l);
        /** Value最小の要素を返す。 */
        std::pair<Vertex, Length> top();
        /** 最小の要素を取り除く */
        void pop();
        /** 要素数がゼロかどうか返す */
        bool empty();

    private:
        int M_;
        Length B_;

        std::set<std::pair<Length, Vertex>> que_;
        std::unordered_map<Vertex, Length> d_;
};

#endif  // HEAP_H_