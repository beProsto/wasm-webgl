#include "utils/include/utils.hpp"
#include "openlibm/include/openlibm.h"
// #include "game.hpp"

float time = 0.0f;

void animFrame() {
	time += 0.01f;
	float sinusoid = (sin(time) + 1.0) / 2.0;

	glClearColor(sinusoid, sinusoid, sinusoid, 1.0f);
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

	memset(&astring[0], 0, 5);

	cout << astring << endl;

	__wasm_set_winreqanim_callback(animFrame);
	__wasm_import_winreqanim_call();
}