#pragma once

// ALL THE CREDIT FOR THIS FILE GOES TO Max Klein (https://github.com/maxkl/) 
// FROM THE PROJECT https://github.com/maxkl/wasm-malloc

#include <stddef.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);