#include "Animation.hpp"


using namespace Textures ;

/*Destructor*/
Animation::~Animation() 
{
    if (m_texture)
    {
      SDL_DestroyTexture ( m_texture ) ;
    }
}

/*Move Assignment*/
Animation& Animation::operator=( Animation&& other ) noexcept
{
  if (this != &other) 
  {
     if (m_texture) 
      SDL_DestroyTexture(m_texture); 
     
     m_animationTimer = other.m_animationTimer;
     m_count = other.m_count;
     m_duration = other.m_duration;
     m_texture = other.m_texture;
     m_frames = std::move(other.m_frames);
     other.m_texture = nullptr;           
  }

  return *this;
}

/*Move Constructor*/
Animation::Animation(  Animation && other ) noexcept : m_texture(other.m_texture) , 
                                                       m_frames(std::move(other.m_frames)) , 
                                                       m_duration(other.m_duration) , m_count(other.m_count) , 
                                                       m_animationTimer(m_animationTimer) 
{ 
  other.m_texture = nullptr ; 
} 


/**
* play the animation
*/
void Animation::UpdateAnimate(const float DeltaTime)
{
    if (m_frames.empty() || m_duration <= 0.0f)
        return;

    const int   frameCount    = static_cast<int>(m_frames.size());
    const float frameDuration = m_duration / static_cast<float>(frameCount);

    m_animationTimer += std::clamp(DeltaTime, 0.0f, 0.1f);   

    while (m_animationTimer >= frameDuration)
    {
        m_animationTimer -= frameDuration;
        m_count = (m_count + 1) % frameCount;
    }
}




/**/
float Animation::getAnimationTimer() const 
{
   return m_animationTimer ;
}
// TODO apply checks and rules 
void Animation::setAnimationTimer ( const float animationTimer ) 
{
    m_animationTimer = animationTimer ;
}

/**/
int Animation::getFrameCount() const 
{
    return m_count ;
}
// TODO apply checks and rules 
void Animation::setFrameCount( const int count ) 
{
    m_count = count ;
}

/**/
float Animation::getDuartion () const 
{
    return m_duration ;
}
// TODO apply checks and rules 
void Animation::setDuration ( const float duration ) 
{
    m_duration = duration ;
}

/**/
SDL_Texture * Animation::getTexture() const 
{
    return m_texture ;
}

/**/
SDL_Rect Animation::getDstRect() const 
{
   return m_dstRect ; 
}
// TODO apply checks and rules 
void Animation::setDstRect( const SDL_Rect dstRect ) 
{
    m_dstRect = dstRect ;
}


/**/
// TODO apply checks and rules
void Animation::setFrameAt ( const SDL_Rect srcRect , const int index ) 
{
    m_frames[index] = srcRect ;
}

// TODO apply checks and rules
void Animation::setFrames ( const std::vector<SDL_Rect> frames ) 
{
    m_frames = std::move(frames) ;
}

SDL_Rect Animation::getFrameAt ( const int index ) const 
{
    return m_frames[index] ;
}

/*
void Animation::UpdateAnimate( const float DeltaTime )
{

    if ( !m_frames.empty() )
    {
        const float FrameDuration = m_duration / m_frames.size() ;
        const int frame = 1 ;

        m_animationTimer += DeltaTime ;
        if ( m_animationTimer >= FrameDuration )
        {
            if ( ( m_count + frame ) % m_frames.size() == m_frames.size() - frame )
             m_count = 0 ;
            else
             m_count = ( m_count + frame ) % m_frames.size() ;

             m_animationTimer -= FrameDuration ;
        }
    }
    else
     std:: cerr << " failed to animate : empty frames at Animation.cpp " << std::endl ;

}
*/