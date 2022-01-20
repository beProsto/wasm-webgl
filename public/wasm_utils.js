class ModuleUtils {
	constructor() {
		// this is our module
		this.moduleref = {};
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
	}

	// functions to import to our wasm code
	getImports() {
		let imports = { env: {
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

					this.frameId = window.requestAnimationFrame(this.animFrame);
				}
				this.frameId = window.requestAnimationFrame(this.animFrame);
			},
			// evaluates a string as js
			__wasm_import_eval: (_ptr) => {
				const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
				let text_buffer = "";
				
				for(; memory_buffer[_ptr] != 0; _ptr++) {
					text_buffer += String.fromCharCode(memory_buffer[_ptr]);
				}

				eval(text_buffer);
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
			glCreateShader: (k) => {
				this.glObjects.push(this.gl.createShader(k));
				return this.glObjects.length-1;
			},
			glShaderSource: (id,str) => {
				this.gl.shaderSource(this.glObjects[id],this.strToTxt(str));
			},
			glCompileShader: (id) => {
				this.gl.compileShader(this.glObjects[id]);

				const compiled = this.gl.getShaderParameter(this.glObjects[id], this.gl.COMPILE_STATUS);
				console.log('Shader compiled successfully: ' + compiled);
				const compilationLog = this.gl.getShaderInfoLog(this.glObjects[id]);
				console.log('Shader compiler log: ' + compilationLog);
			},
			glDeleteShader: (id) => {
				this.gl.deleteShader(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},
			glCreateProgram: () => {
				this.glObjects.push(this.gl.createProgram());
				return this.glObjects.length-1;
			},
			glAttachShader: (id,shader) => {
				this.gl.attachShader(this.glObjects[id],this.glObjects[shader]);
			},
			glLinkProgram: (id) => {
				this.gl.linkProgram(this.glObjects[id]);
			},
			glValidateProgram: (id) => {
				this.gl.validateProgram(this.glObjects[id]);
			},
			glUseProgram: (id) => {
				this.gl.useProgram(this.glObjects[id]);
			},
			glDeleteProgram: (id) => {
				this.gl.deleteProgram(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},
			glCreateVertexArray : () => {
				this.glObjects.push(this.gl.createVertexArray());
				return this.glObjects.length-1;
			},
			glBindVertexArray : (id) => {
				this.gl.bindVertexArray(this.glObjects[id]);
			},
			glVertexAttribPointer : (index, size, type, normalized, stride, offset) => {
				this.gl.vertexAttribPointer(index, size, type, normalized, stride, offset);
			},
			glEnableVertexAttribArray : (index) => {
				this.gl.enableVertexAttribArray(index);
			},
			glDeleteVertexArray : (id) => {
				this.gl.deleteVertexArray(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},
			glCreateBuffer : () => {
				this.glObjects.push(this.gl.createBuffer());
				return this.glObjects.length-1;
			},
			glBindBuffer : (kind,id) => {
				this.gl.bindBuffer(kind,this.glObjects[id]);
			},
			glBufferData : (kind,size,data,usage) => {
				const dataArray = new Uint8ClampedArray(this.moduleref.instance.exports.memory, data, size);
				this.gl.bufferData(kind, dataArray, usage);
			},
			glDeleteBuffer : (id) => {
				this.gl.deleteBuffer(this.glObjects[id]);
				delete this.glObjects[id];
				// this.glObjects.splice(id, 1);
			},
		} };
		return imports;
	}

	strToTxt(str) {
		const memory_buffer = new Uint8Array(this.moduleref.instance.exports.memory.buffer);
		let text_buffer = "";	
		for(; memory_buffer[str] != 0; str++) {
			text_buffer += String.fromCharCode(memory_buffer[str]);
		}
		return text_buffer;
	}
}