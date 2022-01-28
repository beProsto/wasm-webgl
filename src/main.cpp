#include "utils/include/utils.hpp"
#include "openlibm/include/openlibm.h"
#include "game.hpp"

// From game.hpp, contains objects and functions regarding the application
Game* game;

// To be called every frame
void anim_frame() {
	game->update();
}

WASM_EXPORT void Main() {
	// We want to make sure newly created objects can't have the same ID,
	// so that they can be bound.
	g_BoundShader = UINT32_MAX;
	g_BoundVertexBuffer = UINT32_MAX;

	// We "create" the game - initialise it
	// As a fun fact; this means that our malloc is
	// actually used by c++ as the allocator UwU
	game = new Game();

	// We use the "start" function inside the game object
	game->start();

	// We make game's update function run every frame
	window_animation_callback(anim_frame);
}

// Needed for the programme to work
WASM_EXPORT void __cxa_atexit() {}
WASM_EXPORT void _Znwm() {}