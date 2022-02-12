#pragma once

WASM_IMPORT bool __wasm_import_is_mouse_button_pressed(uint32_t button);

WASM_IMPORT float __wasm_import_get_mouse_position(uint32_t i);
WASM_IMPORT float __wasm_import_get_mouse_velocity(uint32_t i);

WASM_IMPORT float get_mouse_wheel();

WASM_IMPORT uint32_t get_mouse_ammount();

inline float is_mouse_button_pressed(uint32_t button, uint32_t mouse_id = 0) {
	return __wasm_import_is_mouse_button_pressed(mouse_id * 5 + button);
};
inline float get_mouse_position_x(uint32_t mouse_id = 0) {
	return __wasm_import_get_mouse_position(mouse_id * 2 + 0);
};
inline float get_mouse_position_y(uint32_t mouse_id = 0) {
	return __wasm_import_get_mouse_position(mouse_id * 2 + 1);
};
inline float get_mouse_velocity_x(uint32_t mouse_id = 0) {
	return __wasm_import_get_mouse_velocity(mouse_id * 2 + 0);
};
inline float get_mouse_velocity_y(uint32_t mouse_id = 0) {
	return __wasm_import_get_mouse_velocity(mouse_id * 2 + 1);
};

struct AABB {float x; float y; float w; float h;};
inline bool get_mouse_id_in_area(uint32_t& mouse_id_ref, AABB aabb) {
	uint32_t mice = get_mouse_ammount();
	for(uint32_t mid = 0; mid < mice; mid++) {
		float x = get_mouse_position_x(mid);
		float y = get_mouse_position_y(mid);
		// if touch is outside the boundaries, continue on with the search
		if(x < aabb.x || x > aabb.x + aabb.w || y < aabb.y || y > aabb.y + aabb.h) {
			continue;
		}

		// touch inside the boundaries was found
		mouse_id_ref = mid;
		return true;
	}
	// touch inside the boundaries was not found
	return false;
}

struct Circle {float x; float y; float r;};
inline bool get_mouse_id_in_area(uint32_t& mouse_id_ref, Circle circle) {
	uint32_t mice = get_mouse_ammount();
	for(uint32_t mid = 0; mid < mice; mid++) {
		float x = get_mouse_position_x(mid);
		float y = get_mouse_position_y(mid);

		// if touch is outside the boundaries, continue on with the search
		float outx = x-circle.x;
		float outy = y-circle.y;
		if(sqrtf(outx*outx + outy*outy) > circle.r) {
			continue;
		}

		// touch inside the boundaries was found
		mouse_id_ref = mid;
		return true;
	}
	return false;
}