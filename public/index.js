let img;
let c2d;

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
	c2d = document.getElementById("vancas").getContext("2d");
	const data = new Uint8ClampedArray(module.instance.exports.memory.buffer, module.instance.exports.getDisplayPtr(), 640 * 360 * 4);
	img = new ImageData(data, 640, 360);
	c2d.putImageData(img, 0, 0);

	// pass a reference to the context
	modutils.c2d = c2d;
	modutils.img = img;
};