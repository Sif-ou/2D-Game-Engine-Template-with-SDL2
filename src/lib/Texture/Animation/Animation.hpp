#pragma once
#include "../../../Header.hpp"
#include "../Texture.hpp"
#include "../../Renderer/Renderer.hpp"


/* #TODO define rules ( status : ongoing ) */
/**
 * # RULES 
 * 
 * ## ERROR
 * - duration > 0 and must be defined 
 * - texture != nullptr 
 * - dstRect = { .... } must contain values 
 * - for each <SDL_Rect>frames srcRect must contain values 
 * 
 * ## WARNING 
 * - repeated elements from <SDL_Rect>frames 
 * 
 */



namespace Textures 
{

class Animation 
{

  private : 

    float m_animationTimer ;
    int m_count ;
    float m_duration ;
    SDL_Texture * m_texture = nullptr ;
    std::vector<SDL_Rect> m_frames ; // srcRect for each frame 
    SDL_Rect m_dstRect ;


  public :

    Animation() = delete ;

    Animation ( const float duration , SDL_Texture * texture , std::vector<SDL_Rect> frames , SDL_Rect dstRect) : 
               m_duration(duration) , m_texture(texture) , m_frames(std::move(frames)) , m_dstRect(dstRect) {}
    ~Animation() ;

    /* Copy & Copy Assignment */  
    Animation(const Animation&) = delete;
    Animation& operator=(const Animation&) = delete;


    /* Move Semantics : Move Constructor & Move Assignment */
    Animation (  Animation && other ) noexcept ;
    Animation& operator=(Animation&& other) noexcept ;




    public : 

     void UpdateAnimate ( const float DeltaTime ) ;


     /* getters & setters */
     /**/
     [[nodiscard]] float getAnimationTimer() const ;
     void setAnimationTimer ( const float animationTimer ) ;

     /**/
     [[nodiscard]] int getFrameCount() const ;
     void setFrameCount( const int count ) ;

     /**/
     [[nodiscard]] float getDuartion () const ;
     void setDuration ( const float duration ) ;

     /**/
     [[nodiscard]] const SDL_Texture * getTexture() const ;


     /**/
     [[nodiscard]] SDL_Rect getDstRect() const ;
     void setDstRect( const SDL_Rect dstRect ) ;
     

     /**/
     void setFrameAt ( const SDL_Rect srcRect , const int index ) ;
     void setFrames ( const std::vector<SDL_Rect> frames ) ;
     [[nodiscard]] SDL_Rect getFrameAt ( const int index ) const ;


     

} ;

}

/* #TODO : 
- more work on it 
-warp it around logger
-documentation  */