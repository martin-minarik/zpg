// Martin Minarik, MIN0139, 2023

#include <iostream>
#include "application.h"

int main() {
    Application &application = Application::get_instance();
    application.run();

    return 0;
}
