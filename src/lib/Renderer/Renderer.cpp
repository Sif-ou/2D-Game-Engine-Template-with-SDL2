#include "Renderer.hpp"

using namespace Graphics ; 

/**/
Renderer::Renderer(SDL_Window* window)
{
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        std::cerr << "Failed to create SDL_Renderer: " << SDL_GetError() << std::endl;
    }
}


/**/
Renderer::~Renderer()
{
    Destroy();
}


/**
 * the pending queue will be dropped
 */
Renderer::Renderer(Renderer&& other) noexcept 
{
    Destroy();
    m_renderer = other.m_renderer;
    other.m_renderer = nullptr;
}

/**
 * the pending queue will be dropped
 */
Renderer& Renderer::operator=(Renderer&& other) noexcept
{
    if (this != &other) {
        Destroy();
        m_renderer = other.m_renderer;
        other.m_renderer = nullptr;
    }
    return *this;
}


/**/
void Renderer::Clear()
{
    if (m_renderer) {
        SDL_RenderClear(m_renderer);
    }
}

/**/
void Renderer::Present()
{
    if (m_renderer) {
        SDL_RenderPresent(m_renderer);
    }
}

/**/
void Renderer::Destroy()
{
    if (m_renderer) {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr; 
    }
}


/**
 * # setRenderCommand Overload 
 * 
 */
void Renderer::setRenderCommand( SDL_Texture * texture , 
                                 const SDL_Rect srcRect , const SDL_Rect dstRect ,
                                 const int zIndex , const double angle )  
{

    if ( !texture )
     return ;

     m_queue.emplace_back( RenderCommand{ texture , srcRect , dstRect , zIndex , angle } ) ;

}

/**
 * # setRenderCommand Overload 
 * no dstRect
 */
void Renderer::setRenderCommand( SDL_Texture * texture , 
                                 const SDL_Rect dstRect ,
                                 const int zIndex , const double angle )  
{

    if ( !texture )
     return ;

     m_queue.emplace_back( RenderCommand{ texture , {0,0,0,0} , dstRect , zIndex , angle , true } ) ;

}

/**
 * # setRenderCommand Overload 
 * no dstRect
 */
void Renderer::setRenderCommand ( SDL_Texture * texture ,   
                        const SDL_Rect srcRect ,
                        const int zIndex , const double angle )  
{

    if ( !texture )
     return ;

     m_queue.emplace_back( RenderCommand{ texture , srcRect , {0,0,0,0} , zIndex , angle , false , true } ) ;

}


void Renderer::setRenderCommand ( SDL_Texture * texture ,   
                                const int zIndex , const double angle )  
{

    if ( !texture )
     return ;

     m_queue.emplace_back( RenderCommand{ texture , {0,0,0,0} , {0,0,0,0} , zIndex , angle , true , true } ) ;

}


/**/
void Renderer::RenderQueue()
{

    std::stable_sort(m_queue.begin(), m_queue.end(), [](const RenderCommand& a, const RenderCommand& b) {
        if (a.zIndex != b.zIndex) {
            return a.zIndex < b.zIndex ;
        }
        return a.texture < b.texture ; 
    });


    for (const auto& cmd : m_queue) 
    {

       const SDL_Rect* pSrc = cmd.srcNull ? nullptr : &cmd.srcRect;
       const SDL_Rect* pDst = cmd.dstNull ? nullptr : &cmd.dstRect;
       
       SDL_RenderCopyEx( m_renderer, cmd.texture, 
                         &cmd.srcRect, &cmd.dstRect, 
                         cmd.angle , nullptr , SDL_FLIP_NONE );
    
    }


    m_queue.clear();
}