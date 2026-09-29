#include "../../Header.hpp"
#include "../Texture/Texture.hpp"



namespace Graphics {


struct RenderCommand 
{

    SDL_Texture * texture = nullptr ;
    SDL_Rect srcRect { 0 , 0 , 0 , 0 } ; 
    SDL_Rect dstRect { 0 , 0 , 0 , 0 } ;
    int zIndex = 0 ;
    double angle = 0.0 ; 

};

}