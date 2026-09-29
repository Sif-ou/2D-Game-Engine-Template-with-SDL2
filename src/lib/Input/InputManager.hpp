#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <array>
#include "KeyLoader/KeyLoader.hpp"


class InputManager 
{


private:

   
    const Uint8* m_keyboardState = nullptr ;
    std::array< SDL_Scancode , static_cast<size_t>(Action::COUNT) > m_Actions ;
    std::unique_ptr<KeyLoader> keyloader  ;


    bool m_quitRequested = false;
    int m_mouseX = 0;
    int m_mouseY = 0;

    bool test = false ;

public:

    InputManager() ;
    void Update() ;
    bool hasQuitRequested() const  ;


    
    bool isActionDown(Action action) const ;
    void bindAction(Action action, SDL_Scancode scancode) ;

    /*----------*/
    bool Test() { 
        
        return test ;
    
    }


    int getMouseX() const ; 
    int getMouseY() const ;


};

