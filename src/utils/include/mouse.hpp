#pragma once

WASM_IMPORT bool is_mouse_button_pressed(uint32_t button);

WASM_IMPORT float get_mouse_position_x();
WASM_IMPORT float get_mouse_position_y();

WASM_IMPORT float get_mouse_velocity_x();
WASM_IMPORT float get_mouse_velocity_y();

WASM_IMPORT float get_mouse_wheel();