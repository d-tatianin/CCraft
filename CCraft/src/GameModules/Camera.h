#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../vendor/glm/glm.hpp"
#include "../vendor/glm/gtc/matrix_transform.hpp"
#include "../vendor/glm/gtc/type_ptr.hpp"
#include "CollisionDetection.h"

namespace CCraft 
{
	
	//default values 
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 5.0f;
	const float SENSITIVITY = 0.08f;
	const float ZOOM = 45.0f;

	class Camera
	{
	public:
		CollisionDetection collisionDetection;
		glm::vec3 Position;
		glm::vec3 Front;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;
		float Yaw;
		float Pitch;
		float MovementSpeed;
		float MouseSensitivity;
		float Zoom;

		Camera(glm::vec3 position = glm::vec3(0.0f, 67.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) 
			: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
		{
			Position = position;
			WorldUp = up;
			Yaw = yaw;
			Pitch = pitch;
			updateCameraVectors();
		}

		glm::mat4 GetViewMatrix()
		{
			return glm::lookAt(Position, Position + Front, Up);
		}

		void ProcessKeyboard(Camera_Movement direction, float deltaTime)
		{

			float velocity = MovementSpeed * deltaTime;
			glm::vec3 tempo = glm::vec3(1.0f);
			glm::vec3 normalizedTempo = glm::vec3(1.0f);

			if (direction == FORWARD)
			{
				tempo = Front;
				tempo.y = 0.0f;
				normalizedTempo = glm::normalize(tempo);
				collisionDetection.testForCollision(Position, normalizedTempo, direction, velocity);
				Position += normalizedTempo * velocity;
			}

			if (direction == BACKWARD)
			{
				tempo = Front;
				tempo.y = 0.0f;
				normalizedTempo = glm::normalize(tempo);
				collisionDetection.testForCollision(Position, normalizedTempo, direction, velocity);
				Position -= normalizedTempo * velocity;
			}

			if (direction == LEFT)
			{
				tempo = Right;
				tempo.y = 0.0f;
				normalizedTempo = glm::normalize(tempo);
				collisionDetection.testForCollision(Position, normalizedTempo, direction, velocity);
				Position -= normalizedTempo * velocity;
			}

			if (direction == RIGHT)
			{
				tempo = Right;
				tempo.y = 0.0f;
				normalizedTempo = glm::normalize(tempo);
				collisionDetection.testForCollision(Position, normalizedTempo, direction, velocity);
				Position += normalizedTempo * velocity;
			}

			if (direction == UP)
			{
				if(collisionDetection.testForVerticalCollision(Position, velocity, direction))
					Position.y += velocity;
			}

			if (direction == DOWN)
			{
				if(collisionDetection.testForVerticalCollision(Position, velocity, direction))
					Position.y -= velocity;
			}
		}

		void ProcessMouseMovement(float xoffset, float yoffset)
		{
			xoffset *= MouseSensitivity;
			yoffset *= MouseSensitivity;

			Yaw += xoffset;
			Pitch += yoffset;

			if (Pitch > 89.0f)
				Pitch = 89.0f;
			if (Pitch < -89.0f)
				Pitch = -89.0f;
			if (Yaw > 180.0f)
				Yaw = -180.f;
			if (Yaw < -180.0f)
				Yaw = 180.f;

			updateCameraVectors();
		}

	private:
		void updateCameraVectors()
		{
			glm::vec3 front;
			front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			front.y = sin(glm::radians(Pitch));
			front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
			Front = glm::normalize(front);
			Right = glm::normalize(glm::cross(Front, WorldUp));
			Up = glm::normalize(glm::cross(Right, Front));
		}
	};

}
