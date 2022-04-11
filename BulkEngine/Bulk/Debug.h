#pragma once

#include <string>
#include <any>

namespace BK
{
	enum class DebugSource : int
	{
		API = 0x8246,
		WindowSystem = 0x8247,
		ShaderCompiler = 0x8248,
		ThirdParty = 0x8249,
		Application = 0x824A,
		Other = 0x824B
	};
	enum class DebugType : int
	{
		Error = 0x824C,
		DeprecatedBehavior = 0x824D,
		UndefinedBehavior = 0x824E,
		Portability = 0x824F,
		Performance = 0x8250,
		Marker = 0x8268,
		PushGroup = 0x8269,
		PopGroup = 0x826A,
		Other = 0x8251
	};
	enum class DebugSeverity : int
	{
		High = 0x9146,
		Medium = 0x9147,
		Low = 0x9148,
		Notification = 0x826A
	};
	class Debug
	{
	public:
		static void Log(const std::string& str);
		static void Log(const std::string& str, DebugSource source, DebugType type, DebugSeverity severity);
	};
}