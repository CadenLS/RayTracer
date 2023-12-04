#pragma once
#include "Color.h"
#include "Camera.h"
#include "Object.h"
#include <iostream>
#include <vector>
namespace ray
{
	class Scene
	{
	public:
		Scene(int depth = 5) : m_depth{ depth } {}
		Scene(int depth, const color3_t& topColor, const color3_t& bottomColor) :
			m_depth{ depth },
			m_topColor{ topColor },
			m_bottomColor{ bottomColor }
		{}

		void Render(class Canvas& canvas, int numSamples);
		color3_t Trace(const ray_t& ray, float minDistance, float maxDistance, raycastHit_t& raycastHit, int depth);
		void AddObject(std::unique_ptr<Object> object) { m_objects.push_back(std::move(object)); }

		void SetCamera(std::shared_ptr<Camera> camera) { m_camera = camera; }

	private:
		std::shared_ptr<Camera> m_camera;
		//<vector of unique pointers to Object> m_objects;
		std::vector<std::unique_ptr<Object>> m_objects;
		int m_depth{ 5 };

		color3_t m_topColor{ 1 };
		color3_t m_bottomColor{ 0 };
	};
}
