
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
#include <vector>
#include <unordered_map>
#include "Group.hpp"
#include "Map.hpp"


int main(int, char const**)
{
    using namespace std::chrono;
    using namespace std::this_thread;
    float x = 0;
    float y = 0;
    
    int frame = 0;
    int frame_boundary = 800;
    int total_len = 0;
    int total_frames = 5;
    std::vector<Map::Res> renderList;
    
    std::unordered_map <int, sf::Sprite> spriteList;
    Map* m = new Map(total_frames);
    
    int ground = 513;
    int start_back_cloud = -720;
    int start_front_cloud = -675;
    int start_ground = 0;
    int start_ground2 = 800;
    int end_ground = -800;
    int end_ground2 = 0;
    int end_front_cloud = 445;
    int end_back_cloud = 690;
    int back_cloud_x = start_back_cloud;
    int front_cloud_x = start_front_cloud;
    int ground_x = start_ground;
    int ground2_x = start_ground2;
    
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
    sf::Texture box_texture;
    if (!box_texture.loadFromFile(resourcePath() + "Boxman.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite box_sprite;
    box_texture.setSmooth(true);
    box_sprite.setTexture(box_texture);
    
    sf::Texture background_texture;
    if (!background_texture.loadFromFile(resourcePath() + "Background.png")) {
        return EXIT_FAILURE;
    }
    
    sf::Sprite background_sprite;
    background_texture.setSmooth(true);
    background_sprite.setTexture(background_texture);
    
    sf::Texture back_cloud_texture;
    if (!back_cloud_texture.loadFromFile((resourcePath() + "CloudsBack.png"))){
        return EXIT_FAILURE;
    }
    sf::Sprite back_cloud_sprite;
    back_cloud_texture.setSmooth(true);
    back_cloud_sprite.setTexture(back_cloud_texture);
    
    
    sf::Texture front_cloud_texture;
    if (!front_cloud_texture.loadFromFile((resourcePath() + "CloudsFront.png"))){
        return EXIT_FAILURE;
    }
    
    sf::Sprite front_cloud_sprite;
    front_cloud_texture.setSmooth(true);
    front_cloud_sprite.setTexture(front_cloud_texture);
    
    sf::Texture ground_texture;
    if (!ground_texture.loadFromFile((resourcePath() + "FlatSurface.png"))){
        return EXIT_FAILURE;
    }
    
    sf::Sprite ground_sprite;
    sf::Sprite ground_sprite2;
    ground_texture.setSmooth(true);
    ground_sprite.setTexture(ground_texture);
    ground_sprite2.setTexture(ground_texture);
    
    sf::Texture platform_texture;
    if (!platform_texture.loadFromFile((resourcePath() + "Platform.png"))){
        return EXIT_FAILURE;
    }
    
    sf::Sprite platform_sprite;
    platform_texture.setSmooth(true);
    platform_sprite.setTexture(platform_texture);
    
    m->addRes(2, 200, 200, 120);
    spriteList[120] = platform_sprite;
    
    std::vector<Map::Res> frameRes = m->getRes(frame);
    for(int i = 0; i < frameRes.size(); i++){
        Map::Res r = frameRes[i];
        renderList.push_back(r);
    }
    
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
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
            
        }
        box_sprite.setPosition(e->getX(), e->getY());
        total_len = e->getDist();
        if(frame < 4){
            if(total_len > frame_boundary){
                int dist;
                dist = total_len - frame_boundary;
                frame += 1;
                frame_boundary += 800;
                for(int i = 0; i < renderList.size(); i++){
                    Map::Res r = renderList[i];
                    int frame_dist = frame - r.frame;
                    if(r.x <= dist){
                        if(frame_dist >= 1){
                            renderList.erase(renderList.begin() + i);
                        }
                    }
                }
                frameRes = m->getRes(frame);
                for(int i = 0; i < frameRes.size(); i++){
                    Map::Res r = frameRes[i];
                    if(r.x <= dist){
                        renderList.push_back(r);
                        frameRes.erase(frameRes.begin() + i);
                        m->Map::updateFrameRes(frameRes, frame);
                    }
                    
                }
                
            }

        }
        
        sleep_for(nanoseconds(18000000));
        // Clear screen
        window.clear();
        
        front_cloud_sprite.setPosition(front_cloud_x, 125);
        back_cloud_sprite.setPosition(back_cloud_x, 0);
        ground_sprite.setPosition(ground_x, ground);
        ground_sprite2.setPosition(ground2_x, ground);
        
        
        front_cloud_x = front_cloud_x + 3;
        back_cloud_x = back_cloud_x + 1;
        ground_x = ground_x - 2;
        ground2_x = ground2_x - 2;
        
        if(ground_x <= -800){
            ground_x = start_ground;
            ground2_x = start_ground2;
        }
        
        if(front_cloud_x >= end_front_cloud){
            front_cloud_x = start_front_cloud;
        }
        if(back_cloud_x >= end_back_cloud){
            back_cloud_x = start_back_cloud;
        }
        //Resize sprites
        background_sprite.setScale(.45, .6);
        back_cloud_sprite.setScale(.40, .35);
        front_cloud_sprite.setScale(.50, .45);
        ground_sprite.setScale(1.41, 1);
        ground_sprite2.setScale(1.41, 1);
        
        
       // Draw the sprite
        window.draw(background_sprite);
        window.draw(back_cloud_sprite);
        window.draw(front_cloud_sprite);
        window.draw(ground_sprite);
        window.draw(ground_sprite2);
        for(int i = 0; i < renderList.size(); i++){
            Map::Res r = renderList[i];
            sf::Sprite s = spriteList[r.id];
            int temp_len = (total_len - (r.frame - 1) * 800 + r.x);
            s.setPosition(( temp_len % 800), r.y);
            window.draw(s);
        }
        window.draw(box_sprite);

        // Update the window
        window.display();
        e->cycle();
    }

    return EXIT_SUCCESS;
}
