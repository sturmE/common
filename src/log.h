#ifndef __log_h__
#define __log_h__

#include <iostream>
#include <iomanip>
#include <errno.h>

#define MAIN_LOG_ERRNO(msg) LOG_E("main", msg << " (errno: " << strerror(errno) << ")")
#define MAIN_LOG_E(msg) LOG_E("main", msg)
#define MAIN_LOG_W(msg) LOG_W("main", msg)
#define MAIN_LOG_D(msg) LOG_D("main", msg)
#define MAIN_LOG_V(msg) LOG_V("main", msg)
#define LOG_E(channel, msg) LOG(channel, "ERROR", msg)
#define LOG_W(channel, msg) LOG(channel, "WARN", msg)
#define LOG_D(channel, msg) LOG(channel, "DEBUG", msg)
#define LOG_V(channel, msg) LOG(channel, "VERBOSE", msg)
#define LOG(channel, severity, msg) do { std::cout << "(" << channel << " [" << std::left << std::setw(5) << severity << "]) " << msg << std::endl; } while(false)

#endif