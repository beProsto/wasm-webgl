#pragma once

enum class ControllerType {
	Mobile = 0,
	PC = 1,
	Invalid = 2
};

class ControllerBase {
public:
	ControllerBase() {

	}
	virtual ~ControllerBase() {

	}

	virtual ControllerType getControllerType() const {
		return ControllerType::Invalid;
	}

public:
	Vec2 movement;
	Vec2 look;
};

#include "mobile.hpp"
#include "pc.hpp"

class Controller {
public:
	Controller(ControllerType _type) {
		m_Controller = nullptr;
		create(_type);
	}
	Controller() {
		m_Controller = nullptr;
	}
	~Controller() {
		if(m_Controller != nullptr) delete m_Controller;
	}

	void create(ControllerType _type) {
		if(m_Controller != nullptr) delete m_Controller;
		
		if(_type == ControllerType::Mobile) {
			m_Controller = new MobileController();
		}
		else {
			m_Controller = new PCController();
		}
	}
	
	Vec2 getMovement() const {
		if(m_Controller == nullptr) return Vec2{0.0f,0.0f};
		return m_Controller->movement;
	}
	Vec2 getLook() const {
		if(m_Controller == nullptr) return Vec2{0.0f,0.0f};
		return m_Controller->look;
	}
	
	ControllerType getControllerType() const {
		if(m_Controller == nullptr) return ControllerType::Invalid;
		return m_Controller->getControllerType();
	}

protected:
	ControllerBase* m_Controller;
};