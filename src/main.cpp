#include "utils/include/utils.hpp"
// #include "game.hpp"

float time = 0.0f;

void animFrame() {
	time += 0.01f;
	// if the number reaches or exceeds 1.0, it will be shortened to only it's post decimal point numbers
	time = time - (float)(int)time;
	glClearColor(time, time, time, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

WASM_EXPORT void Main() {
	cout << "Hejka naklejka!\n";

	string astring("Would you like to sign my petition?");

	cout << astring << endl;

	memcpy(&astring[0], &astring[18], astring.size() - 17);

	astring[astring.size()-19] = '.'; // change the ? for a .
	astring[0] -= 32; // capitalise the first character

	cout << astring << endl;

	// for(uint8_t i = 0; i < 255; i++) {
	// 	cout << i << ": " << (char)i << endl;
	// }

	__wasm_set_winreqanim_callback(animFrame);
	__wasm_import_winreqanim_call();
}