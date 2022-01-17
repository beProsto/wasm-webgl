#pragma once

extern "C" {
	// This imports the functions we defined in JS, in the "env" block
	void __wasm_import_console_log_str(const char*);
	void __wasm_import_console_log_num(double);
	void __wasm_import_console_write_str(const char*);
	void __wasm_import_console_write_num(double);
	// calls window.requestAnimationFrame, passing the __wasm_export_winreqanim_exec function as the one to play on the frame
	void __wasm_import_winreqanim_call();
}