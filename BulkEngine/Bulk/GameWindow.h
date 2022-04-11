#pragma once

#include <string>

struct GLFWwindow;

namespace BK
{
	class GameWindow
	{
	public:
		GameWindow(const std::string& title, uint32_t width, uint32_t height);

		void Run();

		GLFWwindow* GetWindow() const;
	protected:
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;

		uint32_t GetGLVersionMajor() const;
		uint32_t GetGLVersionMinor() const;
		void SetGLVersion(uint32_t major, uint32_t minor);

		bool GetDebugMode() const;
		void SetDebugMode(bool flag);

		void Close();

		virtual void SetupEngine() = 0;
		virtual bool Initialize() = 0;
		virtual void Update() = 0;
		virtual void Render() = 0;
		virtual void Cleanup() = 0;
	private:
		bool InitializeEngine();
		void CleanupEngine();
		// Window
		GLFWwindow* window_;
		// Window size
		uint32_t width_ = 0, height_ = 0;
		// Window title
		std::string title_ = "";
		// Graphics version
		uint32_t major_ = 3, minor_ = 3;
		// Debug layer
		bool debugMode_ = false;
	};
}