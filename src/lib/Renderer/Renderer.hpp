#pragma once
#include "RenderCommand.hpp"



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

    void Clear();
    void Present();
    void Destroy();
    void RenderQueue () ;
    
    /**
     * set RenderCommand in the Renderer queue 
    */
    void setRenderCommand ( SDL_Texture * texture , 
                            const SDL_Rect srcRect , const SDL_Rect dstRect ,
                            int zIndex  ,  double angle ) ;

    /**
     * get SDL_Renderer *
     */
    [[nodiscard]] SDL_Renderer* GetRenderer() const { return m_renderer; }
};


}








