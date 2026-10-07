#pragma once
#include "RenderCommand.hpp"


/**
 * 
 * TODO
 * log output
 * 
 */

namespace Graphics {

class Renderer
{

 private:

    SDL_Renderer* m_renderer = nullptr ;
    std::vector<RenderCommand> m_queue ;

 public:

    explicit Renderer(SDL_Window* window);
    ~Renderer();

    /* Copy & Copy Assignment */
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    /* Move Semantics : Move Constructor & Move Assignment */
    Renderer(Renderer&& other) noexcept ;
    Renderer& operator=(Renderer&& other) noexcept ;

 public : 

    /**
     * get SDL_Renderer *
     */
    [[nodiscard]] SDL_Renderer* GetRenderer() const { return m_renderer; }

    void Clear();
    void Present();
    void Destroy();
    void RenderQueue () ;
    

 /* TODO add overload methods after TODO on RenderCommand.hpp   */
 /**
  * # RendererCommand  method & overload
  *  */   
 public : 
 /**
  * set a RenderCommand type to Renderer queue   
  */

    /**
     * TODO documentation on this after TODO on RenderCommand.hpp     
     * */
    void setRenderCommand ( SDL_Texture * texture , 
                            const SDL_Rect srcRect , const SDL_Rect dstRect ,
                            const int zIndex  , const double angle )  ;
    /**
     *TODO documentation on this after TODO on RenderCommand.hpp  
     * no srcRect ( nullptr )
     */                       
    void setRenderCommandDst ( SDL_Texture * texture ,   
                            const SDL_Rect dstRect ,
                            const int zIndex , const double angle )  ;

    /**
     * TODO documentation on this after TODO on RenderCommand.hpp  
     * no dstRect ( nullptr )
     */                       
    void setRenderCommandSrc ( SDL_Texture * texture ,   
                            const SDL_Rect srcRect ,
                            const int zIndex , const double angle )  ;

    /**
     * TODO documentation on this after TODO on RenderCommand.hpp
     * no dstRect ( nullptr )
     */                       
    void setRenderCommand ( SDL_Texture * texture ,   
                            const SDL_Rect srcRect ,
                            const int zIndex , const double angle )  ;

    /**
     * TODO documentation on this after TODO on RenderCommand.hpp
     * no dstRect & srcRect ( nullptr ) 
     */                       
    void setRenderCommand ( SDL_Texture * texture ,   
                            const int zIndex , const double angle )  ;

};


}








