#pragma once

#include <stdint.h>

// needs to be free()'d after usage
extern "C" char* fetch_string(const char* _url, char** _ptr_to_str_str);

extern "C" void* __wasm_export_malloc(uint32_t _size);

