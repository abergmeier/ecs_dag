
#pragma once

namespace ae {
namespace message {

template <typename T>
concept bool Message = requires (T t) {
	T::typeId();
};

} // namespace message
} // namespace ae

