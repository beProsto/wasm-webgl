#include "utils/include/utils.hpp"
#include "openlibm/include/openlibm.h"
#include "game.hpp"

Game game;

void animFrame() {
	game.update();
}

WASM_EXPORT void Main() {
	game.start();

	__wasm_set_winreqanim_callback(animFrame);
	__wasm_import_winreqanim_call();
}

WASM_EXPORT void __cxa_atexit() {}