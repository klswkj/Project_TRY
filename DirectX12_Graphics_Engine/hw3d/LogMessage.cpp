#include "LogMessage.h"
#include <sstream>


LogMessage::LogMessage( int line,const char* file ) noexcept
	:
	line( line ),
	file( file )
{}

const char* LogMessage::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* LogMessage::GetType() const noexcept
{
	return "Chili Exception";
}

int LogMessage::GetLine() const noexcept
{
	return line;
}

const std::string& LogMessage::GetFile() const noexcept
{
	return file;
}

std::string LogMessage::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}