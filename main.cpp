#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>


#include "Agent.cpp"
#include "Screen.cpp"

int main()
{
    Screen screen(800.f, 800.f, "Box2D Test");
    
    screen.run();


    return 0;
}