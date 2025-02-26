#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <fstream>

class Logger{
public:
    static Logger* Instance();
    void report(const std::string&);
    ~Logger();
private:
    Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream file;
};

Logger::Logger() {
    file.open("log.txt",std::fstream::out | std::fstream::app);
}

void Logger::report(const std::string&input){
    file << input;
}

Logger* Logger::Instance(){
    static Logger obj;
    return &obj;
}

Logger::~Logger(){
    file.close();
}







#endif