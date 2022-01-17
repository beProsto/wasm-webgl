class ModuleUtils {
	constructor() {
		// this is our module
		this.moduleref = {};
		// reference to a context
		this.c2d = {};
		// reference to an image
		this.img = 0;

		// buffer for the text 
		this.console_write_buffer = "";

		this.frameId = 0;
		this.animFrame = () => {};
	}

	// functions to import to our wasm code
	getImports() {
		return { env: {
			// logs a string
			__wasm_import_console_log_str: (_ptr) => {
				const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				let text_buffer = "";
				
				for(; memory_buffer[_ptr] != 0; _ptr++) {
					text_buffer += String.fromCharCode(memory_buffer[_ptr]);
				}

				console.log(text_buffer);
			},
			// logs a number
			__wasm_import_console_log_num: (_num) => {
				console.log(_num);
			},
			// writes a string to a buffer that is logged upon detecting a new line character
			__wasm_import_console_write_str: (_ptr) => {
				const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				
				for(; memory_buffer[_ptr] != 0; _ptr++) {
					if(memory_buffer[_ptr] == 10) {
						console.log(this.console_write_buffer);
						this.console_write_buffer = "";
					}
					else {
						this.console_write_buffer += String.fromCharCode(memory_buffer[_ptr]);
					}
				}
			},
			// writes a number to a buffer that is logged upon detecting a new line character
			__wasm_import_console_write_num: (_num) => {
				this.console_write_buffer += _num;
			},
			// starts a window.requireAnimationFrame loop called on a specific funtion exported by the module
			__wasm_import_winreqanim_call: () => {
				this.animFrame = () => {
					this.moduleref.instance.exports.__wasm_export_winreqanim_callback_execute();

					this.c2d.putImageData(this.img, 0, 0);

					this.frameId = window.requestAnimationFrame(this.animFrame);
				}
				this.frameId = window.requestAnimationFrame(this.animFrame);
			}
		} };
	}
}