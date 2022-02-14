let canv; // canvas must be global sadly
let module; // module too
window.onload = async () => {
	// canvas drawing setup
	// canvas creation
	canv = document.createElement("canvas");
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

	console.log("DEVICE PIXEL RATIO: " + window.devicePixelRatio);

	// loading the module
	const modutils = new ModuleUtils();

	const imports = modutils.getImports();
	imports.env.after_loaded = gameLoaded;

	module = await WebAssembly.instantiateStreaming(
		fetch("./wasm/main.wasm"), imports
	);
	
	// pass the reference of the module to the utils importer
	modutils.moduleref = module;

	// pass a reference to the canvas and the context
	modutils.canv = canv;
	modutils.gl = gl;

	// start executing the main function
	module.instance.exports.begin();
};

function gameLoaded() {
	const header = document.querySelector("header");
	
	// Adds a tempporary measure to ensure that any audio can be played
	// it can only be played if the user first had any interaction with the website
	function enableAudio() {
		// try to resume the audio context
		audioContext.resume()
		.then(() => { // when resumed
			isAudioPlayable = true;
			
			console.log("Audio Context has indeed been resumed.");
		});

		canv.requestFullscreen()
		.then(() => {
			window.removeEventListener("keydown", enableAudio);
			window.removeEventListener("mousedown", enableAudio);
			window.removeEventListener("touchstart", enableAudio);

			if(screen.orientation.lock) screen.orientation.lock('landscape');

			header.parentNode.removeChild(header);

			module.instance.exports.begin_game();
		});
		
		console.log("Tried to resume Audio Context.");
	}
	window.addEventListener("keydown", enableAudio);
	window.addEventListener("mousedown", enableAudio);
	window.addEventListener("touchstart", enableAudio);

	header.innerHTML = "<p>Everyting loaded! :D</p><p>Please press anything to continue!</p>";
}