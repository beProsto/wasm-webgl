let pressedKeys = {};
window.onkeyup = (e) => { pressedKeys[e.code] = false; };
window.onkeydown = (e) => { pressedKeys[e.code] = true; };