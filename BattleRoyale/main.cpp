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

    // Create a player and an enemy
    Player player, player2;

    // Clock properties
    sf::Clock clock;
    float dt;


    sf::Vector2f prevPos, player2Pos;
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
            it->draw(window);
        }

        // Creating new bullet
        player.checkBullets(player2, window);

        player.draw(window);
        player2.draw(window);

        window.display();
        window.clear();
    }

    return EXIT_SUCCESS;
}

