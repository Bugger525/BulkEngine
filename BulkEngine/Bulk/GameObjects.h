#pragma once

#include <vector>

namespace BK
{
	class IGameObject
	{

	};
	class Scene
	{
	private:
		std::vector<IGameObject> objects_;
	};
}