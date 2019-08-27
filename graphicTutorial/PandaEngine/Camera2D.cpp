#include "Camera2D.h"

namespace PandaEngine {

	Camera2D::Camera2D() : _position(0.0f, 0.0f),
		_CameraMatrix(1.0f),
		_scale(1.0f),
		_needsMatrixUpdate(true),
		_screenWidth(500),
		_screenHeight(500),
		_orthoMatrix(1.0f)
	{
	}


	Camera2D::~Camera2D()
	{
	}

	void Camera2D::init(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
		_orthoMatrix = glm::ortho(0.0f, (float)_screenWidth, 0.0f, (float)_screenHeight);

	}

	void Camera2D::Update()
	{
		if (_needsMatrixUpdate)
		{
			// Camera Translation
			glm::vec3 translate(-_position.x + _screenWidth / 2, -_position.y + _screenHeight / 2, 0.0f);
			_CameraMatrix = glm::translate(_orthoMatrix, translate);

			// Camera Scale
			glm::vec3 scale(_scale, _scale, 0.0f);
			_CameraMatrix = glm::scale(glm::mat4(1.0f), scale) * _CameraMatrix;
			_needsMatrixUpdate = false;
		}
	}
	glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCords)
	{
		// Invert Y-Direction 

		screenCords.y = _screenHeight - screenCords.y;

		// make it so that 0 is center
		screenCords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		// Scale the coordinates
		screenCords /= _scale;

		// Translate with the camera position;
		screenCords += _position;

		return screenCords;
	}
	bool Camera2D::isBoxInView(const glm::vec2 & position, const glm::vec2 & dimensions)
	{
	
		glm::vec2 scaledScreenDimension = glm::vec2(_screenWidth, _screenHeight) / (_scale * 2.0f);

		// The minimum distance before a collision occurs
		const float MIN_DISTANCE_X = dimensions.x / 2.0f + scaledScreenDimension.x / 2.0f;
		const float MIN_DISTANCE_Y = dimensions.y / 2.0f + scaledScreenDimension.y / 2.0f;

		// center position of the Object
		glm::vec2 centerPos = position + dimensions / 2.0f;

		// center position of the camera
		glm::vec2 centerCameraPos = _position;
		// vector from the input to the camera
		glm::vec2 distVec = centerPos - centerCameraPos;

		// get the depth of the collision
		float xDepth = MIN_DISTANCE_X - abs(distVec.x);
		float yDepth = MIN_DISTANCE_Y - abs(distVec.y);

		// if either the depths are > 0, then we are collided
		if (xDepth > 0 && yDepth > 0)
		{
			// There was a collision so return true
			return true;
		}
		return false;
	}
}