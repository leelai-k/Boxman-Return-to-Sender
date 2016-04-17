
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "Engine.hpp"
#include <chrono>
#include <thread>

int main(int, char const**)
{
    using namespace std::chrono;
    using namespace std::this_thread;
    float x = 0;
    float y = 0;
    
    Engine* e = new Engine();
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile(resourcePath() + "Boxman.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    texture.setSmooth(true);
    
    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Hello SFML", font, 50);
    text.setColor(sf::Color::Black);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }

    // Play the music
    music.play();

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        e->clearButton();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            e->setLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            e->setRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            e->setUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            e->setDown();
        }
        while (window.pollEvent(event))
        {
            
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            /*
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                e->setLeft();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                e->setRight();
            }
            if (event.type == sf::Event::KeyPressed && ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::Space))) {
                e->setUp();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                e->setDown();
            }
             */
            
        }
        sprite.setPosition(e->getX(), e->getY());
        sleep_for(nanoseconds(18000000));
        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
        e->cycle();
    }

    return EXIT_SUCCESS;
}
