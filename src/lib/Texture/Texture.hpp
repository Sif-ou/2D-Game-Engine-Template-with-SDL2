#pragma once
#include "../../Header.hpp"




/**
 * 
 * TODO
 * log output
 * fix code architecture , see below for more details  
 */



namespace Textures
{


/* #TODO define rules ( status : ongoing ) */
/**
 * # RULES 
 * 
 * ## ERROR
 * - texture is null / no created 
 * - If a texture has already been created, creating a new one or modifying the existing one is not allowed  
 * ## ERROR or WARN 
 * - srcRect is nullptr 
 * - dstRect is nullptr
 * 
 */



/* Info about src & dst 
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
    /**
     * 
     * TODO 
     * fix this code , because what if i want to put src null and dst with value ?
     * the error here is that we there is no way you can assing m_dstRect to a value 
     * in this case , because the constructor only have bool for both src and dst Rects
     * we know that we can assing values to the both of the Rect with the setters below 
     * but we want this fast way of constructor so it easy to use and read
     * 
     */
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