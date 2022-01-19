// Taken from https://github.com/beProsto/OWL/blob/master/_Examples/ModernOpenGLExample/main.cpp
// Used as a reference for needed OpenGL / WebGL functions

float t = 0.0f;

float vertices[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f
};

const char* vsc = 
"#version 330\n\
\n\
layout (location = 0) in vec3 a_Position;\n\
layout (location = 1) in vec3 a_Color;\n\
\n\
out vec4 v_Color;\n\
\n\
uniform vec2 u_Offset;\n\
\n\
void main() {\n\
\tgl_Position = vec4(a_Position + vec3(u_Offset, 0.0f), 1.0f);\n\
\tv_Color = vec4(a_Color, 1.0f);\n\
}\n";

const char* fsc = 
"#version 330\n\
\n\
out vec4 o_Color;\n\
\n\
in vec4 v_Color;\n\
\n\
void main() {\n\
\to_Color = v_Color;\n\
}\n";

unsigned int vShaderID, fShaderID, shaderID, vbID, vaID;

int  success;
char infoLog[512];

vShaderID = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vShaderID, 1, &vsc, NULL);
glCompileShader(vShaderID);

// glGetShaderiv(vShaderID, GL_COMPILE_STATUS, &success);
// if(!success) {
// 	glGetShaderInfoLog(vShaderID, 512, NULL, infoLog);
// 	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
// }

fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fShaderID, 1, &fsc, NULL);
glCompileShader(fShaderID);

// glGetShaderiv(fShaderID, GL_COMPILE_STATUS, &success);
// if(!success) {
// 	glGetShaderInfoLog(fShaderID, 512, NULL, infoLog);
// 	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
// }

shaderID = glCreateProgram();
glAttachShader(shaderID, vShaderID);
glAttachShader(shaderID, fShaderID);
glLinkProgram(shaderID);
glValidateProgram(shaderID);

glDeleteShader(vShaderID);
glDeleteShader(fShaderID);

glUseProgram(shaderID);

glGenVertexArrays(1, &vaID);
glBindVertexArray(vaID);

glGenBuffers(1, &vbID);
glBindBuffer(GL_ARRAY_BUFFER, vbID);

glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), vertices, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);  
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);  

while(window.IsRunning()) {
	window.PollEvents();
	fps.Start();
	time.Start();
	
	if(time.GetDeltaTime() > 0.0f) t += time.GetDeltaTime();

	if(window.Keyboard.GetKeyData().KeyEnum == window.Keyboard.M) {
		window.Mouse.SetVisibility(!window.Mouse.IsVisible());
	}
	if(window.Keyboard.GetKeyData().KeyEnum == window.Keyboard.F11) {
		window.SetFullScreen(!window.IsFullScreen());
	}
	if(window.Keyboard.GetKeyData().KeyEnum == window.Keyboard.Escape) {
		window.Close();
	}

	float sint = std::sin(t) * 0.5f + 0.5f;

	OWL::Vec2f mp = (OWL::Vec2f)window.Mouse.GetPosition() / (OWL::Vec2f)window.GetSize() * OWL::Vec2f(2.0f) - OWL::Vec2f(1.0f);
	mp.y = -mp.y;

	glViewport(0, 0, window.GetSize().x, window.GetSize().y);

	glClearColor(sint, sint, sint, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUniform2f(glGetUniformLocation(shaderID, "u_Offset"), mp.x, mp.y);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	context.SwapBuffers();

	Debug::Out::Print(std::to_string(time.GetDeltaTime()) + "\n");

	fps.End();
	time.End();
}

glDeleteVertexArrays(1, &vaID);
glDeleteBuffers(1, &vbID);
glDeleteProgram(shaderID);