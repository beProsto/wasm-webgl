#pragma once

class MobileController: public ControllerBase {
public:
	MobileController() {

	}
	virtual ~MobileController() {

	}
	
	virtual ControllerType getControllerType() const {
		return ControllerType::Mobile;
	}

	virtual void update() {
		console_log("Mobile Controller Update");
		
	}
};