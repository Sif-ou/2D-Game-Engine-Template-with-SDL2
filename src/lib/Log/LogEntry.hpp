#pragma once 
#include "LogLevel.hpp"
#include <fstream>
#include <filesystem>
#include <string_view>
#include <memory>
#include <chrono>

namespace LOG 
{

 /**/
 inline constexpr std::string_view LogFileName = "Log.log" ; // name of the output logfile  

 /* log levels as string_view just for output */
 inline constexpr std::string_view LOG_DEBUG_INFO = "[DEBUG]" ;
 inline constexpr std::string_view LOG_INFO = "[INFO]" ;
 inline constexpr std::string_view LOG_WARN = "[WARN]" ;
 inline constexpr std::string_view LOG_ERROR = "[ERROR]" ;
 inline constexpr std::string_view LOG_FATAL = "[FATAL]" ;

 
 /* the default log type */
 inline constexpr std::string_view LOG_DEFAULT_TYPE = "ENGINE" ;

}



