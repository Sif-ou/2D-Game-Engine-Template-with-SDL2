#include "KeyLoader.hpp"



KeyLoader::KeyLoader()
{

    namespace fs = std::filesystem ;


    char* base = SDL_GetBasePath();
    fs::path fullPath;

    if (base) {
        fullPath = fs::path(base).parent_path() / KEY_BINDS_FILE;
        SDL_free(base); 
    } else {
        fullPath = KEY_BINDS_FILE; 
    }


    std::ifstream file(fullPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file at: " << fullPath << "\n";
        return;
    }

    json data = json::parse(file);
    size_t i = 0;

    for (auto& keyString : data.items())
    {
        if (i >= m_Keys.size()) break;

        std::string keyName = keyString.value().get<std::string>();
        m_Keys[i] = SDL_GetScancodeFromName(keyName.c_str());
        i++;
    }

}



std::array < SDL_Scancode , KEYS_NUM>& KeyLoader::getKeys() 
{
    return m_Keys ;
}