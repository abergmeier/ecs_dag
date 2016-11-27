
#include <graph/vertex.hpp>

namespace ae {
namespace graph {

struct Edge {
	Edge(Vertex from, Vertex to);
	Vertex const from;
	Vertex const to;
};

bool operator<(Edge const& lhs, Edge const& rhs);

} // namespace graph
} // namespace ae

