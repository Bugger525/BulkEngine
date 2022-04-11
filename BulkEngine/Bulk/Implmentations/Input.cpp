#include "../Input.h"
#include "../GameWindow.h"

#include <GLFW/glfw3.h>

namespace BK
{
	Input::Input(GameWindow* window)
	{
		window_ = window;
	}
	bool Input::GetKeyDown(Keys key)
	{
		return (glfwGetKey(window_->GetWindow(), static_cast<int>(key)) == GLFW_PRESS);
	}
	bool Input::GetKeyUp(Keys key)
	{
		return (glfwGetKey(window_->GetWindow(), static_cast<int>(key)) == GLFW_RELEASE);
	}
}