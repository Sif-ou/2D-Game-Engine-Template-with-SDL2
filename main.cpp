#include "src/lib/Renderer/Renderer.hpp"
#include "src/lib/Window/Window.hpp"
#include "src/lib/input/InputManager.hpp"
#include "src/lib/input/FileLoader/FileLoader.hpp"
#include "src/lib/Texture/TextureManager/TextureManager.hpp"
#include "src/lib/Texture/Animation/Animation.hpp"

#ifdef DEBUG
    #define R std::cout << "Debug mode active\n" ;
#else
    #define R std::cout << "Release mode active\n" ;
#endif




int getter( ) { return 0 ; }

int main ( int argc , char * argv[] )
{




    std::unique_ptr<Window> window ;
    std::unique_ptr<Graphics::Renderer> renderer ;
    InputManager input ;
    std::unique_ptr<Textures::TextureManager> texturemanager = std::make_unique<Textures::TextureManager>() ;

    //FileLoader f ;

   if ( SDL_Init ( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( " error in init %s" , SDL_GetError() ) ;
    }
    else
    {

     window = std::make_unique<Window>( " test " , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 720 , 720 , false ) ;
     renderer = std::make_unique<Graphics::Renderer>( window->getWindow() ) ;

     SDL_SetWindowResizable ( window->getWindow() , SDL_TRUE ) ;

    }





/*-----------------------------------------------------------*/

    const int x_blank = 5 ;
    const int y_blank = 2 ;

    const int m_w = 100 ;
    const int m_h = 125 ;
    const int x_middle = (720 / 2 ) - (m_w / 2);
    const int y_middle = (720 / 2) - (m_h / 2) ;


    const int x_size = 20 ;
    const int y_size = 32 ;

    const int x_space = 12 ;
    const int y_space = 4 ;

    std::vector<SDL_Rect> ff  ;

    ff.push_back( { SDL_Rect { 5 , 5 , 25 , 31 } } ) ;
    // , SDL_Rect { x_middle , y_middle , m_w , m_h }

    for ( int i = 0 ; i <= 8 ; i++ )
    {

       ff.push_back ( { SDL_Rect{ x_blank + ( x_size * i ) + ( x_space * i ) , 258 , x_size , y_size } } ) ;
    } //  , SDL_Rect{ x_middle , y_middle , m_w , m_h}






Textures::Animation anime = { 0.75 , SDL_CreateTextureFromSurface ( renderer->GetRenderer() , IMG_Load("temp_assets/test_img.png") ) 
                   , ff , SDL_Rect{ x_middle , y_middle , m_w , m_h}  } ;


texturemanager->InsertSingleAnimation ( "test" ,"temp_assets/test_img.png" , 0.75 , ff 
                                       , renderer->GetRenderer() , SDL_Rect{ x_middle , y_middle , m_w , m_h}) ; 
/*-----------------------------------------------------------*/



bool run = true ;

const float TARGET_FPS = 120.0f;
const float TARGET_FRAME_DURATION_MS = 1000.0f / TARGET_FPS; 

Uint64 frequency = SDL_GetPerformanceFrequency();
Uint64 previousTime = SDL_GetPerformanceCounter();

Uint64 fpsTimer = SDL_GetPerformanceCounter();
int frames = 0;
int fps = 0 ;


    while ( run )
    {

      /*-------------------------------------------------------------------------------*/  
      Uint64 currentTime = SDL_GetPerformanceCounter();
      float deltaTime = static_cast<float>(currentTime - previousTime) / static_cast<float>(frequency);
      previousTime = currentTime;
      /*-------------------------------------------------------------------------------*/


      


        renderer->Clear() ;
        input.Update();
        if ( input.hasQuitRequested() ) {
            run = false ;
        }

        renderer->RenderQueue() ;
        renderer->Present() ;
     



       /*------------------------------------------------------fps----------------------------------------------------------*/
          Uint64 frameEndTime = SDL_GetPerformanceCounter();
          float frameWorkTimeMs = static_cast<float>(frameEndTime - currentTime) * 1000.0f / static_cast<float>(frequency);
      
          
          if (frameWorkTimeMs < TARGET_FRAME_DURATION_MS) 
          {
              Uint32 delayTimeMs = static_cast<Uint32>(TARGET_FRAME_DURATION_MS - frameWorkTimeMs);
              SDL_Delay(delayTimeMs);
              
          }
   
           frames++;
           Uint64 currentTick = SDL_GetPerformanceCounter();
           if ( ( currentTick - fpsTimer) / static_cast<float>(frequency) >= 1.0f ) 
           {
               fps = frames ;
               frames = 0;
               fpsTimer = currentTick;
           }
           //std:: cout << fps << std::endl ;
        /*------------------------------------------------------------------------------------------------------------------*/ 
    } ;


    return 0 ;

}



/*

    SDL_Surface * surf = nullptr ;
    surf = IMG_Load ( "temp_assets/test_img.png") ;

    SDL_Texture * texture = nullptr ;
    texture = SDL_CreateTextureFromSurface ( renderer->GetRenderer() , surf ) ;
    SDL_FreeSurface( surf ) ;


    
    const int x_blank = 5 ;
    const int y_blank = 2 ;

    const int m_w = 100 ;
    const int m_h = 125 ;
    const int x_middle = (720 / 2 ) - (m_w / 2);
    const int y_middle = (720 / 2) - (m_h / 2) ;


    const int x_size = 20 ;
    const int y_size = 32 ;

    const int x_space = 12 ;
    const int y_space = 4 ;

    Frame animation [9] ;

    animation[0].srcRect.x = 5 ;
    animation[0].srcRect.y = 5 ;
    animation[0].srcRect.w = 25 ;
    animation[0].srcRect.h = 31 ;
    animation[0].dstRect.x = x_middle ;
    animation[0].dstRect.y = y_middle ;
    animation[0].dstRect.w = m_w ;
    animation[0].dstRect.h = m_h ;

    for ( int i = 0 ; i <= 8 ; i++ )
    {
       animation[i].srcRect.x = x_blank + ( x_size * i ) + ( x_space * i );
       animation[i].srcRect.y =  258  ;
       animation[i].srcRect.w = x_size ;
       animation[i].srcRect.h = y_size ;
       animation[i].dstRect.x = x_middle ;
       animation[i].dstRect.y = y_middle ;
       animation[i].dstRect.w = m_w ;
       animation[i].dstRect.h = m_h ;
    }

Animation tester ; 
tester.m_duration = 0.75 ;   
tester.m_texture = texture ;

for ( int i = 0 ; i <= 8 ; i++ )
{
  tester.m_frames.push_back( { animation[i].srcRect , animation[i].dstRect } ) ;
}









SDL_Rect srcrect ;
srcrect.x = 3 ;
srcrect.y = 5 ;
srcrect.w = 25 ;
srcrect.h = 30 ;
SDL_Rect dstrect ;
dstrect.x = 720 / 4 ;
dstrect.y = 720 / 4 ;
dstrect.w = 300 ;
dstrect.h = 300 ;







SDL_Rect t ; 
texturemanager->InsertSingleTextuer ( "test" , "temp_assets/test_img.png" 
    , SDL_Rect( {100 , 100 , 250 , 250 } ) , SDL_Rect( {0 , 0 , 250 , 250 } ) , renderer->GetRenderer() ) ;



    const int x_blank = 5 ;
    const int y_blank = 2 ;

    const int m_w = 100 ;
    const int m_h = 125 ;
    const int x_middle = (720 / 2 ) - (m_w / 2);
    const int y_middle = (720 / 2) - (m_h / 2) ;


    const int x_size = 20 ;
    const int y_size = 32 ;

    const int x_space = 12 ;
    const int y_space = 4 ;

    std::vector<Frame> animation  ;

    animation.push_back( { SDL_Rect { 5 , 5 , 25 , 31 } , SDL_Rect { x_middle , y_middle , m_w , m_h } } ) ;


    for ( int i = 0 ; i <= 8 ; i++ )
    {

       animation.push_back ( { SDL_Rect{ x_blank + ( x_size * i ) + ( x_space * i ) , 258 , x_size , y_size } 
                              , SDL_Rect{ x_middle , y_middle , m_w , m_h} } ) ;
    }


    texturemanager->InsertSingleAnimation( "test" , "temp_assets/test_img.png" , 0.75 , animation , renderer->GetRenderer()) ;



/*SDL_Surface * s = IMG_Load ( "temp_assets/test_img.png") ;
SDL_Texture * pop = SDL_CreateTextureFromSurface ( renderer->GetRenderer() , s ) ;
SDL_FreeSurface ( s ) ;




*/
