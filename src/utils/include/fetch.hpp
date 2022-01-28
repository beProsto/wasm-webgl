#pragma once

extern "C" char* fetch(const char* _url);

extern "C" void __wasm_export_malloc(uint32_t _size);