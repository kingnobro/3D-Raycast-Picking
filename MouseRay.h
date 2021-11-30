#pragma once

#include <glm/glm.hpp>
#include "Camera.h"

class MouseRay
{
public:
	MouseRay(Camera* cam)
	{
		camera = cam;
	}

	/*
	 * generate a ray from mouse position
	 * and convert 2D screen space to 3D world space
	 */
	glm::vec3 calculateMouseRay(double mouse_x, double mouse_y, int screen_width, int screen_height)
	{
		glm::vec3 ray_ndc = getNormalisedDeviceCoordinates(mouse_x, mouse_y, screen_width, screen_height);
		// we want our ray's z to point forwards - this is usually the negative z direction in OpenGL style
		glm::vec4 ray_clip = glm::vec4(ray_ndc.x, ray_ndc.y, -1.0, 1.0);
		glm::vec4 ray_eye = toEyeCoords(ray_clip);
		glm::vec3 ray_world = toWorldCoords(ray_eye);
		return ray_world;
	}

private:
	/*
	 * 3D Normalised Device Coordinates
	 * scale the range of x,y and reverse the direction of y
	 * we don't actually need to specify a z yet, but I put one in (for the craic)
	 */
	glm::vec3 getNormalisedDeviceCoordinates(float mouse_x, float mouse_y, int screen_width, int screen_height)
	{
		float ndc_x = (2.0f * mouse_x) / (double)screen_width - 1.0f;
		float ndc_y = 1.0f - (2.0f * mouse_y) / (double)screen_height;
		float ndc_z = 1.0;
		return glm::vec3(ndc_x, ndc_y, ndc_z);
	}

	/*
	 * normally, to get into clip space from eye space we multiply the vector by a projection matrix
     * we can go backwards by multiplying by the inverse of this matrix 
	 */
	glm::vec4 toEyeCoords(glm::vec4 ray_clip)
	{
		glm::vec4 ray_eye = glm::inverse(camera->GetProjectionMatrix()) * ray_clip;
		// Now, we only needed to un-project the x,y part, so let's manually set the z,w part to mean "forwards, and not a point"
		ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.0, 0.0);
		return ray_eye;

	}

	glm::vec3 toWorldCoords(glm::vec4 ray_eye)
	{
		glm::vec3 ray_world = glm::inverse(camera->GetViewMatrix()) * ray_eye;
		ray_world = glm::normalize(ray_world);
		return ray_world;
	}

	Camera* camera;
};