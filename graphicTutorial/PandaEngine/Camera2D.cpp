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
		// make it so that 0 is center
		screenCords -= glm::vec2(_screenWidth / 2, _screenHeight / 2);
		// Scale the coordinates
		screenCords /= _scale;

		// Translate with the camera position;
		screenCords += _position;

		return screenCords;
	}
}