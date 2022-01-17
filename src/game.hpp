#pragma once

#include "utils/include/utils.hpp"

class Game {
public:
	Game() {
		m_ColorInterval = 0.0f;
	}
	~Game() {
		
	}

	void start() {

	}
	void update() {
		m_ColorInterval += 0.01f;
		m_ColorInterval /= 1.0f;
		glClearColor(m_ColorInterval, m_ColorInterval, m_ColorInterval, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

private:
	float m_ColorInterval;
};