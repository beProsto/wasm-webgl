#include "utils/include/utils.hpp"

#include "game.hpp"

uint32_t loaded = 0;
uint32_t to_load = 0; 

WASM_EXPORT void loading_callback();
void start_app();
WASM_IMPORT void after_loaded();

// The entry point for our application
WASM_EXPORT void begin() {
	// We want to make sure newly created objects can't have the same ID,
	// so that they can be bound.
	g_BoundShader = UINT32_MAX;
	g_BoundVertexBuffer = UINT32_MAX;

	// load all the needed files as text (strings)
	fetch_string("./assets/shaders/shader.vert", &g_VertexShaderSource); to_load++;
	fetch_string("./assets/shaders/shader.frag", &g_FragmentShaderSource, nullptr, []{ 
			console_log("loaded callback ^~^"); 
	}); to_load++;
	g_Music = load_audio("./assets/audio/music.mp3", true, loading_callback); to_load++;
}

// called every time an asset is loaded
WASM_EXPORT void loading_callback() {
	loaded++;
	if(loaded == to_load) {
		start_app();
	}
}

// From game.hpp, contains objects and functions regarding the application
Game* game;
// To be called every frame
void anim_frame(float time) { game->update(time); }

// When everything is loaded and ready
void start_app() {
	// We "create" the game - initialise it
	game = new Game();

	// We don't need the strings we've loaded anymore
	free(g_VertexShaderSource);
	free(g_FragmentShaderSource);

	// Everything's loaded
	after_loaded();
}

WASM_EXPORT void begin_game() {
	// We use the "start" function inside the game object
	game->start();

	// We make game's update function run every frame
	window_animation_callback(anim_frame);
}

// Needed for the programme to work
WASM_EXPORT void __cxa_atexit() {}
WASM_EXPORT void* _Znwm(size_t _s) { return malloc(_s); }
WASM_EXPORT void _ZdlPv(void* _p) { free(_p); }