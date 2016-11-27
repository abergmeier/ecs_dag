
#include <graph/edge.hpp>

namespace ae {
namespace graph {

Edge::Edge(Vertex from, Vertex to)
	: from(std::move(from))
	, to(std::move(to))
{}

bool
operator<(Edge const& lhs, Edge const& rhs) {
	return lhs.from < rhs.from || lhs.to < rhs.to;
}

} // namespace graph
} // namespace ae

