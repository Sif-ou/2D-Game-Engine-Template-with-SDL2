#include "TextureManager.hpp"

using namespace Textures ;

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}



/**
 * TODO : insert all of the Textures froma a given json file to textures map 
 */
void TextureManager::InsertTexture()
{

}


/**
 * TODO : insert all of the animation from a given json file to animation map 
 */
void TextureManager::InsertAnimation()
{

}


void TextureManager::InsertSingleTextuer ( const std::string& name , const char* texture 
                         , const SDL_Rect srcRect , const SDL_Rect dstRect , SDL_Renderer * r ) 
{
    SDL_Surface * surf = IMG_Load ( texture ) ;
    m_textures.insert ( {name , Texture ( SDL_CreateTextureFromSurface( r , surf ) , srcRect , dstRect )} ) ;

    SDL_FreeSurface ( surf ) ;

}


void TextureManager::InsertSingleAnimation ( const std::string& name , const char* texture 
                               , const float duration , std::vector<SDL_Rect> frames , SDL_Renderer * r , SDL_Rect dstRect ) 
{
    SDL_Surface * surf = IMG_Load ( texture ) ;

    Animation temp_anime (  { duration , SDL_CreateTextureFromSurface ( r , surf ) , std::move(frames) , dstRect } ) ;

    m_animations.insert ( { name , std::move(temp_anime) } ) ; 

    SDL_FreeSurface ( surf ) ;
}


