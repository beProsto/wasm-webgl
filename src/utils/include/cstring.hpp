#pragma once

inline size_t strlen_4bytes(const char* _str_start) {
	const char* str_end = _str_start;
    while(true) {
        unsigned x = *(unsigned*)str_end;
        if((x & 0xFF) == 0) return str_end - _str_start; 
        if((x & 0xFF00) == 0) return str_end - _str_start + 1;
        if((x & 0xFF0000) == 0) return str_end - _str_start + 2;
        if((x & 0xFF000000) == 0) return str_end - _str_start + 3;
        str_end += 4;
    }
}

inline size_t strlen_1byte(const char* _str_start) {
	const char* str_end = _str_start;

	for(; *str_end; str_end++);

	return str_end - _str_start;
}

inline size_t strlen(const char* _str) {
	return strlen_4bytes(_str);
}