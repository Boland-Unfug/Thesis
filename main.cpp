#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    // Create a window with the same pixel depth as the desktop
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Test Window");

    // Main loop that continues until we close the window
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window button clicked
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear screen with a dark blue color
        window.clear(sf::Color(0, 0, 128));

        // Draw everything here...
        // window.draw(...);

        // End the current frame and display its contents on screen
        window.display();
    }

    return 0;
}
