#pragma once

#include "imports.hpp"
#include "malloc.hpp"
#include <stdint.h>

// As this is a c++ file, and we're not exporting or importing any of these functions to or from js
// - we can do inlines and define multiple functions with the same name. :D

// CONSOLE LOGGING //

inline void console_log(const char* _str) {
	__wasm_import_console_log_str(_str);
}
inline void console_log(char _c) {
	char buffer[2] = {_c, '\0'};
	__wasm_import_console_log_str(buffer);
}
inline void console_log(int _a) {
	__wasm_import_console_log_num((double)_a);
}
inline void console_log(float _a) {
	__wasm_import_console_log_num((double)_a);
}

// inline size_t strlen(const char* _str) {
// 	return __builtin_strlen(_str);
// }

// class string {
// public:
// 	string(const char* buff);
// 	string(unsigned int len);
// 	~string();


// private:
// 	char* buffer;
// };

class console_writer {
public:
	console_writer& operator<<(const char* _str) {
		__wasm_import_console_write_str(_str);
		return *this;
	}
	console_writer& operator<<(char _c) {
		char buffer[2] = {_c, '\0'};
		__wasm_import_console_write_str(buffer);
		return *this;
	}
	template<typename T>
	console_writer& operator<<(T _a) {
		__wasm_import_console_write_num(static_cast<double>(_a));
		return *this;
	}
};

static console_writer cout;

constexpr const char endl = '\n';