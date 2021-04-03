#ifndef LOGM_H
#define LOGM_H

#include<iostream>
#include <string>
#include <fstream>

class LogM
{
public:
	enum class MessageType : unsigned short {
		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO
	};

	LogM() = delete;
	LogM(const LogM&) = delete;
	LogM(LogM&&) = delete;
	LogM& operator=(const LogM&) = delete;
	LogM& operator=(LogM&&) = delete;

	static void OnCreate(const std::string& name_ = "GAME258EngineLog");
	static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError(const std::string& message_, const std::string& fileName_, const int line_);

private:
	static void Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_);
	static MessageType currentSev;
	static std::string outputName;
};
#endif

