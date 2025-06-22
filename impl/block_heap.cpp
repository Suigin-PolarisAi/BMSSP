#include "api/common_types.h"
#include "api/block_heap.h"

#include <iostream>
#include <vector>

BlockHeap::BlockHeap(int M, Length B) {
    M_ = M;
    B_ = B;
}

std::pair<Length, std::vector<Vertex>> BlockHeap::pull() {
    std::vector<Vertex> S;
    for(int i = 0; i < M_; i++) {
        if(que_.empty()) {
            break;
        }
        std::pair<Length, Vertex> p = *que_.begin();
        que_.erase(p);
        d_.erase(p.second);
        S.push_back(p.second);
    }
    if(que_.empty()) {
        return std::make_pair(B_, S);
    } else {
        return std::make_pair(que_.begin()->first, S);
    }
}

void BlockHeap::batch_prepend(const std::vector<std::pair<Vertex, Length>>& L) {
    for(int i = 0; i < (int)L.size(); i++) {
        insert(L[i].first, L[i].second);
    }
}

void BlockHeap::insert(Vertex v, Length l) {
    if(d_.count(v) != 0 && d_[v] < l) {
        return;
    } else if (d_.count(v) != 0 && d_[v] >= l) {
        que_.erase(std::make_pair(d_[v], v));
    }
    que_.insert(std::make_pair(l, v));
    d_[v] = l;
}

bool BlockHeap::empty() {
    return que_.empty();
}