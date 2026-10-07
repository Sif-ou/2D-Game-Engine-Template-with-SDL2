#include "Window.hpp"



Window::Window( const char * title , int x , int y , int w , int h , Uint32 flags )
{
    window = SDL_CreateWindow ( title , x , y , w , h , flags ) ;
    LOG_INFO ( LOG::LOG_DEFAULT_TYPE , "WINDOW" , "window created successfully") ;
}

Window::~Window()
{
    SDL_DestroyWindow( window ) ;
    LOG_INFO ( LOG::LOG_DEFAULT_TYPE , "WINDOW" , "window destroyed") ;
}

SDL_Window* Window::getWindow()
{

    return window ;
}
