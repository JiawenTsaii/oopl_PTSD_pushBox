#include "App.hpp"

#include "Core/Context.hpp"
#include "Util/Logger.hpp"
#include "Util/BGM.hpp"

#include <iostream>

int main(int, char**) {
    auto context = Core::Context::GetInstance();
    App app;
    //std::cout << "Entering main function" << std::endl;

    while (!context->GetExit()) {
        //std::cout << static_cast<int>(app.GetCurrentState()) << std::endl;
        Util::BGM m_BGM(RESOURCE_DIR "BGM/BGM_ground.mp3");
        
        switch (app.GetCurrentState()) {
            case App::State::START:
                app.Start();
                break;

            case App::State::UPDATE:
                app.Update();
                break;

            case App::State::END:
                app.End();
                context->SetExit(true);
                break;
        }
        context->Update();
    }
    return 0;
}
