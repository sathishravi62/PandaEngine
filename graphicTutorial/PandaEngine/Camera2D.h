#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace PandaEngine {

	class Camera2D
	{
	public:
		Camera2D();
		~Camera2D();

		// setting up the orthographic matrix and screen dimension
		void init(int screenWidth, int screenHeight);

		//	update the camera matrix if needed
		void Update();


		glm::vec2 convertScreenToWorld(glm::vec2 screenCords);

		// settes
		void setPosition(const glm::vec2& newPosition) { _position = newPosition; _needsMatrixUpdate = true; }
		void setScale(float newScale) { _scale = newScale; _needsMatrixUpdate = true; }

		// getters
		glm::vec2 getPosition() { return _position; }
		float getScale() { return _scale; }
		glm::mat4 getCameraMatrix() { return _CameraMatrix; }

	private:

		int _screenWidth, _screenHeight;
		bool _needsMatrixUpdate;
		float _scale;
		glm::vec2 _position;
		glm::mat4 _CameraMatrix;
		glm::mat4 _orthoMatrix;
	};
}

#endif // !CAMERA2D_H


