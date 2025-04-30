#include "core/Application.h"

int main() {
    Application app;
    if(app.initialize("ECS", 800, 600)) {
        app.run();
    }
    return 0;
}
