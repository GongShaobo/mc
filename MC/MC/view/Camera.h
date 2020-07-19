#ifndef CAMERA_H
#define CAMERA_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <iostream>
enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default camera values
const float YAW = 0.0f;//ƫ����
const float PITCH = 0.0f;//������
const float SPEED = 2.5f;//����ٶ�
const float SENSITIVITY = 0.38f;//���λ�����ж�
const float ZOOM = 45.0f;//����
class Camera {
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	void setPos(glm::vec3 position);
	void getWorldPos(int worldPos[]);//get camera's world position
	glm::mat4 GetViewMatrix();
	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch);
	void ProcessMouseScroll(float yoffset);


private:
	// calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};
#endif // !CAMERA_H
