#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "Cloth.h"
#include "Camera.h"

class ClothPicker
{
public:
	ClothPicker(Camera* cam)
	{
		camera = cam;
	}

	/*
	 * check whether ray intersect with cloths
	 * return the cloth with the greatest z
	 */
	Cloth* pickCloth(const vector<Cloth*> &cloths, const glm::vec3 &ray)
	{
		// points on the cloth
		Cloth* selectedCloth = nullptr;
		for (Cloth* cloth : cloths)
		{
			glm::vec3 pointLeftUpper = cloth->clothPos;
			glm::vec3 pointRightUpper = pointLeftUpper + glm::vec3(cloth->width, 0, 0);
			glm::vec3 pointRightBottom = pointLeftUpper + glm::vec3(cloth->width, -cloth->height, 0);

			// normal vector of the cloth
			glm::vec3 normal = glm::cross(pointRightBottom - pointLeftUpper, pointRightUpper - pointLeftUpper);
			// hitPoint = camera.Position + ray * t
			double t = glm::dot(pointLeftUpper - camera->Position, normal) / glm::dot(ray, normal);
			// intersection point
			glm::vec3 hitPoint = camera->Position + glm::vec3(ray.x * t, ray.y * t, ray.z * t);
			if (hitPoint.x >= pointLeftUpper.x && hitPoint.x <= pointRightUpper.x && hitPoint.y <= pointLeftUpper.y && hitPoint.y >= pointRightBottom.y)
			{
				// TODO: find the cloth closet to the camera
				if (selectedCloth == nullptr)
				{
					selectedCloth = cloth;
					std::cout << "Cloth " << selectedCloth->GetClothID() << " Selected\n";
					break;
				}
			}
		}
		return selectedCloth;
	}
private:
	Camera* camera;
};