#include "../include/fetch.hpp"
#include "../include/malloc.hpp"
#include <stdint.h>

extern "C" void* __wasm_export_malloc(uint32_t _size) {
	return malloc(_size);
}