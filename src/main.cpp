#include <iostream>

#include <core/Engine.h>

int main()
{
    Photons::Engine *engine = new Photons::Engine();

    delete engine;
    return 0;
}
