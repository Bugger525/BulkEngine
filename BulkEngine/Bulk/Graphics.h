#pragma once

#include <string>

namespace BK
{
	class IRenderable
	{

	};
	class Font
	{

	};
	class Shader
	{
	public:
		uint32_t id_;
	private:
		Shader(const std::string& vertexPath, const std::string& fragPath);
	};
	class Camera
	{

	};
	class Text : public IRenderable
	{

	};
	class Texture : public IRenderable
	{

	};
	class Renderer
	{

	};

}