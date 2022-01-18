#pragma once

template<typename T, typename Y>
inline T max(T _a, Y _b) {
	return _a > _b ? _a : _b;
}

template<typename T, typename Y>
inline T min(T _a, Y _b) {
	return _a < _b ? _a : _b;
}
