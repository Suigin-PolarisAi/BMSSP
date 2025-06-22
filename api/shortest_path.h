#ifndef SHORTEST_PATH_H_
#define SHORTEST_PATH_H_

#include "api/common_types.h"
#include <vector>

/** 論文のアルゴリズムの実装 */
class ShortestPath {
    public:
        ShortestPath(const Graph& G);
        /** 始点sから全頂点への距離が格納された配列を返す。 */
        std::vector<Length> get(Vertex s);

    private:
        int t_;
        int k_;
        std::vector<Length> dhat_;
        Graph G_;

        /** 論文中のAlgorithm 3 */
        std::pair<Length, std::vector<Vertex>> BMSSP(int l, Length B, const std::vector<Vertex>& S);
        /** 論文中のAlgorithm 2 */
        std::pair<Length, std::vector<Vertex>> base_case(Length B, const std::vector<Vertex>& S);
        /** 論文中のAlgorithm 1 */
        std::pair<std::vector<Vertex>, std::vector<Vertex>> find_pivots(Length B, const std::vector<Vertex>& S);

        std::vector<Vertex> prev_;
        std::vector<int> tree_size_;
        std::vector<std::vector<Vertex>> F_;
};

#endif  // SHORTEST_PATH_H_