#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main()
{
    // Create the window
    sf::RenderWindow window(sf::VideoMode(600, 800), "Goku Animation");

    sf::Music music;
    if(!music.openFromFile("./assets/music/sound.wav")) {
        return EXIT_FAILURE;
    }

    // Set the volume of the sound
    music.setVolume(50);
    music.play();

    // Load the sprite images
    sf::Texture texture1, texture2, texture3;
    if (!texture1.loadFromFile("./assets/sprites/goku1.png") ||
        !texture2.loadFromFile("./assets/sprites/goku2.png") ||
        !texture3.loadFromFile("./assets/sprites/goku3.png"))
    {
        // Handle the error if the images failed to load
        return EXIT_FAILURE;
    }

    // Create the sprite
    float scaleFactor = 4.0;
    sf::Sprite sprite;
    sprite.setScale(scaleFactor, scaleFactor);
    sprite.setTexture(texture1);

    // Set the initial position of the sprite
    sprite.setPosition(200, 200);

    // Set the animation frame duration
    sf::Time frameDuration = sf::seconds(0.08f);

    // Create a clock to track time
    sf::Clock clock;

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get the elapsed time
        sf::Time elapsed = clock.getElapsedTime();

        // Check if it's time to switch the sprite image
        if (elapsed >= frameDuration)
        {
            // Reset the clock
            clock.restart();

            // Switch to the next sprite image
            if (sprite.getTexture() == &texture1)
                sprite.setTexture(texture2);
            else if (sprite.getTexture() == &texture2)
                sprite.setTexture(texture3);
            else
                sprite.setTexture(texture1);
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the contents of the window
        window.display();
    }

    return 0;
}

