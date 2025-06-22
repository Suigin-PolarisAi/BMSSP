#include "api/common_types.h"
#include "api/shortest_path.h"

#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int N, M, s;
    std::cin >> N >> M >> s;
    Graph G(N);
    for(int i = 0; i < M; i++) {
        int a, b; Length c;
        std::cin >> a >> b >> c;
        G[a].push_back(std::make_pair(b, c));
    }
    ShortestPath shortest_path(G);
    auto ans = shortest_path.get(s);
    for(int i = 0; i < N; i++) {
        if(ans[i] == INF) {
            std::cout << "INF" << std::endl;
        } else {
            std::cout << ans[i] << std::endl;
        }
    }
    return 0;
}