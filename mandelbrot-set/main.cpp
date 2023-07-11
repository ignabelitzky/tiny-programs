#include <SFML/Graphics.hpp>
#include <complex>
#include "params.h"

float map(float value, float fromMin, float fromMax, float toMin, float toMax)
{
    float fromRange = fromMax - fromMin;
    float toRange = toMax - toMin;
    float normalizedValue = (value - fromMin) / fromRange;
    return (normalizedValue * toRange) + toMin;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Mandelbrot Set");
    window.setVerticalSyncEnabled(true);

    sf::View view(window.getDefaultView());
    float zoomLevel = 1.0f;
    const float zoomFactor = 1.1f;
    const float zoomMax = 10.0f;
    const float zoomMin = 0.1f;

    sf::Vector2f panOffset;
    bool isPanning = false;
    sf::Vector2i lastMousePos;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::MouseWheelScrolled) {
                if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if(event.mouseWheelScroll.delta > 0) {
                        // Zoom in
                        if(zoomLevel < zoomMax) {
                            zoomLevel *= zoomFactor;
                            view.zoom(1.0f / zoomFactor);
                        }
                    } else if (event.mouseWheelScroll.delta < 0) {
                        if(zoomLevel > zoomMin) {
                            zoomLevel /= zoomFactor;
                            view.zoom(zoomFactor);
                        }
                    }
                }
            } else if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    isPanning = true;
                    lastMousePos = sf::Mouse::getPosition(window);
                }
            } else if(event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    // Stop panning
                    isPanning = false;
                }
            }
            else if(event.type == sf::Event::MouseMoved) {
                if(isPanning) {
                    // Calculate the panning offset
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    panOffset = sf::Vector2f(lastMousePos - mousePos);
                    lastMousePos = mousePos;

                    // Update the view position
                    view.move(panOffset);
                }
            }
        }
        window.clear();
        window.setView(view);
        for(int x = 0; x < windowWidth; ++x) {
            for(int y = 0; y < windowHeight; ++y) {
                std::complex<float> z(map(x, 0, windowWidth, -2, 2), map(y, 0, windowHeight, -2, 2));
                std::complex<float> originalZ = z;
                float n = 0;
                while(n < maxIterations) {
                    float real = z.real() * z.real() - z.imag() * z.imag();
                    float imag = 2 * z.real() * z.imag();
                    z.real(real + originalZ.real());
                    z.imag(imag + originalZ.imag());
                    if(std::abs(z.real() + z.imag()) > 500) {
                        break;
                    }
                    ++n;
                }

                float bright = map(n, 0, maxIterations, 0, 255);
                if(n == maxIterations) {
                    bright = 0;
                }

                sf::RectangleShape pixel(sf::Vector2f(1, 1));
                pixel.setPosition(x, y);
                pixel.setFillColor(sf::Color(bright, bright, bright, 255));
                window.draw(pixel);
            }
        }
        window.display();
    }
    return 0;
}
