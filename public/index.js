window.onload = async () => {
	const modutils = new ModuleUtils();
	const module = await WebAssembly.instantiateStreaming(
		fetch("./main.wasm"), modutils.getImports()
	);
	// pass the reference of the module to the utils importer
	modutils.moduleref = module;

	// start executing the main function
	module.instance.exports.Main();

	// canvas drawing setup
	const gl = document.getElementById("vancas").getContext("webgl");
	// gl.clearColor(1.0, 1.0, 0.0, 1.0);
	// gl.clear(gl.COLOR_BUFFER_BIT);

	// pass a reference to the context
	modutils.gl = gl;
};