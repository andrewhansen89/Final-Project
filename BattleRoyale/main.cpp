#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include "player.hpp"
#include "bullet.hpp"
#include "platform.hpp"
#include "ResourcePath.hpp"

// window dimensions
int WIDTH = 800;
int HEIGHT = 600;
 
int main(int, char const**) {
 
    // Initalize time
    srand(time(0));
 
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
 
    RectObject bg("Background.png", sf::Vector2f(0, 0));
 
    // Initializes all platforms and sets their positions
    std::vector<Platform*> plats;
    plats.push_back(new SmallPlatform(sf::Vector2f(175, 475)));
    plats.push_back(new SmallPlatform(sf::Vector2f(575, 475)));
    plats.push_back(new SmallPlatform(sf::Vector2f(275, 400)));
    plats.push_back(new SmallPlatform(sf::Vector2f(475, 400)));
    plats.push_back(new MidPlatform(sf::Vector2f(50, 300)));
    plats.push_back(new MidPlatform(sf::Vector2f(600, 300)));
    plats.push_back(new FullPlatform(sf::Vector2f(250, 200)));
 
    // Create a player and an enemy
    Player player, enemy;
 
    // Clock properties
    sf::Clock clock;
    float dt;
 
    // Initializing the ip to the ip of the user
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char connectionType;
 
    // Establishing the server/client relationship
    std::cout << "server (s) or client (c)?\n";
    std::cin >> connectionType;
 
    if (connectionType == 's'){
        //the listener looks for a port to connect to
        sf::TcpListener listener;
        // Value of 2000 is arbitrary. anything under 1024 is considered a private
        // port and can not be used
        listener.listen(2000);
        // If a connection is found at port 2000, accept the connection and store it in the socket
        listener.accept(socket);
    }
    else
        socket.connect(ip, 2000);
 
    sf::Vector2f prevPosition, enemyPos;
    socket.setBlocking(false);
    bool update = false;
 
    while (window.isOpen()) { // game loop
 
        // Create the event object
        sf::Event event;
        dt = clock.restart().asSeconds();
 
        // While there are events going on
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::GainedFocus) {
                update = true;
            }
            else if (event.type == sf::Event::LostFocus) {
                update = false;
            }
            // Lost focus and gained focus were added so that you only control the window
            // you're clicked on. Not both windows at the same time.
 
            player.update(dt, event, window);
            enemy.update(dt, event, window); 
        }
 
        prevPosition = player.getPos();
       
        // This makes it so only the screen that's in focus is being moved
        if (update)
        {
            // Player movement
            player.move(dt);
        }
 
        // Gravity Logic: If the player isn't on a platform, allow gravity.
        // If a player is on a platform, allow jumping and stop gravity.
        player.allowGravity(plats);
 
        sf::Packet packet;
 
        // If position of the player changes
        if (prevPosition != player.getPos()){
            // Store position in packet
            packet << player.getPos().x << player.getPos().y;
            // Send packet to the socket
            socket.send(packet);
        }
 
        socket.receive(packet);
        // Store information in  packet in the enemy player class
        if (packet >> enemyPos.x >> enemyPos.y){
            enemy.setPos(enemyPos);
        }
 
 
        bg.draw(window); // Drawing Background
        for (auto it : plats) { // Drawing Platforms
            it->draw(window);
        }
 
        // Creating new bullet
        player.checkBullets(enemy, window);
 
        player.draw(window);
        enemy.draw(window);
 
        window.display();
        window.clear();
    }
 
    return EXIT_SUCCESS;
}
//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
//#include <iostream>
//#include <ctime>
//#include <vector>
//#include <thread>
//#include "player.hpp"
//#include "bullet.hpp"
//#include "platform.hpp"
//#include "ResourcePath.hpp"
//
//// window dimensions
//int WIDTH = 800;
//int HEIGHT = 600;
//
//int main(int, char const**) {
//
//    // Initalize time
//    srand(time(0));
//
//    // Create the window
//    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML window");
//    window.setFramerateLimit(60);
//    window.setKeyRepeatEnabled(true);
//
//    RectObject bg("Background.png", sf::Vector2f(0,0));
//
//    // Initializes all platforms and sets their positions
//    std::vector<Platform*> plats;
//    plats.push_back( new SmallPlatform(sf::Vector2f(175,475)));
//    plats.push_back( new SmallPlatform(sf::Vector2f(575,475)));
//    plats.push_back( new SmallPlatform(sf::Vector2f(275,400)));
//    plats.push_back( new SmallPlatform(sf::Vector2f(475,400)));
//    plats.push_back( new MidPlatform(sf::Vector2f(50,300)));
//    plats.push_back( new MidPlatform(sf::Vector2f(600,300)));
//    plats.push_back( new FullPlatform(sf::Vector2f(250,200)));
//
//    // Create a player and an enemy
//    Player player, enemy;
//
//    // Clock properties
//    sf::Clock clock;
//    float dt;
//
//    while (window.isOpen()) { // game loop
//
//        // Create the event object
//        sf::Event event;
//        dt = clock.restart().asSeconds();
//
//        // While there are events going on
//        while (window.pollEvent(event)) {
//
//            player.update(dt, event, window);
//        }
//        //Player movement
//        player.move(dt);
//
//        //Gravity Logic: If the player isn't on a platform, allow gravity, If a player is on a platform, allow jumping and stop gravity
//        player.allowGravity(plats);
//
//        window.clear();
//        bg.draw(window); // Drawing Background
//        for (auto it: plats) { // Drawing Platforms
//            it->draw(window);
//        }
//        // Creating new bullet
//        player.checkBullets(enemy, window);
//
//        player.draw(window);
//        enemy.draw(window);
//        window.display();
//    }
//
//    return EXIT_SUCCESS;
//}


