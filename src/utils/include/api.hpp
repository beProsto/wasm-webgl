#pragma once

#include "imports.hpp"
#include "malloc.hpp"
#include <stdint.h>

#define WASM_EXPORT extern "C"

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

class string {
public:
	string() {
		m_Str = nullptr;
		m_Size = 0;
	}
	string(const char* _str) {
		m_Size = strlen(_str);
		m_Str = (char*)malloc(m_Size + 1);
		// m_Str[m_Size] = '\0';
		memcpy(m_Str, _str, m_Size);
	}
	string(size_t _size, char _toFillWith = '\0') {
		m_Size = _size;
		m_Str = (char*)malloc(m_Size + 1);
		m_Str[m_Size] = '\0';
		m_Str = (char*)amemset((void*)m_Str, (uint8_t)_toFillWith, m_Size);
	}
	~string() {
		if(m_Str != nullptr) {
			free(m_Str);
		}
	}
	
	size_t size() const {
		return m_Size;
	}

	const char* cstr() const {
		return &m_Str[0];
	}

	char& operator[](size_t _i) {
		return m_Str[_i];
	}
	const char& operator[](size_t _i) const {
		return m_Str[_i];
	}

private:
	char* m_Str;
	size_t m_Size;
};

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
	console_writer& operator<<(const string& _c) {
		__wasm_import_console_write_str(_c.cstr());
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
