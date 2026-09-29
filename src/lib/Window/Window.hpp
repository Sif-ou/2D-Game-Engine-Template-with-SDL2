#pragma once 
#include "../../Header.hpp"


class Window
{

private:

   SDL_Window * window = nullptr ;

public:

    Window( const char * title , int x , int y , int w , int h , Uint32 flags );
    ~Window();
    SDL_Window* getWindow () ;

};

