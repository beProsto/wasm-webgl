#include "../include/cstring.hpp"

extern "C" uint32_t __wasm_export_strlen(const char* _str) {
	return strlen(_str);
}