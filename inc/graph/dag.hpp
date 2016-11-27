
#include <ecs/system.hpp>
#include <graph/edge.hpp>
#include <message/message.hpp>

namespace ae {

template <typename T>
concept bool Graphable = decltype(T::graph(), bool);

template <typename T>
concept bool GraphableSystem = Graphable<T> && System<T>;

namespace graph {

// Directed acyclic Graph
class Dag {
public:
	// Public interface to edges
	class Edges {
		Edges& operator=(Edges const&) = delete;
		Edges& operator=(Edges&&) = delete;

		void insert(Edge edge);
		template <Message M, GraphableSystem S, Callable Function>
		void emplace(Function function){
			auto messageVertex  = makeVertex<M>();
			auto callbackVertex = makeVertex<S>(function);
			insert(Edge(std::move(messageVertex), std::move(callbackVertex)));
		}

		template <GraphableSystem S, Message M, Callable Function>
		void emplace(Function function) {
			auto callbackVertex = makeVertex<S>(function);
			auto messageVertex  = makeVertex<M>();
			insert(Edge(std::move(callbackVertex), std::move(messageVertex)));
		}

		template <GraphableSystem FromSystem, GraphableSystem ToSystem, Callable FromFunction, Callable ToFunction>
		void emplace(FromFunction from, ToFunction to) {
			auto fromVertex = makeVertex<FromSystem>(from);
			auto toVertex   = makeVertex<ToSystem>(to);
			insert(Edge(std::move(fromVertex), std::move(toVertex)));
		}

	private:
		Dag& dag_;
	};

	class Vertices {
		template <typename... Args>
		void emplace(Args... args) {
			insert(Vertex(std::forward<Args>(args)...));
		}
		void insert(Vertex vertex);
	private:
		Dag& dag_;
	};

	Dag operator+(Dag&& other);
	Dag& operator+=(Dag&& other);
public:
	Edges edges;
private:
	std::vector<Vertex> vertices_;
	std::vector<Edge> edges_;
};

void
dfs(Vertex const& begin, Vertex const& end) {
	auto discovered = std::unordered_set<Vertex const*>();
	auto stack = std::stack<Vertex const*>();
	stack.push(&begin);
	auto adjacentEdges = std::vector<Edge const*>();
	while (!stack.empty()) {
		adjacentEdges.clear();
		auto vertex = stack.pop();
		auto discoveredIt = discovered.find(&vertex);
		if (discoveredIt != discovered.cend())
			continue; // Already discovered
		discovered.insert(&vertex);
		for (auto& edge : graph.adjacent(vertex, adjacentEdges)) {
			stack.push(&edge.to);
		}
	}
}




} // namespace graph
} // namespace ae



