#include "CondorEngine/debug.hpp"
// std
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

bool CondorEngine::Debug::hasInit = false;

void CondorEngine::Debug::init() {
    // do NOT reinitialize during a single run of the application.
    if (hasInit) { return; }

    // create/open file
    std::ofstream file("Log.log");
    if (!file.is_open()) {
        throw std::runtime_error("Debug :: Failed to create/open log file!");
    }

    // time
    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);

    // header
    file << "#Version 1.0" << std::endl;
    file << "#Date: " << localTime->tm_year + 1900 << "-" << localTime->tm_mon + 1 << "-" << localTime->tm_mday;
    file << " " << localTime->tm_hour << ":" << localTime->tm_min << ":" << localTime->tm_sec << std::endl;
    file << "#Fields: time type message" << std::endl;

    // complete
    file.close();
    Log("CondorEngine::Debug :: Log file has initialized."); // only console log log file init
    hasInit = true;
}

void CondorEngine::Debug::Log(const char* msg) {
    std::string print = "[" + getTime() + "] INFO " + msg;
    std::cout << print << std::endl;
    printToFile(print);
}

void CondorEngine::Debug::Log(std::string msg) {
    Log(msg.c_str());
}
void CondorEngine::Debug::LogWarning(const char* msg) {
    std::string print = "[" + getTime() + "] WARNING " + msg;
    std::clog << print << std::endl;
    printToFile(print);
}

void CondorEngine::Debug::LogWarning(std::string msg) {
    LogWarning(msg.c_str());
}
void CondorEngine::Debug::LogError(const char* msg) {
    std::string print = "[" + getTime() + "] ERROR " + msg;
    std::cerr << print << std::endl;
    printToFile(print);
}

void CondorEngine::Debug::LogError(std::string msg) {
    LogError(msg.c_str());
}

void GLAPIENTRY CondorEngine::Debug::GLMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
    std::stringstream print;
    print << "[" << getTime() << "] ";

    if (type == GL_DEBUG_TYPE_ERROR) {
        print << "ERROR ";
    }
    else {
        print << "WARNING ";
    }
    print << "GL CALLBACK: type = 0x" << std::hex << type << ", " << "severity = 0x" << std::hex << severity << ", message = " << message;

    std::cout << print.str() << std::endl;
    printToFile(print.str());
}

std::string CondorEngine::Debug::getTime() {
    std::time_t now = std::time(0);
    std::tm* localTime = std::localtime(&now);
    char timeBuffer[80];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", localTime);
    return std::string(timeBuffer);
}

void CondorEngine::Debug::printToFile(const std::string& message) {
    std::ofstream file("Log.log", std::ios::app);
    if (file.is_open()) {
        file << message << std::endl;
        file.close();
    }
    else {
        throw std::runtime_error("Debug :: Failed to open log file!");
    }
}
