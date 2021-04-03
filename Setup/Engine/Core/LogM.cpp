#include "LogM.h"

LogM::MessageType LogM::currentSev = MessageType::TYPE_NONE;
std::string LogM::outputName = "";

void LogM::OnCreate(const std::string& name_) {
	outputName = name_ + ".txt";
	std::ofstream out;
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	currentSev = MessageType::TYPE_INFO;
}

void LogM::SetSeverity(MessageType type_) {
	currentSev = type_;
}

void LogM::Info(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_INFO, "[INFO]:" +message_, fileName_, line_);
}

void LogM::Trace(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_TRACE, "[TRACE]:" + message_, fileName_, line_);
}

void LogM::Warning(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_WARNING, "[WARNING]:" + message_, fileName_, line_);
}

void LogM::Error(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_ERROR, "[ERROR]:" + message_, fileName_, line_);
}

void LogM::FatalError(const std::string& message_, const std::string& fileName_, const int line_) {
	Log(MessageType::TYPE_FATAL_ERROR, "[FATAL ERROR]:" + message_, fileName_, line_);
}

void LogM::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_) {
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE) {
		std::ofstream out;
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		out << message_ << "in:" << fileName_ << " on line:" << line_ << std::endl;
		out.flush();
		out.close();
	}
}
