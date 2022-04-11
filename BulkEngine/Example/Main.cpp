#include "../Bulk/GameWindow.h"
#include "../Bulk/Input.h"
#include "../Bulk/Debug.h"

class MyGame : public BK::GameWindow
{
public:
	MyGame(const std::string& title, uint32_t width, uint32_t height)
		: BK::GameWindow(title, width, height)
	{
	}
	void SetupEngine() override
	{
		SetDebugMode(true);
		SetGLVersion(3, 3);
	}
	bool Initialize() override
	{
		BK::Debug::Log(std::to_string(GetDebugMode()));
		BK::Debug::Log(std::to_string(GetGLVersionMajor()));
		BK::Debug::Log(std::to_string(GetGLVersionMinor()));

		return true;
	}
	void Update() override
	{
		BK::Input input{ this };
		if (input.GetKeyDown(BK::Keys::Escape))
			Close();
	}
	void Render() override
	{
	}
	void Cleanup() override
	{
	}
private:
};

int main(int argc, char* argv[])
{
	MyGame game{ "BulkWindow", 800, 600 };
	game.Run();
}