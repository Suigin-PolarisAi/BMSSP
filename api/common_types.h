#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <limits>
#include <map>
#include <vector>

using Vertex = int;
using Length = long long;
const Length INF = std::numeric_limits<long long>::max();
using Edge = std::pair<Vertex, Length>;
using Graph = std::vector<std::vector<Edge>>;

#endif  // COMMON_TYPES_H_