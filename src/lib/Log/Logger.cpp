#include "Logger.hpp"

using namespace LOG ;


Logger::Logger()
{
    /*everytime the log file is open old output will be deleted*/
    m_LogFile.open(std::string(LogFileName), std::ios::out | std::ios::trunc);

    /*in case for any error during creating / opening the file */
    #ifdef DEBUG
      if (!m_LogFile.is_open())
          std::cerr << "couldn't open or create log file\n";
      else
          std::cout << "log file ready\n";
    #endif 
}


Logger::~Logger()
{
    CloseLog() ;
}

void Logger::CloseLog()
{
    if (m_LogFile.is_open())
        m_LogFile.close();
}


void Logger::Print( LOG_LEVEL lvl , std::string_view type , 
                   const char * title , std::string_view msg ) 
{

   /**/
   auto now = std::chrono::system_clock::now();
   std::time_t t = std::chrono::system_clock::to_time_t(now);
   
   std::tm local{};
   #ifdef _WIN32
   localtime_s(&local, &t);
   #else
   localtime_r(&t, &local);
   #endif
   
   char buffer[24];
   std::strftime(buffer, sizeof(buffer), "|%m/%d/%y|%H:%M:%S|", &local);
   /**/

   std::string_view str_lvl ;
   std::string_view str_title ;

   switch (lvl)
   {

    case INFO:
     str_lvl = LOG_INFO ;
     break;

    #ifdef DEBUG
    case DEBUG_INFO:
     str_lvl = LOG_DEBUG_INFO ;
     break;
    #endif

    case WARN:
     str_lvl = LOG_WARN ;
     break;

    case ERROR:
     str_lvl = LOG_ERROR ;
     break;

    case FATAL:
     str_lvl = LOG_FATAL ;
     break;

    default:
     break;
   }


   if ( !title )
    title = "" ;


   m_LogFile << str_lvl
             << '{' << type << '}'
             << buffer 
             << '"' << title << '"'
             << ':'
             << msg 
             << '\n' ;
             
  #ifdef DEBUG
      m_LogFile.flush();
  #else
      if (lvl >= LOG_LEVEL::ERROR) m_LogFile.flush();
  #endif

}


