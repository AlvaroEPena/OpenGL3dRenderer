
#include "common.h"
#include "cube_mesh.h"

#include "Camera.h"
#include "game_map.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int SCR_WIDTH = 1000;
unsigned int SCR_HEIGHT = 1000;

float rot_speed = 30.f;

float deltaTime = 0.0f;	// Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;


int main()
{
	GLFWwindow* window;

	if (!glfwInit()) {
		cout << "GLFW could not init" << endl;
		return -1;
	}

	// creating window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Custom Window", NULL, NULL);

	// make the window the current OpenGL context to render to
	glfwMakeContextCurrent(window);

	// tell glad to find where all the open gl function defs are
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// clear screen color
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

	Shader shader = ResourceManager::LoadShader("../../src/shaders/vertex.vert", "../../src/shaders/fragment.frag", NULL, "base");
	Texture2D texture = ResourceManager::LoadTexture("../../src/images/grass.jpg", true, "grass");

	CubeMesh* cube = new CubeMesh();

	shader.Use();
	texture.Bind();

	//shader.SetInteger("material", 0);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shader.SetMatrix4("projection", projection);

	glm::mat4 view(1.f);

	glm::vec3 cube_pos[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f),
		glm::vec3(-2.3f,  5.0f, -30.0f)
	};
	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);

	// enable culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);


	Vertex vertices[] = {
		// Front face
		{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 2.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // top left
		{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // bottom left
		{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // bottom right
		{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // top right

		// Back face
		{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // top right
		{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // bottom right
		{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 1.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // bottom left
		{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 2.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // top left

		// Left face
		{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 2.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // top left
		{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.75f, 1.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom left
		{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom right
		{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.0f, 2.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // top right

		// Right face
		{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // top left
		{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // bottom left
		{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // bottom right
		{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // top right

		// Top face
		{{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top left
		{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {0.0f, 1.0f, 0.0f}}, // bottom left
		{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {0.0f, 1.0f, 0.0f}}, // bottom right
		{{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top right

		// Bottom face
		{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {0.0f, -1.0f, 0.0f}}, // bottom left
		{{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.25f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // top left
		{{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // top right
		{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {0.0f, -1.0f, 0.0f}}  // bottom right
	};

	Vertex vertices2x2[] = {
		// Front face
		{{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 2.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // top left
		{{-1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // bottom left
		{{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // bottom right
		{{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {0.0f, 0.0f, 1.0f}}, // top right

		// Back face
		{{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // top right
		{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // bottom right
		{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.75f, 1.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // bottom left
		{{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.75f, 2.0f / 3.0f}, {0.0f, 0.0f, -1.0f}}, // top left

		// Left face
		{{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.75f, 2.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // top left
		{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.75f, 1.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom left
		{{-1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // bottom right
		{{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 2.0f / 3.0f}, {-1.0f, 0.0f, 0.0f}}, // top right

		// Right face
		{{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // top left
		{{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // bottom left
		{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // bottom right
		{{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {1.0f, 0.0f, 0.0f}}, // top right

		// Top face
		{{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top left
		{{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 2.0f / 3.0f}, {0.0f, 1.0f, 0.0f}}, // bottom left
		{{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 2.0f / 3.0f}, {0.0f, 1.0f, 0.0f}}, // bottom right
		{{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f}, {0.0f, 1.0f, 0.0f}}, // top right

		// Bottom face
		{{-1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 1.0f / 3.0f}, {0.0f, -1.0f, 0.0f}}, // bottom left
		{{-1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.25f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // top left
		{{ 1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.0f}, {0.0f, -1.0f, 0.0f}}, // top right
		{{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.5f, 1.0f / 3.0f}, {0.0f, -1.0f, 0.0f}}  // bottom right
	};


	// Indices remain the same as your data
	unsigned int indices[] = {
		0, 1, 2, 2, 3, 0,         // Front face
		4, 5, 6, 6, 7, 4,         // Back face
		8, 9, 10, 10, 11, 8,      // Left face
		12, 13, 14, 14, 15, 12,   // Right face
		16, 17, 18, 18, 19, 16,   // Top face
		20, 21, 22, 22, 23, 20    // Bottom face
	};

	Vertex triangle_t[] = {
		// Position             // Color (e.g., white)     // Texture Coords (u, v)    // Normal
		{glm::vec3(0.0f,  0.5f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // Top vertex
		{glm::vec3(-0.5f, -0.5f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}, // Bottom-left vertex
		{glm::vec3(0.5f, -0.5f,  0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)}  // Bottom-right vertex
	};

	Vertex s[] = {
		// Front face
		{{-0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.f}, {0.0f, 0.0f, 1.0f}}, // top left
		{{-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.f}, {0.0f, 0.0f, 1.0f}}, // bottom left
		{{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.f, 0.f}, {0.0f, 0.0f, 1.0f}}, // bottom right
		{{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 1.0f}, {1.f, 1.f}, {0.0f, 0.0f, 1.0f}}, // top right

	};

	unsigned int is[] = {
		0,1,2,
		0,2,3
	};


	unsigned int indices_t[] = {
	0, 1, 2 
	};

	//Mesh test(vertices, 24, indices, 36, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.25f));
	Mesh test(vertices2x2, 24, indices, 36, glm::vec3(0.f), glm::vec3(0.f), glm::vec3(0.5f));
	//Mesh test(triangle_t, 4, indices_t, 6);
	//Mesh test(s, 4, is, 6);


	Map gameMap(&test, &shader);

	while (!glfwWindowShouldClose(window)) {
		GLenum err;
		while ((err = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL error: " << err << std::endl;
		}
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.SetMatrix4("projection", glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f));

		shader.SetMatrix4("view", camera.GetViewMatrix());

		float time = (float)glfwGetTime() * rot_speed;

		//cout << time << endl;

		//for (int i = 0; i < 11; i++) {
		//	test.setPosition(cube_pos[i]);
		//	test.setRotation(glm::vec3(0.f, time, 45.f));
		//	test.render(&shader);
		//}
		
		gameMap.draw();

		glfwPollEvents();
		glfwSwapBuffers(window);

	}

	// clean up
	glfwTerminate();


	return 0;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCR_WIDTH = width;
	SCR_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	// ESCAPE key handling (still continuous on hold)
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(static_cast<float>(yoffset));
}