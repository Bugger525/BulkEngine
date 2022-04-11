#include "../Debug.h"

#include <glad/glad.h>

namespace BK
{
	void Debug::Log(const std::string& str)
	{
		glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_MARKER, 0, GL_DEBUG_SEVERITY_LOW, -1, str.c_str());
	}
	void Debug::Log(const std::string& str, DebugSource source, DebugType type, DebugSeverity severity)
	{
		glDebugMessageInsert(static_cast<GLenum>(source), static_cast<GLenum>(type), 0, static_cast<GLenum>(severity), -1, str.c_str());
	}
}