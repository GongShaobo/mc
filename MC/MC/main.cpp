#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include"Camera.h"
#include"Chunk.h"
#include"particleGenerator.h"
#include"stb_image.h"
#include"Block.h"
#include<time.h>
#include<vector>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Map.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_click_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void screen2world(double xpos, double ypos, glm::vec3* worldPos);

// settings
extern const unsigned int SCR_WIDTH = 800;
extern const unsigned int SCR_HEIGHT = 600;
float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
float lastFrame = 0.0f; // ��һ֡��ʱ��
float lastX = 400, lastY = 300;
bool firstMouse = true;
Camera myCamera(glm::vec3(6.0f, 15.0f, 20.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f,0.0f);
Map* myMap;
std::vector<operateBlock*> extraBlocks;
std::vector<operateBlock*> delBlocks;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_move_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetMouseButtonCallback(window, mouse_click_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glEnable(GL_DEPTH_TEST);//������Ȳ���
	glEnable(GL_CULL_FACE);//���޳�

	myMap = new Map(&myCamera);
	myMap->updateMap();
	Block::loadTextures();
	/*Shader partShader("particles_vs.txt", "particles_fs.txt");
	Texture partTex(GL_TEXTURE_2D, "blocks/dirt.png");
	blockParticles = new ParticleGen(partShader, partTex, 10);*/

	while (!glfwWindowShouldClose(window))
	{
		float curTime = glfwGetTime();
		deltaTime = curTime - lastFrame;
		lastFrame = curTime;
		processInput(window);
		glClearColor(91.0f / 255.0f, 206.0f/255.0f, 1.0f, 1.0f);//background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myMap->renderMap();//draw map
		
		// �������岢��ѯIO�¼���
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	delete myMap;

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		myCamera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		myCamera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	myMap->updateMap();
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_move_callback(GLFWwindow* window, double xpos, double ypos)
{//screen origin(0,0): ���Ͻ�
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	myCamera.ProcessMouseMovement(xoffset, yoffset, true);
}

void mouse_click_callback(GLFWwindow* window, int button, int action, int mods) {
	glm::vec3 world = glm::vec3(0.0f, 0.0f, 0.0f);
	double cursor_x = 0, cursor_y = 0;
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {//press 
		cout << "left press " << endl;
		glfwGetCursorPos(window, &cursor_x, &cursor_y);
		screen2world(cursor_x, cursor_y, &world);
		cout << cursor_x << "," << cursor_y << "  #   " << world.x << "," << world.y << "," << world.z << endl;
		//place a block
		operateBlock* p = new operateBlock;
		p->mapCoord[0] = 0;
		p->mapCoord[1] = 0;
		p->chunkCoord[0] = 0;
		p->chunkCoord[1] = 0;
		p->type = Block::Stone;
		extraBlocks.push_back(p);
	}
	else if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_RIGHT) {
		cout << "right press " << endl;
		double cursor_x = 0, cursor_y = 0;
		glfwGetCursorPos(window, &cursor_x, &cursor_y);
		screen2world(cursor_x, cursor_y, &world);//place block
		cout << cursor_x << "," << cursor_y << "  #   " << world.x << "," << world.y << "," << world.z << endl;
		//destroy a block:
		operateBlock* p = new operateBlock;
		p->mapCoord[0] = 0;
		p->mapCoord[1] = 0;
		p->chunkCoord[0] = 1;
		p->chunkCoord[1] = 0;
		delBlocks.push_back(p);
	}
	return;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	myCamera.ProcessMouseScroll(yoffset);
}
void screen2world(double xpos, double ypos, glm::vec3* worldPos)
{//creeen coordiate to world coordiate
	GLint viewport[4];
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	GLfloat winX, winY, winZ;							//��괦����+��괦�������
	GLdouble object_x, object_y, object_z;				//�������������
	glm::vec3 pp = glm::vec3(0.0f, 0.0f, 0.f);
	int mouse_x = xpos;
	int mouse_y = ypos;

	view = myCamera.GetViewMatrix();
	projection = glm::perspective(glm::radians(myCamera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (float)mouse_x;
	winY = (float)viewport[3] - (float)mouse_y;
	glReadBuffer(GL_BACK);
	glReadPixels((int)winX, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
	//glm::unProject((GLdouble)winX, (GLdouble)winY, (GLdouble)winZ, (GLdouble*)glm::value_ptr(view*model), 
	//	(GLdouble*)glm::value_ptr(projection), viewport, &object_x, &object_y, &object_z);
	//pp.x = object_x;
	//pp.y = object_y;
	//pp.z = object_z;

	//���ӵ��UVNϵͳ
	glm::vec3 U, V, N;
	glm::vec3 up = { 0.0,1.0,0.0 };
	glm::vec3 eye, direction;            //�ӵ�������۲������

	N = eye - direction;                 //ʸ������
	U = glm::cross(N, up);                //ʸ�����
	V = glm::cross(N, U);
	glm::normalize(N);                      //ʸ����һ��
	glm::normalize(U);
	glm::normalize(V);
	worldPos->x = U.x * pp.x + V.x * pp.y + N.x * pp.z + eye.x;
	worldPos->y = U.y * pp.x + V.y * pp.y + N.y * pp.z + eye.y;
	worldPos->z = U.z * pp.x + V.z * pp.y + N.z * pp.z + eye.z;
}