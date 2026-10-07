#pragma once
#include "LogEntry.hpp"

namespace LOG
{

 class Logger
 {

   private:

    std::ofstream m_LogFile ;
    /*mutex here in case multithreading*/

    private : 
      
     Logger();
     ~Logger();

   public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

   public : 
     
      static Logger& Get ()
      {
         static Logger instance ;
         return instance ;
      }

      void Print ( LOG_LEVEL lvl , std::string_view type , 
                   const char * title , std::string_view msg ) ;

      void CloseLog() ;


 };

}


/*MACROS*/
/**
 * 
 * TODO
 * possible change after timestamp in Print function  
 * 
 */

#ifdef DEBUG
 #define LOG_DEBUG(type , title , msg)  LOG::Logger::Get().Print(LOG::LOG_LEVEL::DEBUG_INFO,  (type) , (title) , (msg) )
 #define LOG_INFO_DMODE(type , title , msg)  LOG::Logger::Get().Print(LOG::LOG_LEVEL::INFO,  (type) , (title) , (msg) )
 #define LOG_WARN_DMODE(type , title , msg)  LOG::Logger::Get().Print(LOG::LOG_LEVEL::WARN,  (type) , (title) , (msg) )
 #define LOG_ERROR_DMODE(type , title , msg) LOG::Logger::Get().Print(LOG::LOG_LEVEL::ERROR, (type) , (title) , (msg) )
#endif



#define LOG_INFO(type , title , msg)  LOG::Logger::Get().Print(LOG::LOG_LEVEL::INFO,  (type) , (title) , (msg) )
#define LOG_WARN(type , title , msg)  LOG::Logger::Get().Print(LOG::LOG_LEVEL::WARN,  (type) , (title) , (msg) )
#define LOG_ERROR(type , title , msg) LOG::Logger::Get().Print(LOG::LOG_LEVEL::ERROR, (type) , (title) , (msg) )
#define LOG_FATAL(type , title , msg)  LOG::Logger::Get().Print(LOG::LOG_LEVEL::FATAL,  (type) , (title) , (msg) )
