#include "ModelLogMessage.h"
#include <sstream>

ModelLogMessage::ModelLogMessage( int line,const char* file,std::string note ) noexcept
	:
	LogMessage( line,file ),
	note( std::move( note ) )
{}

const char* ModelLogMessage::what() const noexcept
{
	std::ostringstream oss;
	oss << LogMessage::what() << std::endl
		<< "[Note] " << GetNote();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ModelLogMessage::GetType() const noexcept
{
	return "Chili Model Exception";
}

const std::string& ModelLogMessage::GetNote() const noexcept
{
	return note;
}