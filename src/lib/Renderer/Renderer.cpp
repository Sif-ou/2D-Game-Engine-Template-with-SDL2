#include "Renderer.hpp"

using namespace Graphics ; 

/**/
Renderer::Renderer(SDL_Window* window)
{
    m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    
    LOG_INFO_DMODE ( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "renderer created successfully") ;

    if (!m_renderer) {
        LOG_FATAL ( LOG::LOG_DEFAULT_TYPE , "RENDERER" , SDL_GetError() ) ;
        //std::cerr << "Failed to create SDL_Renderer: " << SDL_GetError() << std::endl;
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
    
    LOG_WARN_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "Move Constructor is called" ) ;

    Destroy();
    m_renderer = other.m_renderer;
    other.m_renderer = nullptr;
}

/**
 * the pending queue will be dropped
 */
Renderer& Renderer::operator=(Renderer&& other) noexcept
{
    
    LOG_WARN_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "Move Assigment is called" ) ;
    
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
        
        LOG_DEBUG( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "SDL_Renderer destroyed" ) ;
        
    }
}


/**
 *
 */
void Renderer::setRenderCommand( SDL_Texture * texture , 
                                 const SDL_Rect srcRect , const SDL_Rect dstRect ,
                                 const int zIndex , const double angle )  
{

    if ( !texture )
    {
        LOG_ERROR ( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "texture is null while setting RenderCommand with src & dst Rect") ;
        return ;
    } 

    
     LOG_INFO_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "setting RendererCommand with both dst & src Rect" ) ;
     

     m_queue.emplace_back( RenderCommand{ texture , srcRect , dstRect , zIndex , angle } ) ;
     

     LOG_DEBUG( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "RenderCommand has been set with both src & dst Rect" ) ;

}

/**
 * # setRenderCommand Overload 
 * no dstRect
 */
void Renderer::setRenderCommandDst( SDL_Texture * texture , 
                                 const SDL_Rect dstRect ,
                                 const int zIndex , const double angle )  
{

    if ( !texture )
    {
        LOG_ERROR ( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "texture is null while setting RenderCommand with dst Rect") ;
        return ;
    } 

     LOG_WARN_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "setting RendererCommand with only dstRect" ) ;
     
     m_queue.emplace_back( RenderCommand{ texture , {0,0,0,0} , dstRect , zIndex , angle , true } ) ;
     
     LOG_DEBUG( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "RenderCommand has been set with dst Rect" ) ;
}

/**
 * # setRenderCommand Overload 
 * no dstRect
 */
void Renderer::setRenderCommandSrc ( SDL_Texture * texture ,   
                        const SDL_Rect srcRect ,
                        const int zIndex , const double angle )  
{

    if ( !texture )
    {
        LOG_ERROR ( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "texture is null while setting RenderCommand with src Rect") ;
        return ;
    } 

     LOG_WARN_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "setting RendererCommand with only src Rect" ) ;
     
     m_queue.emplace_back( RenderCommand{ texture , srcRect , {0,0,0,0} , zIndex , angle , false , true } ) ;
     
     LOG_DEBUG( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "RenderCommand has been set with src Rect" ) ;

}

/**/
void Renderer::setRenderCommand ( SDL_Texture * texture ,   
                                const int zIndex , const double angle )  
{

    if ( !texture )
    {
        LOG_ERROR ( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "texture is null while setting RenderCommand with no src & dst Rect") ;
        return ;
    } 

     LOG_WARN_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "setting RendererCommand with no src & dst Rect" ) ;
     
     m_queue.emplace_back( RenderCommand{ texture , {0,0,0,0} , {0,0,0,0} , zIndex , angle , true , true } ) ;
     
     LOG_DEBUG( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "RenderCommand has been set with no src & dst Rect" ) ;

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

    LOG_INFO_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "sorting RenderCommand based on zIndex finished" ) ;

    for (const auto& cmd : m_queue) 
    {

       const SDL_Rect* pSrc = cmd.srcNull ? nullptr : &cmd.srcRect;
       const SDL_Rect* pDst = cmd.dstNull ? nullptr : &cmd.dstRect;
       
       SDL_RenderCopyEx( m_renderer, cmd.texture, 
                         &cmd.srcRect, &cmd.dstRect, 
                         cmd.angle , nullptr , SDL_FLIP_NONE );
    
    }
    LOG_INFO_DMODE( LOG::LOG_DEFAULT_TYPE , "RENDERER" , "rendering frames finished" ) ;

    m_queue.clear();
}