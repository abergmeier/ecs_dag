
#include <graph/vertex.hpp>

namespace ae {
namespace graph {

template<class> struct always_false : std::false_type {};

bool
operator<(Vertex const& lhs, Vertex const& rhs) {
	auto const lhsIndex = lhs.index();
	auto const rhsIndex = rhs.index();

	if (lhsIndex < rhsIndex) {
		return true;
	}

	if (lhsIndex > rhsIndex) {
		return false;
	}

	return std::visit([&](auto&& arg) {
		using T = std::remove_cv_t<std::remove_reference_t<decltype(arg)>>;
		if constexpr (std::is_same_v<T, SystemFunctionBinding>)
			return std::get<SystemFunctionBinding>(lhs) < std::get<SystemFunctionBinding>(rhs);
		else if constexpr (std::is_same_v<T, MessageId>)
			return std::get<MessageId>(lhs) < std::get<MessageId>(rhs);
		else if constexpr (std::is_same_v<T, SystemId>)
			return std::get<SystemId>(lhs) < std::get<SystemId>(rhs);
		else 
			static_assert(always_false<T>::value, "non-exhaustive visitor!");
	}, lhs);
}

} // namespace graph
} // namespace ae
