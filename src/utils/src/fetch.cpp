#include "../include/fetch.hpp"
#include "../include/malloc.hpp"
#include <stdint.h>

extern "C" void __wasm_export_call(void (*_ptr_to_func)()) {
	_ptr_to_func();
}