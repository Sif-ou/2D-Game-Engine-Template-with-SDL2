#pragma once
#include "../../Header.hpp"

namespace Textures
{


/* #TODO define rules ( status : ongoing ) */
/**
 * # RULES 
 * 
 * ## ERROR
 * - texture is null / no created 
 * - If a texture has already been created, creating a new one or modifying the existing one is not allowed  
 * ## WARNING 
 * - srcRect is nullptr 
 * - dstRect is nullptr
 * 
 */



/* TOME
   srcrect (Source Rectangle): Which region of the image file/texture to cut out.
   dstrect (Destination Rectangle): Where on the screen to draw it, and what size to render it.
*/

class Texture
{
    private : 

    SDL_Texture* m_texture = nullptr;
    SDL_Rect m_srcRect{0, 0, 0, 0}; 
    SDL_Rect m_dstRect{0, 0, 0, 0};

    bool m_srcNull = false ; /* allow to be null or not */
    bool m_dstNull = false ; /* false = no null , true = null */

    public : 

    Texture() = default;
    Texture(SDL_Texture* texture, const SDL_Rect srcRect, const SDL_Rect dstRect) ;
    Texture(SDL_Texture* texture , const bool src , const bool dst ) ;
    
    ~Texture();

    // Disable copying to avoid double-freeing the texture pointer
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    // Enable move semantics for transfer of ownership
    Texture(Texture&& other) noexcept ;
    Texture& operator=(Texture&& other) noexcept ;


    public : 

    /* getters for srcRect & dstRect */
    [[nodiscard]] const SDL_Rect* getSrcRect () const ; 
    [[nodiscard]] const SDL_Rect* getDstRect () const ;

    /* setters for srcRect & dstRect */
    void setSrcRect( const SDL_Rect srcRect ) ;
    void setDstRect ( const SDL_Rect dstRect ) ;

    /**/
    [[nodiscard]] const SDL_Texture* getTexture() const ;

};

}