// Everything besides _touchintlpos is the mouse's interface
let mouse = {
	position: [0.0, 0.0],
	velocity: [0.0, 0.0],
	pressedButtons: [false, false, false, false, false],
	wheel: 0.0,
	_touchintlpos: [0.0, 0.0]
};

function initMouseHandling() {
	window.onmousemove = (e) => {
		mouse.position[0] = e.clientX * window.devicePixelRatio; 
		mouse.position[1] = e.clientY * window.devicePixelRatio; 
		mouse.velocity[0] = e.movementX;
		mouse.velocity[1] = e.movementY;
	};
	window.onmousedown = (e) => {
		mouse.pressedButtons[e.button] = true;
	};
	window.onmouseup = (e) => {
		mouse.pressedButtons[e.button] = false;
	};
	window.onwheel = (e) => {
		mouse.wheel = e.deltaY;
	};
	
	window.ontouchmove = (e) => {
		mouse.position[0] = e.touches[0].clientX * window.devicePixelRatio; 
		mouse.position[1] = e.touches[0].clientY * window.devicePixelRatio; 
		mouse.velocity[0] = mouse.position[0] - mouse._touchintlpos[0];
		mouse.velocity[1] = mouse.position[1] - mouse._touchintlpos[1];
		mouse._touchintlpos[0] = mouse.position[0];
		mouse._touchintlpos[1] = mouse.position[1];
	};
	window.ontouchstart = (e) => {
		mouse.position[0] = e.touches[0].clientX * window.devicePixelRatio; 
		mouse.position[1] = e.touches[0].clientY * window.devicePixelRatio; 
		mouse.velocity[0] = 0.0;
		mouse.velocity[1] = 0.0;
		mouse._touchintlpos[0] = mouse.position[0];
		mouse._touchintlpos[1] = mouse.position[1];
		
		mouse.pressedButtons[0] = true; 
	};
	window.ontouchend = (e) => {
		mouse.pressedButtons[0] = false; 
		mouse.velocity[0] = 0.0;
		mouse.velocity[1] = 0.0;
	};
	window.ontouchcancel = (e) => {
		mouse.pressedButtons[0] = false; 
		mouse.velocity[0] = 0.0;
		mouse.velocity[1] = 0.0;
	};
	
	// prevents the context menu from appearing
	window.oncontextmenu = (e) => { return false; };
}