//int main(int argc, const char * argv[])
//{
//    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//    sf::TcpSocket socket;
//    char connectionType;
//
//    std::cout << "server (s) or client (c)?\n";
//    std::cin >> connectionType;
//
//
//    if (connectionType == 's'){
//        sf::TcpListener listener;
//        listener.listen(2000);
//        listener.accept(socket);
//    }
//    else if (connectionType == 'c'){
//        socket.connect(ip, 2000);
//   }
//
//    sf::RectangleShape rect1, rect2;
//
//    rect1.setSize(sf::Vector2f(20, 20));
//    rect2.setSize(sf::Vector2f(20, 20));
//
//    rect1.setFillColor(sf::Color::Red);
//    rect2.setFillColor(sf::Color::Blue);
//
//    sf::RenderWindow window(sf::VideoMode(800, 600, 32), "Packets");
//    sf::Vector2f prevPosition, p2Position;
//
//    socket.setBlocking(false);
//
//    bool update = false;
//
//    while (window.isOpen())
//    {
//        sf::Event event;
//        //let you esc from program
//        while (window.pollEvent(event)){
//            if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
//                window.close();
//            }
//            else if (event.type == sf::Event::GainedFocus){
//                update = true;
//            }
//            else if (event.type == sf::Event::LostFocus) {
//                update = false;
//            }
//            //lost focus and gained focus were added so that you only control the window you're clicked
//            //on. Not both windows at the same time.
//        }
//
//        prevPosition = rect1.getPosition();
//
//
//        if (update){
//            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Right) {
//                rect1.move(1.0f, 0.0f);
//            }
//            else if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Left) {
//                rect1.move(-1.0f, 0.0f);
//            }
//            else if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Up) {
//                rect1.move(0.0f, -1.0f);
//            }
//            else if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::Down) {
//                rect1.move(0.0f, 1.0f);
//            }
//
//        }
//
//        //use uif, units, or floats. not ints when sending packets
//
//        sf::Packet packet;
//        if (prevPosition != rect1.getPosition()){
//            packet << rect1.getPosition().x << rect1.getPosition().y;
//            socket.send(packet);
//        }
//
//        socket.receive(packet);
//        if (packet >> p2Position.x >> p2Position.y){
//            rect2.setPosition(p2Position);
//        }
//
//
//
//        window.draw(rect1);
//        window.draw(rect2);
//
//        window.display();
//        window.clear();
//    }
//
//
//
//
//    return 0;
// }
//
//
