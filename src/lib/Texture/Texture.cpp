#include "Texture.hpp"

using namespace Textures ;


Texture::Texture(SDL_Texture* texture, const SDL_Rect& srcRect, const SDL_Rect& dstRect) 
                   : m_texture(texture), m_srcRect(srcRect), m_dstRect(dstRect) 
{
  /* won't let getters return nullptr for both rects */
  m_srcNull = false ; 
  m_dstNull = false ;

} 

Texture::Texture ( SDL_Texture * texture , const bool src , const bool dst ) 
                   : m_texture(texture) 
{
 m_srcNull = src ;
 m_dstNull = dst ;
}

/**/
Texture::~Texture()
{
  if (m_texture) {
    SDL_DestroyTexture(m_texture);
  }
}

/**/
Texture::Texture ( Texture && other ) noexcept : m_texture(std::exchange(other.m_texture, nullptr)) ,
                                                 m_srcRect(other.m_srcRect) ,
                                                 m_dstRect(other.m_dstRect) 
{} 

/**/
Texture& Texture::operator=(Texture&& other) noexcept 
{
  if (this != &other) {
      if (m_texture) SDL_DestroyTexture(m_texture);
      m_texture = std::exchange(other.m_texture, nullptr);
      m_srcRect = other.m_srcRect;
      m_dstRect = other.m_dstRect;
  }
  return *this;
    
}


/* getters for srcRect & dstRect */
const SDL_Rect* Texture::getSrcRect () const 
{
   if ( !m_srcNull )
    return &m_srcRect ;

   return nullptr ;
} 
/**/
const SDL_Rect* Texture::getDstRect () const
{
  if ( !m_dstNull )
   return &m_dstRect ;

  return nullptr ;
} 


/* setters for srcRect & dstRect */
void Texture::setSrcRect( const SDL_Rect srcRect ) 
{
   m_srcRect = srcRect ;
}
/**/
void Texture::setDstRect ( const SDL_Rect dstRect ) 
{
  m_dstRect = dstRect ;
}

/**/
const SDL_Texture* Texture::getTexture() const 
{
  return m_texture ;
}
