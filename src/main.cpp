// Martin Minarik, MIN0139, 2023

#include <iostream>
#include "application.h"
#include "scenes/scene_4_spheres.h"

int main() {
    Application &application = Application::get_instance();
    application.init();

    application.set_scene(new Scene4Spheres());

    application.run();

    return 0;
}
