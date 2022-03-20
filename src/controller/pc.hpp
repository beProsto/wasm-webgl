#pragma once

class PCController: public ControllerBase {
public:
	PCController() {

	}
	virtual ~PCController() {

	}

	virtual ControllerType getControllerType() const {
		return ControllerType::PC;
	}
	
	virtual void update() {
		console_log("PC Controller Update");

	}

};