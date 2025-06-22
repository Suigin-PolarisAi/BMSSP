#include "api/shortest_path.h"
#include "api/block_heap.h"
#include "api/heap.h"

#include <unordered_set>
#include <iostream>
#include <queue>
#include <cassert>
#include <cmath>

ShortestPath::ShortestPath(const Graph& G) {
    G_ = G;
}

namespace {
    int find_tree_size(int u, std::vector<int>& tree_size, const std::vector<std::vector<Vertex>>& F) {
        if(tree_size[u] != -1) return tree_size[u];
        int res = 1;
        for(int i = 0; i < (int)F[u].size(); i++) {
            Vertex v = F[u][i];
            res += find_tree_size(v, tree_size, F);
        }
        return tree_size[u] = res;
    }
}

std::vector<Length> ShortestPath::get(int s) {
    int N = (int)G_.size();
    k_ = std::ceil(pow(std::log2(N), 1.0 / 3.0));
    t_ = std::floor(pow(std::log2(N), 2.0 / 3.0));
    int l = std::ceil(std::log2(N) / t_);

    dhat_ = std::vector<Length>(N, INF);
    dhat_[s] = 0;
    prev_ = std::vector<Vertex>(N, -1);
    tree_size_ = std::vector<Vertex>(N, -1);
    F_ = std::vector<std::vector<Vertex>>(N, std::vector<Vertex>());

    std::vector<Vertex> S;
    S.push_back(s);
    BMSSP(l, INF, S);

    return dhat_;
}


std::pair<Length, std::vector<Vertex>> ShortestPath::BMSSP(int l, Length B, const std::vector<Vertex>& S) {
    if(l == 0) {
        return base_case(B, S);
    }
    auto pw = find_pivots(B, S);
    std::vector<Vertex> P = pw.first; std::vector<Vertex> W = pw.second;

    int M = std::pow(2, (l - 1) * t_);
    BlockHeap D(M, B);
    Length Bd = INF;
    for(int i = 0; i < (int)P.size(); i++) {
        Vertex u = P[i];
        D.insert(u, dhat_[u]);
        Bd = std::min(Bd, dhat_[u]);
    }
    std::unordered_set<Vertex> U;

    while((int)U.size() < k_ * std::pow(2, l * t_) && !D.empty()) {
        auto bs = D.pull();
        Length Bi = bs.first; std::vector<Vertex> Si = bs.second;
        auto bu = BMSSP(l - 1, Bi, Si);
        Length Bid = bu.first; std::vector<Vertex> Ui = bu.second;
        for(int j = 0; j < (int)Ui.size(); j++) {
            U.insert(Ui[j]);
        }

        std::vector<std::pair<Vertex, Length>> K;
        for(int j = 0; j < (int)Ui.size(); j++) {
            Vertex u = Ui[j];
            for(int k = 0; k < (int)G_[u].size(); k++) {
                Vertex v = G_[u][k].first; Length w = G_[u][k].second;
                if(dhat_[v] >= dhat_[u] + w) {
                    Length new_dist = dhat_[u] + w;
                    dhat_[v] = new_dist;
                    if(Bi <= new_dist && new_dist < B) {
                        D.insert(v, new_dist);
                    } else if(Bid <= new_dist && new_dist < Bi) {
                        K.push_back(std::make_pair(v, new_dist));
                    }
                }
            }
        }
        for(int i = 0; i < (int)Si.size(); i++) {
            int u = Si[i];
            if(Bid <= dhat_[u] && dhat_[u] < Bi) K.push_back(std::make_pair(u, dhat_[u]));
        }
        D.batch_prepend(K);
        Bd = Bid;
    }
    Bd = std::min(Bd, B);
    for(int i = 0; i < (int)W.size(); i++) {
        Vertex u = W[i];
        if(dhat_[u] < Bd) U.insert(u);
    }
    return std::make_pair(Bd, std::vector<Vertex>(U.begin(), U.end()));
}

std::pair<Length, std::vector<Vertex>> ShortestPath::base_case(Length B, const std::vector<Vertex>& S) {
    assert(S.size() == 1);

    Vertex x = S[0];

    std::unordered_set<Vertex> U0(S.begin(), S.end());
    Heap H;
    H.push(x, dhat_[x]);

    while(!H.empty() && (int)U0.size() < k_ + 1) {
        auto p = H.top(); H.pop();
        Vertex u = p.first; Length d = p.second;
        U0.insert(u);

        for(int i = 0; i < (int)G_[u].size(); i++) {
            int v = G_[u][i].first; Length w = G_[u][i].second;
            if(dhat_[v] >= dhat_[u] + w && dhat_[u] + w < B) {
                dhat_[v] = dhat_[u] + w;
                H.push(v, dhat_[v]);
            }
        }
    }

    if((int)U0.size() <= k_) {
        return make_pair(B, std::vector<Vertex>(U0.begin(), U0.end()));
    } else {
        Length Bd = -INF;
        std::vector<Vertex> U;
        for(auto u: U0) {
            Bd = std::max(Bd, dhat_[u]);
        }
        for(auto u: U0) {
            if(dhat_[u] < Bd) {
                U.push_back(u);
            }
        }
        return make_pair(Bd, U);
    }
}


std::pair<std::vector<Vertex>, std::vector<Vertex>> ShortestPath::find_pivots(Length B, const std::vector<Vertex>& S) {
    std::unordered_set<Vertex> W(S.begin(), S.end());
    std::unordered_set<Vertex> Wp(S.begin(), S.end());

    for(auto v: W) {
        prev_[v] = -1;
    }

    for(int i = 0; i < k_; i++) {
        std::unordered_set<Vertex> Wi; 
        for(auto u: Wp) {
            for(int k = 0; k < (int)G_[u].size(); k++) {
                Vertex v = G_[u][k].first; Length w = G_[u][k].second;
                if(dhat_[v] >= dhat_[u] + w) {
                    dhat_[v] = dhat_[u] + w;
                    prev_[v] = u;
                    // 論文ではここにdhat_[u] + w < Bのチェックが入るが、恐らく不要。
                    Wi.insert(v);
                }
            }
        }
        for(auto v: Wi) {
            W.insert(v);
        }
        if((int)W.size() >= k_ * (int)S.size()) {
            return std::make_pair(S, std::vector<Vertex>(W.begin(), W.end()));
        }
        Wp = Wi;
    }

    for(auto v: W) {
        tree_size_[v] = -1;
        F_[v].clear();
    }
    for(auto v: W) {
        Vertex u = prev_[v];
        if(u == -1) continue;
        F_[u].push_back(v);
    }
    std::vector<Vertex> P;
    for(int i = 0; i < (int)S.size(); i++) {
        Vertex u = S[i];
        if(find_tree_size(u, tree_size_, F_) >= k_ && prev_[u] == -1) {
            P.push_back(u);
        }
    }
    return std::make_pair(P, std::vector<Vertex>(W.begin(), W.end()));
}