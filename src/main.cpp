#include "core/Application.h"

int main() {
    Application app;
    if(app.initialize("Metroidvania", 800, 600)) {
        app.run();
    }
    return 0;
}
