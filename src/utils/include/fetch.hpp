#pragma once

#include <stdint.h>

// needs to be free()'d after usage
extern "C" char* fetch_string(const char* _url, char** _ptr_to_str_ptr, uint32_t* _ptr_to_size = 0, void (*_ptr_to_func)() = 0);

extern "C" void* __wasm_export_malloc(uint32_t _size);

extern "C" void __wasm_export_call(void (*_ptr_to_func)());

