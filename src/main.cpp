#define GLEW_STATIC
#include "utils/include/utils.hpp"
// #include "game.hpp"


float time = 0.0f;

void animFrame() {
	time += 0.1f;
	time = time - (float)(int)time;
	glClearColor(time, time, time, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

extern "C" void Main() {
	cout << "Hejka naklejka!\n";

	__wasm_set_winreqanim_callback(animFrame);
	__wasm_import_winreqanim_call();
}