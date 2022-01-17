#include "utils/include/utils.hpp"

uint8_t display[640*360*4];

extern "C" uint8_t* getDisplayPtr() {
	return &display[0];
}

void animationFrame() {

}

extern "C" void Main() {
	cout << "Hejka naklejka!\n";

	for(size_t i = 0; i < 640*360*4; i+=4) {
		display[i+0] = 255;
		display[i+1] = 0;
		display[i+2] = 255;
		display[i+3] = 255;
	}

	__wasm_set_winreqanim_callback(animationFrame);
	__wasm_import_winreqanim_call();
}