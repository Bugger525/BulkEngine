#include "../GameWindow.h"
#include "../Debug.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void APIENTRY glDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return; // ignore these non-significant error codes

	std::cout << "---------------\n";
	std::cout << "Debug message (" << id << "): " << message << "\n";

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << "\n";

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	}std::cout << "\n";

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: High"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: Medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: Low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: Notification"; break;
	} std::cout << std::endl;
}

namespace BK
{
	GameWindow::GameWindow(const std::string& title, uint32_t width, uint32_t height)
	{
		title_ = title;
		width_ = width;
		height_ = height;
	}
	void GameWindow::Run()
	{
		SetupEngine();

		if (!InitializeEngine())
		{
			Debug::Log("Failed to initialize Bulk.", DebugSource::WindowSystem, DebugType::Error, DebugSeverity::High);
			return;
		}
		if (!Initialize())
		{
			Debug::Log("Failed to initialize.", DebugSource::Application, DebugType::Error, DebugSeverity::Medium);
			return;
		}
		while (!glfwWindowShouldClose(window_))
		{
			glfwPollEvents();
			Update();
			Render();
		}
		Cleanup();
		CleanupEngine();
	}
	GLFWwindow* GameWindow::GetWindow() const
	{
		return window_;
	}
	uint32_t GameWindow::GetWidth() const
	{
		return width_;
	}
	uint32_t GameWindow::GetHeight() const
	{
		return height_;
	}
	uint32_t GameWindow::GetGLVersionMajor() const
	{
		return major_;
	}
	uint32_t GameWindow::GetGLVersionMinor() const
	{
		return minor_;
	}
	void GameWindow::SetGLVersion(uint32_t major, uint32_t minor)
	{
		major_ = major;
		minor_ = minor;
	}
	bool GameWindow::GetDebugMode() const
	{
		return debugMode_;
	}
	void GameWindow::SetDebugMode(bool flag)
	{
		debugMode_ = flag;
	}
	void GameWindow::Close()
	{
		glfwSetWindowShouldClose(window_, true);
	}
	bool GameWindow::InitializeEngine()
	{
		if (!glfwInit())
		{
			// std::cout << "Failed to initialize GLFW.\n";
			return false;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major_);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor_);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, debugMode_);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
		if (window_ == nullptr)
		{
			// std::cout << "Failed to create GLFW window.\n";
			return false;
		}
		glfwMakeContextCurrent(window_);
		gladLoadGL();

		if (debugMode_)
		{
			int flags;
			glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
			if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
			{
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageCallback(glDebugOutput, nullptr);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
			}
		}
		glViewport(0, 0, width_, height_);

		return true;
	}
	void GameWindow::CleanupEngine()
	{
		glfwDestroyWindow(window_);
		glfwTerminate();
	}
}