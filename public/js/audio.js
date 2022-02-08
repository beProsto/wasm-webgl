// Create an AudioContext
let audioContext = new AudioContext();

// Create a (first-order Ambisonic) Resonance Audio scene and pass it
// the AudioContext.
let resonanceAudioScene = new ResonanceAudio(audioContext);

// Connect the scene’s binaural output to stereo out.
resonanceAudioScene.output.connect(audioContext.destination);

// Add the room definition to the scene. We are passing in two objects, both of which i will leave empty for now, so they set to default values.
// The first object defines the room's width, height and length 
// while the second one defines the materials it's walls are made up of.
// For more information you can visit the Resonance Audio's website. :D
resonanceAudioScene.setRoomProperties({}, {});

// Check if any audio can even be played
let isAudioPlayable = false;

// Adds a tempporary measure to ensure that any audio can be played
// it can only be played if the user first had any interaction with the website
function enableAudio() {
	// try to resume the audio context
	audioContext.resume()
	.then(() => { // when resumed
		isAudioPlayable = true;
		
		window.removeEventListener("keydown", enableAudio);
		window.removeEventListener("mousedown", enableAudio);
		window.removeEventListener("touchstart", enableAudio);
		
		console.log("Audio Context has indeed been resumed.");
	});
	console.log("Tried to resume Audio Context.");
}
window.addEventListener("keydown", enableAudio);
window.addEventListener("mousedown", enableAudio);
window.addEventListener("touchstart", enableAudio);

// Let's keep track of the number of audios in the scene for absolutely no reason other than that we can assign them ID's based on in what place they were created
let audios = 0;

// This class will contain everything we need for 3D Audio
class PlayableAudio {
	constructor(_url, _position, _loop = false) {
		// We should know which one it is, for debugging purposes
		this.id = audios;
		audios++;
		// It should know where it's audio comes from - we'll have to get the audio from somewhere :D
		this.url = _url;
		// It should know the position from which we'll hear it
		this.posX = _position[0];
		this.posY = _position[1];
		this.posZ = _position[2];
		// We want to know if it's a loop + we want to be able to set it the way we want it
		this.isLoop = _loop;

		// Wether it's playing or not 
		// - playable tells us if the sound isn't currently being stopped, 
		// whilst playing determines wether or not it is, actually, playing
		this.isPlayable = false;
		this.isPlaying = false;
		
		// These are useless callbacks but whatever
		this.onFinished = () => {};
		this.onStarted = () => {};
		
		// Create a Resonance source and set its position in space.
		this.source = resonanceAudioScene.createSource();
		this.source.setPosition(this.posX, this.posY, this.posZ);

		// These will be filled when the sound is loaded
		this.buffer = null;
		this.bufferSource = null;

		// Now we use the previously saved URL to download, "fetch", the audio from the server
		fetch(this.url).then( // first we retrieve the data hiding behind the url, most likely it'll just be the audio file
			(response) => response.arrayBuffer() // after retrieving the file, we treat it as a buffer or data, at this point it doesn't really matter what data it is
		).then(
			(buffer) => audioContext.decodeAudioData(buffer) // then we get the data we retrieved and finally try and find sound in it
		).then( // if we found sound, as in - if the file contains audio data
			(decodedBuffer) => {
				this.buffer = decodedBuffer;
				this.genBufferSource(); // we create the actual buffer that will be played
			}
		);
	}

	// Generates the buffer that'll actually be played
	genBufferSource() {
		// We set the state to be playable, not playing, so that we can start playing the audio whenever we use the "play" function
		this.isPlayable = true;
		this.isPlaying = false;

		// Create a buffer source. This will need to be recreated every time
		// we wish to start the audio, see
		// https://developer.mozilla.org/en-US/docs/Web/API/AudioBufferSourceNode
		this.bufferSource = audioContext.createBufferSource();
		this.bufferSource.loop = this.isLoop; // tell it wether we want to loop it or not
		this.bufferSource.connect(this.source.input); // we connect the audio, this will have to be reversed as soon as the audio ends

		this.bufferSource.buffer = this.buffer;

		// Upon generating the buffer source, we define it's destructor - what happens, when it stops
		// Audio can be ended both by a user (the stop function), and by itself - just reaching the end
		this.bufferSource.onended = () => {
			this.bufferSource.disconnect(); // we disconnect the audio, to get rid of some nasty handlers
			delete this.bufferSource;

			this.genBufferSource(); // we regenerate the buffer source - as we know, it has to be done every time the buffer ends, thus we do it here

			// We call the user-defined callback in case of a sound ending - these seem to be pretty handy, actually! :D
			this.onFinished();
		};
	}

	// Play the audio (with the option of starting at a given time)
	play(_from = 0) {
		// We should only be able to start playing the audio if it isn't playing already, and if it is playable (the cleanup process has finished)
		if(this.isPlayable && !this.isPlaying && isAudioPlayable) {
			this.bufferSource.start(0, _from);

			// We let the world know that the sound is, indeed, playing
			this.isPlaying = true;

			// We once again, call the user-defined callback, except this time it's for when the audio starts, which is indeed what happened :D
			this.onStarted();
		}
	}

	// Stop the audio 
	stop() {
		// We only stop the audio if it is, in fact, playing AND isn't currently in the process of being stopped
		if(this.isPlayable && this.isPlaying) {
			this.isPlayable = false; // We mark that the audio is in the process of being stopped, thus can't be stopped nor played now

			this.bufferSource.stop(0);
		}
	}

	// These simply let us know and set if the audio is looped
	set loop(_loop) {
		this.isLoop = _loop;
		this.bufferSource.loop = this.isLoop;
	}
	get loop() {
		return this.isLoop;
	}
	
	// This one lets us check the duration of the audio (in seconds)
	get duration() {
		return this.buffer.duration;
	}

	// Set and get audio's position
	set position(_pos) {
		this.posX = _pos[0];
		this.posY = _pos[1];
		this.posZ = _pos[2];

		this.source.setPosition(this.posX, this.posY, this.posZ);
	}
	get position() {
		return [this.posX, this.posY, this.posZ];
	}

	// Check if the audio is currently playing
	get playing() {
		return this.isPlayable && this.isPlaying;
	}
}
