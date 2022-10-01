#ifndef APPLICATION_HDR
#define APPLICATION_HDR

#include <vector>
#include <memory>
#include <string>

#include "../States/StateBase.h"
#include "../Renderer/RenderMaster.h"
#include "../Source/Camera.h"

#include "Context.h"

namespace acid 
{
    class Application 
    {
    public:
        Application(std::string&& title);
        ~Application() = default;

        void mainLoop();

        template<typename T, typename... Args>
        void pushState(Args&&... args) 
        {
            _states.push_back(std::make_unique<T>(std::forward<Args>(args)...));
            auto& s = _states.back();
        }

        Camera& getCamera() { return _camera; }
        const sf::RenderWindow& getWindow() const { return _context.window; }

        void popState();
    private:
        void handleEvents();

        std::vector<std::unique_ptr<StateBase>> _states;

        Context _context;
        RenderMaster _masterRenderer;
        Camera _camera;

        bool _isPopState = false;
    };
}

#endif // !APPLICATION_HDR
