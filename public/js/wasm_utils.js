// Make the audio
let music = new PlayableAudio("./assets/audio/music.mp3", [0.0, 0.0, 0.0], true);

class ModuleUtils {
	constructor() {
		// this is our module
		this.moduleref = {};
		// reference to a canvas
		this.canv = {};
		// reference to a context
		this.gl = {};

		// buffer for the text 
		this.console_write_buffer = "";
		// window's frame's identifier
		this.frameId = 0;
		// animation frame function
		this.animFrame = () => {};
		// storage for ever gl object
		this.glObjects = [];

		// stores the currently bound WebGLProgram
		// this *was* supposed to be a temporary measure
		// it will stay like this
		this.boundProgram = {};
	}

	// functions to import to our wasm code
	getImports() {
		let imports = { env: {
			// logs a string
			__wasm_import_console_log_str: (_ptr) => {
				const text_buffer = this.strToTxt(_ptr);
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
				// this function will play out once all the assets are loaded
				gameLoaded();
				// this function will play out every frame
				this.animFrame = (time) => {

					music.play();
					// this.canv.requestFullscreen();
					// this.canv.requestPointerLock();

					this.moduleref.instance.exports.__wasm_export_winreqanim_callback_execute(time);

					this.frameId = window.requestAnimationFrame(this.animFrame);
				};
				this.frameId = window.requestAnimationFrame(this.animFrame);
			},
			// evaluates a string as js
			__wasm_import_eval: (_ptr) => {
				let text_buffer = this.strToTxt(_ptr);
				eval(text_buffer);
			},
			// fetch'es a string asynchronously
			fetch_string: (_str, _ptrToStrPtr, _ptrToSize, _ptrToFunc) => {
				// converts the string of the requested url into js text
				const url = this.strToTxt(_str);
				// fetches the file asynchronously
				this.fetchText(url).then((str) => {
					// allocates space for the new string inside the module's memory
					const ptr = this.moduleref.instance.exports.__wasm_export_malloc(str.length + 1);
					// encodes the string - converts it into a byte array
					const strBuf = new TextEncoder().encode(str);
					// places the encoded string in the allocated memory
					const outBuf = new Uint8Array(this.moduleref.instance.exports.memory.buffer, ptr, strBuf.length);
					for(let i = 0; i < strBuf.length; i++) {
						outBuf[i] = strBuf[i];
					}

					// places the pointer to the string in the requested pointer 
					new Uint32Array(this.moduleref.instance.exports.memory.buffer, _ptrToStrPtr, _ptrToStrPtr+4)[0] = ptr;
					// places the size of the string in the requested integer 
					if(_ptrToSize != 0) {
						new Uint32Array(this.moduleref.instance.exports.memory.buffer, _ptrToSize, _ptrToSize+4)[0] = str.length + 1;
					}

					// calls the specified callback upon loading
					if(_ptrToFunc != 0) {
						this.moduleref.instance.exports.__wasm_export_call(_ptrToFunc);
					}
					
					// calls the general file loading callback
					this.moduleref.instance.exports.loading_callback();
				});
			},
			// Keyboard and Mouse bindings
			is_key_pressed: (_keycode) => {
				return pressedKeys[_keycode];
			},
			is_mouse_button_pressed: (_button) => {
				return mouse.pressedButtons[_button];
			},
			get_mouse_position_x: () => {
				return mouse.position[0];
			},
			get_mouse_position_y: () => {
				return mouse.position[1];
			},
			get_mouse_velocity_x: () => {
				return mouse.velocity[0];
			},
			get_mouse_velocity_y: () => {
				return mouse.velocity[1];
			},
			get_mouse_wheel: () => {
				return mouse.wheel;
			},
			// Canvas size and stuff
			get_width: () => {
				return this.canv.width;
			},
			get_height: () => {
				return this.canv.height;
			},
			// webgl imports
			
			// I wonder if there's some way to optimise this.
			// One way i can imagine would be to create some
			// general purpose `genWebglBind` function, that
			// will take in the function's name and then
			// modify it's name (like delete the first two 
			// characters and minimasie the first one left)
			// and then use that generated name with the same
			// arguments, but a prefix of `this.gl.`.
			// That's just an idea, but maybeee it could work for
			// some if not most of these, lol.
			
			// Common stuff
			glClearColor: (r,g,b,a) => {
				this.gl.clearColor(r,g,b,a);
			},
			glClear: (m) => {
				this.gl.clear(m);
			},
			glViewport: (x,y,w,h) => {
				this.gl.viewport(x,y,w,h);
			},
			glDrawArrays: (m,f,c) => {
				this.gl.drawArrays(m,f,c);
			},

			// Shaders
			glCreateShader: (k) => {
				this.glObjects.push(this.gl.createShader(k));
				return this.glObjects.length-1;
			},
			glShaderSource: (id,str) => {
				this.gl.shaderSource(this.glObjects[id],this.strToTxt(str));
			},
			glCompileShader: (id) => {
				this.gl.compileShader(this.glObjects[id]);

				// Debug purposes:
				console.log('Shader compiled successfully: ' + this.gl.getShaderParameter(this.glObjects[id], this.gl.COMPILE_STATUS));
				console.log('Shader compiler log: ' + this.gl.getShaderInfoLog(this.glObjects[id]));
			},
			glDeleteShader: (id) => {
				this.gl.deleteShader(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},

			// Programmes
			glCreateProgram: () => {
				this.glObjects.push(this.gl.createProgram());
				return this.glObjects.length-1;
			},
			glAttachShader: (id,shader) => {
				this.gl.attachShader(this.glObjects[id],this.glObjects[shader]);
			},
			glLinkProgram: (id) => {
				this.gl.linkProgram(this.glObjects[id]);

				// Debug purposes:
				console.log("Program link status: " + this.gl.getProgramParameter(this.glObjects[id], this.gl.LINK_STATUS));
				console.log("Program Linker log: " + this.gl.getProgramInfoLog(this.glObjects[id]));
			},
			glValidateProgram: (id) => {
				this.gl.validateProgram(this.glObjects[id]);

				// Upon validation we make up a list of uniform locations (both assigned by Id and Name)
				const numUniforms = this.gl.getProgramParameter(this.glObjects[id], this.gl.ACTIVE_UNIFORMS);
				console.log("We got: " + numUniforms + " uniforms!")
				this.glObjects[id].uniformLocsById = [];
				this.glObjects[id].uniformIdsByName = {};
				for(let i = 0; i < numUniforms; ++i) {
					const info = this.gl.getActiveUniform(this.glObjects[id], i);
					console.log('name:', info.name, 'type:', info.type, 'size:', info.size);
					this.glObjects[id].uniformLocsById[i] = this.gl.getUniformLocation(this.glObjects[id], info.name);
					this.glObjects[id].uniformIdsByName[info.name] = i;
				}
			},
			glUseProgram: (id) => {
				this.gl.useProgram(this.glObjects[id]);
				this.boundProgram = this.glObjects[id];
			},
			glDeleteProgram: (id) => {
				this.gl.deleteProgram(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},
			// Programmes - Uniforms
			glGetUniformLocation: (program_id, str) => {
				const name = this.strToTxt(str);
				if(typeof this.glObjects[program_id].uniformIdsByName[name] !== 'undefined') {
					return this.glObjects[program_id].uniformIdsByName[name];
				}
				else {
					return -1;
				}
			},
			glUniform1f: (loc, v0) => {
				this.gl.uniform1f(this.boundProgram.uniformLocsById[loc], v0);
			},
			glUniform1i: (loc, v0) => {
				this.gl.uniform1i(this.boundProgram.uniformLocsById[loc], v0);
			},
			glUniform2f: (loc, v0, v1) => {
				this.gl.uniform2f(this.boundProgram.uniformLocsById[loc], v0, v1);
			},
			glUniform2i: (loc, v0, v1) => {
				this.gl.uniform2i(this.boundProgram.uniformLocsById[loc], v0, v1);
			},
			glUniform3f: (loc, v0, v1, v2) => {
				this.gl.uniform3f(this.boundProgram.uniformLocsById[loc], v0, v1, v2);
			},
			glUniform3i: (loc, v0, v1, v2) => {
				this.gl.uniform3i(this.boundProgram.uniformLocsById[loc], v0, v1, v2);
			},
			glUniform4f: (loc, v0, v1, v2, v3) => {
				this.gl.uniform4f(this.boundProgram.uniformLocsById[loc], v0, v1, v2, v3);
			},
			glUniform4i: (loc, v0, v1, v2, v3) => {
				this.gl.uniform4i(this.boundProgram.uniformLocsById[loc], v0, v1, v2, v3);
			},

			// Vertex Arrays
			glCreateVertexArray: () => {
				this.glObjects.push(this.gl.createVertexArray());
				return this.glObjects.length-1;
			},
			glBindVertexArray: (id) => {
				this.gl.bindVertexArray(this.glObjects[id]);
			},
			glVertexAttribPointer: (index, size, type, normalized, stride, offset) => {
				this.gl.vertexAttribPointer(index, size, type, normalized, stride, offset);
			},
			glEnableVertexAttribArray: (index) => {
				this.gl.enableVertexAttribArray(index);
			},
			glDeleteVertexArray: (id) => {
				this.gl.deleteVertexArray(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},

			// Buffers
			glCreateBuffer: () => {
				this.glObjects.push(this.gl.createBuffer());
				return this.glObjects.length-1;
			},
			glBindBuffer: (kind,id) => {
				this.gl.bindBuffer(kind,this.glObjects[id]);
			},
			glBufferData: (kind,size,data,usage) => {
				const dataArray = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				this.gl.bufferData(kind, dataArray, usage, data, size);
			},
			glDeleteBuffer: (id) => {
				this.gl.deleteBuffer(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},
		} };
		return imports;
	}

	strToTxt(str) {
		const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer, str, this.moduleref.instance.exports.__wasm_export_strlen(str));
		let text_buffer = new TextDecoder().decode(memory_buffer);
		return text_buffer;
	}

	async fetchText(url) {
		let response = await fetch(url);
		let responseText = await response.text();
		return responseText;
	}
}