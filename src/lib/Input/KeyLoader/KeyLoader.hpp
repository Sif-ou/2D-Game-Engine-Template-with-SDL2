#pragma once
#include "../../../Header.hpp"
#include <filesystem>
#include <fstream>
#include "../../../external/nlohmann/json.hpp"


using json = nlohmann::json ;

enum class Action 
{
    test ,
    COUNT 
} ;


constexpr int KEYS_NUM = 1 ;
const std::string KEY_BINDS_FILE = "../../../../test.json";

class KeyLoader
{

private:
    

   std::array < SDL_Scancode , KEYS_NUM > m_Keys ;


public:

    KeyLoader() ;
    ~KeyLoader() = default ;


    std::array < SDL_Scancode , KEYS_NUM >& getKeys()  ;

    
};


