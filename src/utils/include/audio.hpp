#pragma once

WASM_IMPORT uint32_t load_audio(const char* url, bool loop, void(*loaded_callback)());
WASM_IMPORT void play_audio(uint32_t _id, float _from = 0.0f);
WASM_IMPORT void stop_audio(uint32_t _id);
WASM_IMPORT void loop_audio(uint32_t _id, bool _loop);
WASM_IMPORT bool is_audio_looped(uint32_t _id);
WASM_IMPORT bool is_audio_playing(uint32_t _id);
WASM_IMPORT float get_audio_duration(uint32_t _id);
WASM_IMPORT void set_audio_position(uint32_t _id, float x, float y, float z);
WASM_IMPORT float get_audio_position_x(uint32_t _id);
WASM_IMPORT float get_audio_position_y(uint32_t _id);
WASM_IMPORT float get_audio_position_z(uint32_t _id);