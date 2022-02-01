#include "utils/include/utils.hpp"

#include "game.hpp"

uint32_t loaded = 0;
const uint32_t to_load = 2; 

WASM_EXPORT void loading_callback();
void start_app();

// The entry point for our application
WASM_EXPORT void begin() {
	// We want to make sure newly created objects can't have the same ID,
	// so that they can be bound.
	g_BoundShader = UINT32_MAX;
	g_BoundVertexBuffer = UINT32_MAX;

	// load all the needed files as text (strings)
	fetch_string("./shader.vert", &g_VertexShaderSource);
	fetch_string("./shader.frag", &g_FragmentShaderSource);
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

	// We use the "start" function inside the game object
	game->start();

	// We make game's update function run every frame
	window_animation_callback(anim_frame);
}


// Needed for the programme to work
WASM_EXPORT void __cxa_atexit() {}
WASM_EXPORT void _Znwm() {}