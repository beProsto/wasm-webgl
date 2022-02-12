#pragma once

WASM_IMPORT bool __wasm_import_is_mouse_button_pressed(uint32_t button);

WASM_IMPORT float __wasm_import_get_mouse_position(uint32_t i);
WASM_IMPORT float __wasm_import_get_mouse_velocity(uint32_t i);

WASM_IMPORT float get_mouse_wheel();

WASM_IMPORT uint32_t get_mouse_ammount();

inline float is_mouse_button_pressed(uint32_t _button, uint32_t _mouseId = 0) {
	return __wasm_import_is_mouse_button_pressed(_mouseId * 5 + _button);
};
inline float get_mouse_position_x(uint32_t _mouseId = 0) {
	return __wasm_import_get_mouse_position(_mouseId * 2 + 0);
};
inline float get_mouse_position_y(uint32_t _mouseId = 0) {
	return __wasm_import_get_mouse_position(_mouseId * 2 + 1);
};
inline float get_mouse_velocity_x(uint32_t _mouseId = 0) {
	return __wasm_import_get_mouse_velocity(_mouseId * 2 + 0);
};
inline float get_mouse_velocity_y(uint32_t _mouseId = 0) {
	return __wasm_import_get_mouse_velocity(_mouseId * 2 + 1);
};