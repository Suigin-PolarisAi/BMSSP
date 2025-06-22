#ifndef SHORTEST_PATH_H_
#define SHORTEST_PATH_H_

#include "api/common_types.h"
#include <vector>

class ShortestPath {
    public:
        ShortestPath(const Graph& G);
        std::vector<Length> get(Vertex s);

    private:
        int t_;
        int k_;
        std::vector<Length> dhat_;
        Graph G_;

        std::pair<Length, std::vector<Vertex>> BMSSP(int l, Length B, const std::vector<Vertex>& S);
        std::pair<Length, std::vector<Vertex>> base_case(Length B, const std::vector<Vertex>& S);
        std::pair<std::vector<Vertex>, std::vector<Vertex>> find_pivots(Length B, const std::vector<Vertex>& S);

        std::vector<Vertex> prev_;
        std::vector<int> tree_size_;
        std::vector<std::vector<Vertex>> F_;
};

#endif  // SHORTEST_PATH_H_