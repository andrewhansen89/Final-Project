
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <vector>
#include <thread>
#include "player.hpp"
#include "bullet.hpp"
#include "platform.hpp"
#include "background.hpp"
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

    sf::Texture background;
    background.loadFromFile(resourcePath() + "Background.png");
    sf::Sprite sBackground(background);
    
    // Initializes all platforms and sets their positions
    std::vector<Platform*> plats;
    plats.push_back( new SmallPlatform(sf::Vector2f(150,500)));
    plats.push_back( new SmallPlatform(sf::Vector2f(600,500)));
    plats.push_back( new SmallPlatform(sf::Vector2f(300,400)));
    plats.push_back( new SmallPlatform(sf::Vector2f(450,400)));
    plats.push_back( new MidPlatform(sf::Vector2f(50,300)));
    plats.push_back( new MidPlatform(sf::Vector2f(600,300)));
    plats.push_back( new FullPlatform(sf::Vector2f(250,200)));
    
    // Create a player and an enemy
    Player player, enemy;
    bool isFlipped = false;

    // Create vector to store bullets and set shooting property to false.
    std::vector<Bullet> bulletVec;
    bool isFiring = false;

    // Create Gravity's Properties
    const int groundHeight = 550;
    float gravitySpeed = 0;
    const int bulletSpeed = 5;
    bool isJumping = false;
    const float jumpHeight = 150.f;
    

    sf::Clock clock;
    float dt;
    float multiplier = 60.f;
    
    sf::Vector2f currentVelocity;
    sf::Vector2f direction;
    float maxVelocity = 10;
    float acceleration = 2.f;
    float drag = 0.5;
    

    while (window.isOpen()) { // game loop

        // Create the event object
        sf::Event event;

        // While there are events going on
        while (window.pollEvent(event)) {
            
            dt = clock.restart().asSeconds();
            direction = sf::Vector2f(0, 0);
            
            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) && isJumping == false) { // If the player presses W, jump.
                player.move(sf::Vector2f(0, -jumpHeight));
                isJumping = true;
                gravitySpeed = 4;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::D) { // If the player presses D then move right
                player.flipRight();
                isFlipped = false;
                player.setIsFlipped(isFlipped);
                direction.x = 1.f;
                if (currentVelocity.x < maxVelocity)
                    currentVelocity.x += acceleration * direction.x;
    
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::A) { // If the player presses A, move left
                player.flipLeft();
                isFlipped = true;
                player.setIsFlipped(isFlipped);
                direction.x = -1.f;
                if (currentVelocity.x > -maxVelocity)
                    currentVelocity.x += acceleration * direction.x;
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                isFiring = true;
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R ) {
                if (enemy.getIsDead())
                    enemy.respawn();
                else if (player.getIsDead())
                    player.respawn();
            }

            // If the window is closed, stop running the game
            if (event.type == sf::Event::Closed)
                window.close();
            // If the player presses escape, stop running the game
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
            // If the player releases a key, then stop the jumping.
            
            //Drag for X
            if(currentVelocity.x > 0.f) {
                currentVelocity.x -= drag * dt * multiplier;
                if (currentVelocity.x < 0.f) {
                    currentVelocity.x = 0.f;
                }
            }
            else if (currentVelocity.x < 0.f) {
                currentVelocity.x += drag * dt * multiplier;
                if (currentVelocity.x > 0.f) {
                    currentVelocity.x = 0.f;
                }
            }
            // Drag for Y
            if(currentVelocity.y > 0.f) {
                currentVelocity.y -= drag * dt * multiplier;
                if (currentVelocity.y < 0.f) {
                    currentVelocity.y = 0.f;
                }
            }
            else if (currentVelocity.y < 0.f) {
                currentVelocity.y += drag * dt * multiplier;
                if (currentVelocity.y > 0.f) {
                    currentVelocity.y = 0.f;
                }
            }

            player.move(sf::Vector2f(currentVelocity.x * dt * multiplier, 0));
        }
        
        //Gravity Logic: If the player isn't on a platform, allow gravity, If a player is on a platform, allow jumping and stop gravity
        if (player.checkFeet(plats) == false && player.getY() < groundHeight){
            gravitySpeed = 4;
            player.move(sf::Vector2f(0, gravitySpeed));
            isJumping = false;
        }
        else {
            isJumping = false;
            gravitySpeed = 0;
        }

        int counter = 0; // Bullet Logic
        for (int i = 0; i < bulletVec.size(); i++) {
            if (enemy.checkColl(bulletVec.at(i))) {
                bulletVec.erase(bulletVec.begin() + i);
            }
        }

        window.clear();

        // Drawing Background
        window.draw(sBackground);
        // Drawing Platforms
        for (auto it: plats) {
            it->draw(window);
        }
      
        if (isFiring == true) {
            Bullet newBullet(sf::Vector2f(player.getX(), player.getY() + 10), isFlipped);
            bulletVec.push_back(newBullet);
            isFiring = false;
        }

        for (int i = 0; i < bulletVec.size(); i++) {
            bulletVec[i].draw(window);
            bulletVec[i].update(bulletSpeed);
        }

        for (int i = 0; i < bulletVec.size(); i++) {
            if(enemy.checkColl(bulletVec[i]))
                enemy.setIsDead(true);
        }
        
        player.draw(window);
        enemy.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}
        
     


