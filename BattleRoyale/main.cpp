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

 //window dimensions
int WIDTH = 800;
int HEIGHT = 600;

int main(int, char const**) {

    // Initalize time
    srand(time(0));

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
       listener.listen(2005); // Value of 2000 is arbitrary. anything under 1024 is considered a private port and can not be used
       listener.accept(socket); // If a connection is found at port 2000, accept the connection and store it in the socket
    }
    else {
        socket.connect(ip, 2005);
        std::cout << "connected";
    }

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

<<<<<<< HEAD
    // Create a player and an enemy
<<<<<<< HEAD
    Player player, player2;
=======
    // Create Gravity's Properties
    const int groundHeight = 550;
    float gravitySpeed = 0;
    const int bulletSpeed = 5;
    bool isJumping = false;
    const float jumpHeight = 150.f;
    
>>>>>>> parent of a6af7a6... Updated project

    // Clock properties
    sf::Clock clock;
    float dt;
<<<<<<< HEAD


    sf::Vector2f prevPos, player2Pos;
    socket.setBlocking(false);
    bool update = false;
=======
    float multiplier = 60.f;
    
    sf::Vector2f currentVelocity;
    sf::Vector2f direction;
    float maxVelocity = 10;
    float acceleration = 2.f;
    float drag = 0.5;
    
>>>>>>> parent of a6af7a6... Updated project
=======
    Player player, enemy;
    bool isFlipped = false;

    // Create vector to store bullets and set shooting property to false.
    std::vector<Bullet> bulletVec;
    bool isFiring = false;
    
    // Create Gravity's Properties
    const int groundHeight = 550;
    float gravitySpeed = 0;
    const int bulletSpeed = 6;
    bool isJumping = false;
    const float jumpHeight = 150.f;
    
    // Clock properties
    sf::Clock clock;
    float dt;
    float multiplier = 60.f;
    
    // Movement physics
    sf::Vector2f currentVelocity;
    sf::Vector2f direction;
    float maxVelocity = 8.f;
    float acceleration = 2.f;
    float drag = 0.5;

>>>>>>> parent of f22fa5c... finished consolidating code

    while (window.isOpen()) { // game loop

        // Create the event object
        sf::Event event;
<<<<<<< HEAD
<<<<<<< HEAD
        dt = clock.restart().asSeconds();
<<<<<<< HEAD
=======
=======
>>>>>>> parent of a6af7a6... Updated project

=======
        bool isValid = false;
        
>>>>>>> parent of f22fa5c... finished consolidating code
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
>>>>>>> parent of a6af7a6... Updated project

<<<<<<< HEAD
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

<<<<<<< HEAD
            player.update(dt, event, window);
=======
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
=======
            direction = sf::Vector2f(0, 0);

            if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W) && isJumping == false) { // If the player presses W, jump.
                isJumping = true;
                gravitySpeed = 4;
                direction.y = -1.f;
                currentVelocity.y = -jumpHeight;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::D) { // If the player presses D then move right
                player.flipRight();
                isFlipped = false;
                player.setIsFlipped(isFlipped);
                direction.x = 1.f;
                if (currentVelocity.x < maxVelocity)
                    currentVelocity.x += acceleration * direction.x * dt * multiplier;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code ==  sf::Keyboard::A) { // If the player presses A, move left
                player.flipLeft();
                isFlipped = true;
                player.setIsFlipped(isFlipped);
                direction.x = -1.f;
                if (currentVelocity.x > -maxVelocity)
                    currentVelocity.x += acceleration * direction.x * dt * multiplier;
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
            if (event.type == sf::Event::Closed) // If the window is closed, stop running the game
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) // If the player presses escape, stop running the game
                window.close();
            
            // Drag physics
            if(currentVelocity.x > 0.f) {
                currentVelocity.x -= drag * dt * multiplier;
                if (currentVelocity.x < 0.f)
                    currentVelocity.x = 0.f;
            }
            else if (currentVelocity.x < 0.f) {
                currentVelocity.x += drag * dt * multiplier;
                if (currentVelocity.x > 0.f)
                    currentVelocity.x = 0.f;
            }
            if(currentVelocity.y > 0.f) {
                currentVelocity.y -= drag * dt * multiplier;
                if (currentVelocity.y < 0.f)
                    currentVelocity.y = 0.f;
            }
            else if (currentVelocity.y < 0.f) {
                currentVelocity.y += drag * dt * multiplier;
                if (currentVelocity.y > 0.f)
                    currentVelocity.y = 0.f;
            }
        }
        //Player movement
        player.move(sf::Vector2f(currentVelocity.x * dt * multiplier, currentVelocity.y));
        currentVelocity.y = 0.f;
>>>>>>> parent of f22fa5c... finished consolidating code

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
<<<<<<< HEAD
>>>>>>> parent of a6af7a6... Updated project
        }

        prevPos = player.getPos();

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

        if (prevPos.x != player.getLeft() || prevPos.y != player.getTop()){
            // Store position in packet
            packet << player.getLeft() << player.getTop();
            // Send packet to the socket
            socket.send(packet);
            std::cout << "packet sent";
        }

        socket.receive(packet);
        float x,y;
        // Store information in  packet in the enemy player class

        if (packet >> y >> x){
            std::cout << "packet recieved" << std::endl;
            player2.setPos(sf::Vector2f(x,y));
        }

        bg.draw(window); // Drawing Background
        for (auto it : plats) { // Drawing Platforms
=======
        }

        int counter = 0; // Bullet Logic
        for (int i = 0; i < bulletVec.size(); i++) {
            if (enemy.checkColl(bulletVec.at(i))) {
                bulletVec.erase(bulletVec.begin() + i);
            }
        }

        window.clear();

        // Drawing Background
        bg.draw(window);
        // Drawing Platforms
        for (auto it: plats) {
>>>>>>> parent of f22fa5c... finished consolidating code
            it->draw(window);
        }

        // Creating new bullet
<<<<<<< HEAD
        player.checkBullets(player2, window);
=======
        if (isFiring == true) {
            Bullet newBullet(sf::Vector2f(player.getX(), player.getY() + 10), isFlipped);
            bulletVec.push_back(newBullet);
            isFiring = false;
        }
        // Looping through the bullet vector and updating all of them
        for (int i = 0; i < bulletVec.size(); i++) {
            bulletVec[i].draw(window);
            bulletVec[i].update(bulletSpeed);
        }
        // Checking for collisions
        for (int i = 0; i < bulletVec.size(); i++) {
            if(enemy.checkColl(bulletVec[i]))
                player.setIsDead(true);
        }
>>>>>>> parent of f22fa5c... finished consolidating code

        player.draw(window);
        player2.draw(window);

        window.display();
        window.clear();
    }

    return EXIT_SUCCESS;
}

