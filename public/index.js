// Make the audio
let music = new PlayableAudio("./music.mp3", [0.0, 0.0, 0.0], true);

window.onload = async () => {
	// canvas drawing setup
	// canvas creation
	const canv = document.createElement("canvas");
	canv.style = "position: absolute; width: 100%; height: 100%; left: 0; top: 0; right: 0; bottom: 0; margin: 0;";
	document.body.appendChild(canv); 
	// creating the gl context
	const gl = canv.getContext("webgl2");
	
	// when the window is resized, we change the canvas' size
	window.onresize = () => {
		canv.width = canv.clientWidth * window.devicePixelRatio;
		canv.height = canv.clientHeight * window.devicePixelRatio;
		gl.viewport(0, 0, canv.width, canv.height);
	};
	window.onresize();

	// loading the module
	const modutils = new ModuleUtils();
	const module = await WebAssembly.instantiateStreaming(
		fetch("./main.wasm"), modutils.getImports()
	);
	// pass the reference of the module to the utils importer
	modutils.moduleref = module;

	// pass a reference to the canvas and the context
	modutils.canv = canv;
	modutils.gl = gl;

	// start executing the main function
	module.instance.exports.begin();
};

// Music (music.mp3) from: https://freesound.org/people/Timbre/sounds/617036/