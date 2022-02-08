// Simply a list of currently pressed keys
let pressedKeys = {};

window.onkeyup = (e) => { pressedKeys[e.which] = false; };
window.onkeydown = (e) => { pressedKeys[e.which] = true; };