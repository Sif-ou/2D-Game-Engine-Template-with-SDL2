#include "InputManager.hpp"


InputManager::InputManager()
{
    keyloader = std::make_unique<KeyLoader>() ;
}

void InputManager::Update()
{
        m_quitRequested = false;

        SDL_Event event;
        while (SDL_PollEvent(&event)) {

            switch (event.type) {

                case SDL_QUIT:
                    m_quitRequested = true;
                    break;
               
                case SDL_MOUSEMOTION:
                    m_mouseX = event.motion.x;
                    m_mouseY = event.motion.y;
                    break;

            }
        }

}



bool InputManager::hasQuitRequested() const { return m_quitRequested; }
int InputManager::getMouseX() const { return m_mouseX; }
int InputManager::getMouseY() const { return m_mouseY; }


inline bool InputManager::isActionDown(Action action) const {
        SDL_Scancode scancode = m_Actions[static_cast<size_t>(action)];
        return m_keyboardState[scancode] != 0;
}


void InputManager::bindAction(Action action, SDL_Scancode scancode) {
        m_Actions[static_cast<size_t>(action)] = scancode;
}

