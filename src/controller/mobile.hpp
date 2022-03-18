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

};