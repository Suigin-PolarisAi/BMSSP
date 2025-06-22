#include "api/common_types.h"
#include "api/heap.h"

#include <iostream>
#include <vector>
#include <unordered_map>

void Heap::push(Vertex v, Length l) {
    if(d_.count(v) != 0 && d_[v] < l) {
        return;
    } else if (d_.count(v) != 0 && d_[v] >= l) {
        que_.erase(std::make_pair(d_[v], v));
    }
    que_.insert(std::make_pair(l, v));
    d_[v] = l;
}

std::pair<Vertex, Length> Heap::top() {
    auto p = *que_.begin();
    return std::make_pair(p.second, p.first);
}

void Heap::pop() {
    d_.erase(top().second);
    que_.erase(que_.begin());
}

bool Heap::empty() {
    return que_.empty();
}