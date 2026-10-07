#pragma once
#include "../../../EntryPoint.hpp"
#include "../Animation/Animation.hpp"

/**
 * 
 * TODO
 * log output
 * 
 */


namespace Textures
{


/* #TODO define rules ( status : ongoing ) */
/**
 * # RULES 
 * 
 * ## ERROR
 * - same name on the map ( if a name in m_textures is also in m_animation it consider okey )
 * 
 */   
class TextureManager
{


 public : // TODO private 

 std::unordered_map<std::string_view , Texture > m_textures ;
 std::unordered_map<std::string_view , Animation > m_animations ;



 public : 

    TextureManager();
    ~TextureManager();



 public :
    /*
     * insert all textures from a given JSON file  
     */
    void InsertTexture () ; // insert textures from json file
    
    /*
     * insert all textuers and frames from a given JSON file  
     */
    void InsertAnimation () ; // insert textures and frames from json file  




 public :
    /* Debug */

    void InsertSingleTextuer ( const std::string& name , const char* texture 
                             , const SDL_Rect srcRect , const SDL_Rect dstRect , SDL_Renderer * r ) ;
    void InsertSingleAnimation ( const std::string& name , const char* texture 
                               , const float duration ,  std::vector<SDL_Rect> frames , SDL_Renderer * r  , SDL_Rect dstRect) ;


};


}

