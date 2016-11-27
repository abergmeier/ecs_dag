
#include <cstdint>

#include <variant>

#include <ecs/system.hpp>
#include <message/message.hpp>

namespace ae {
namespace graph {

struct SystemFunctionBinding {
	std::size_t systemId;
	void* function;
};

class MessageId {
public:
	MessageId(std::size_t value);
private:
	std::size_t value_;
};

class SystemId {
};

using Vertex = std::variant<SystemFunctionBinding, SystemId, MessageId>;

template <message::Message M>
inline Vertex
makeVertex() {
	auto vertex = Vertex();
	vertex.emplace<MessageId>(M::typeId());
	return vertex;
}

template <ecs::System S, typename F>
inline Vertex
makeVertex(F function) requires ecs::SystemFunction<F, S> {
	auto vertex = Vertex();
	auto binding = SystemFunctionBinding();
	binding.systemId = S::typeId();
	binding.function = &function;
	vertex.emplace<SystemFunctionBinding>(std::move(binding));
	return vertex;
}

inline bool
operator<(SystemFunctionBinding const& lhs, SystemFunctionBinding const& rhs) {
	if (lhs.systemId < rhs.systemId)
		return true;

	if (lhs.systemId > rhs.systemId)
		return false;

	return lhs.function < rhs.function;
}

inline bool
operator<(MessageId const& lhs, MessageId const& rhs) {
	return lhs < rhs;
}

inline bool
operator<(SystemId const& lhs, SystemId const& rhs) {
	return lhs < rhs;
}

bool operator<(Vertex const& lhs, Vertex const& rhs);

} // namespace graph
} // namespace ae
