#include "Window.hpp"



Window::Window( const char * title , int x , int y , int w , int h , Uint32 flags )
{

    window = SDL_CreateWindow ( title , x , y , w , h , flags ) ;

}

Window::~Window()
{
    SDL_DestroyWindow( window ) ;
}

SDL_Window* Window::getWindow()
{

    return window ;
}
