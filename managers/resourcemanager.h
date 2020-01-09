#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>


class ResourceManager
{
    public:
        ResourceManager();
        ~ResourceManager();

        void loadFonts(); // Loads font files
        void setupWindow(std::string); // Calls createWindow based on configuration
        void createWindow(std::string); // Fullscreen
        void createWindow(std::string, int, int); // Windowed

        sf::VideoMode vidMode;
        sf::RenderWindow window;

        sf::Font fontNormal, fontBold, fontItalic, fontEvanes;
        const std::string version = "Version 0.0.9";
    protected:

        static const std::string configFilename;
};

#endif // RESOURCEMANAGER_H