//#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
//#include <string>
//#include <iostream>
//
//int main(int argc, const char * argv[])
//{
//    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
//    sf::TcpSocket socket;
//    char connectionType;
//    //char mode;
//    //char buffer[2000];
//    //std::size_t received;
//    //std::string text = "Connected to: ";
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
//#include <SFML/Audio.hpp>
//#include <SFML/Graphics.hpp>
//#include <iostream>
//#include <ctime>
//#include <vector>
//#include <thread>
//#include "player.hpp"
//#include "bullet.hpp"
//#include "platform.hpp"
//#include "background.hpp"
//#include "ResourcePath.hpp"
//
//// window dimensions
//int WIDTH = 800;
//int HEIGHT = 600;
//
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
//    sf::Texture background;
//    background.loadFromFile(resourcePath() + "Background.png");
//    sf::Sprite sBackground(background);
//
//    // Initializes all platforms and sets their positions
//    std::vector<Platform*> plats;
//    plats.push_back( new SmallPlatform(sf::Vector2f(150,500)));
//    plats.push_back( new SmallPlatform(sf::Vector2f(600,500)));
//    plats.push_back( new SmallPlatform(sf::Vector2f(300,400)));
//    plats.push_back( new SmallPlatform(sf::Vector2f(450,400)));
//    plats.push_back( new MidPlatform(sf::Vector2f(50,300)));
//    plats.push_back( new MidPlatform(sf::Vector2f(600,300)));
//    plats.push_back( new FullPlatform(sf::Vector2f(250,200)));
//
//    // Create a player and an enemy
//    Player player, enemy;
//    bool isFlipped = false;
//
//    // Create vector to store bullets and set shooting property to false.
//    std::vector<Bullet> bulletVec;
//    bool isFiring = false;
//
//    // Create Gravity's Properties
//    const int groundHeight = 550;
//    float gravitySpeed = 0;
//    const int bulletSpeed = 5;
//    bool isJumping = false;
//    const float jumpHeight = 150.f;
//
//    sf::Clock clock;
//    float dt;
//    float multiplier = 60.f;
//
//
//    while (window.isOpen()) { // game loop
//        // Player will move at certain speed
//        const float moveSpeed = 3.f;
//
//        // Create the event object
//        sf::Event event;
//
//        // While there are events going on
//        while (window.pollEvent(event)) {
//
//            dt = clock.restart().asSeconds();
//
//            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) && isJumping == false) { // If the player presses W, jump.
//                player.move(sf::Vector2f(0, -jumpHeight));
//                isJumping = true;
//                gravitySpeed = 4;
//            }
//
//            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::D) { // If the player presses D then move right
//                player.flipRight();
//                isFlipped = false;
//                player.setIsFlipped(isFlipped);
//                player.move(sf::Vector2f(moveSpeed * dt * multiplier, 0));
//
//            }
//
//            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::A) { // If the player presses A, move left
//                player.flipLeft();
//                isFlipped = true;
//                player.setIsFlipped(isFlipped);
//                player.move(sf::Vector2f(-moveSpeed * dt * multiplier, 0));
//            }
//
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
//                isFiring = true;
//            }
//
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R ) {
//                if (enemy.getIsDead())
//                    enemy.respawn();
//                else if (player.getIsDead())
//                    player.respawn();
//            }
//            if (event.type == sf::Event::Closed)
//                window.close();
//            // If the player presses escape, stop running the game
//            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
//                    window.close();
//            // If the player releases a key, then stop the jumping.
//
//        }
//
//        //Gravity Logic: If the player isn't on a platform, allow gravity, If a player is on a platform, allow jumping and stop gravity
//        if (player.checkFeet(plats) == false && player.getY() < groundHeight){
//            gravitySpeed = 4;
//            player.move(sf::Vector2f(0, gravitySpeed));
//            isJumping = false;
//        }
//        else {
//            isJumping = false;
//            gravitySpeed = 0;
//        }
//
//         // Bullet Logic
//        for (int i = 0; i < bulletVec.size(); i++) {
//            if (enemy.checkColl(bulletVec.at(i))) {
//                bulletVec.erase(bulletVec.begin() + i);
//            }
//        }
//
//        window.clear();
//
//        // Drawing Background
//        window.draw(sBackground);
//        // Drawing Platforms
//        for (auto it: plats) {
//            it->draw(window);
//        }
//
//        if (isFiring == true) {
//            Bullet newBullet(sf::Vector2f(player.getX(), player.getY() + 10), isFlipped);
//            bulletVec.push_back(newBullet);
//            isFiring = false;
//        }
//
//        for (int i = 0; i < bulletVec.size(); i++) {
//            bulletVec[i].draw(window);
//            bulletVec[i].update(bulletSpeed);
//        }
//
//        for (int i = 0; i < bulletVec.size(); i++) {
//            if(enemy.checkColl(bulletVec[i]))
//                enemy.setIsDead(true);
//        }
//
//        player.draw(window);
//        enemy.draw(window);
//        window.display();
//    }
//
//    return EXIT_SUCCESS;
//}
