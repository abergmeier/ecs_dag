
#pragma once

#include <functional>

namespace ae {
namespace ecs {

class SystemInterface {
};

template <typename T>
concept bool System = std::is_base_of<SystemInterface, T>::value && requires (T t) {
	T::typeId();
};

template <typename T, typename U>
concept bool SystemFunction = requires (T t, U u) {
	std::invoke(t, u);
};

} // namespace ecs
} // namespace ae
