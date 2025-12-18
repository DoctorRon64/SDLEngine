#pragma once

template<typename T>
struct AtomicWrapper {
	std::atomic<T> value;

	AtomicWrapper() : value{} {}
	AtomicWrapper(const std::atomic<T>& other) : value(other.load()) {}
	AtomicWrapper(const AtomicWrapper& other) : value(other.value.load()) {}

	AtomicWrapper& operator=(const AtomicWrapper& other) {
		value.store(other.value.load());
		return *this;
	}
};