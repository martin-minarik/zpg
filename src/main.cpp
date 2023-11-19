// Martin Minarik, MIN0139, 2023

#include <iostream>
#include "application.h"
#include "scenes/scene_week_9.h"

int main() {
    Application &application = Application::get_instance();
    application.init();

    application.set_scene(new SceneWeek9());

    application.run();

    return 0;
}
