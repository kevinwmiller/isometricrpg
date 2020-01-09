
#include "resourcemanager.h"
#include <iostream>
#include <string>

using namespace std;

const string ResourceManager::configFilename = "Options.txt";


ResourceManager::ResourceManager()
{

}



ResourceManager::~ResourceManager()
{
    window.close();
}


void ResourceManager::loadFonts()
{
    if (!fontNormal.loadFromFile("resources/fonts/verdana.ttf"))
        exit(301);
    if (!fontBold.loadFromFile("resources/fonts/verdanab.ttf"))
        exit(302);
    if (!fontItalic.loadFromFile("resources/fonts/verdanai.ttf"))
        exit(303);
    if (!fontEvanes.loadFromFile("resources/fonts/evanescent.ttf"))
        exit(304);
}

void ResourceManager::setupWindow(std::string windowTitle)
{
    int windowWidth = 1366;
    int windowHeight = 768;

    if (windowWidth > 0 && windowHeight > 0)
        createWindow(windowTitle, windowWidth, windowHeight);
    else
        createWindow(windowTitle);

    window.setVerticalSyncEnabled(true); // Set vsync from setting
}

void ResourceManager::createWindow(string windowTitle)
{
    // Create a window in fullscreen at the current resolution
    vidMode = sf::VideoMode::getDesktopMode();

    // Only use a resolution 1080p or less - this is temporary until we can figure out how to handle multiple monitors
    if (vidMode.width > 1920 || vidMode.height > 1200)
    {
        auto videoModes = sf::VideoMode::getFullscreenModes();
        for (auto& vM: videoModes)
        {
            cout << vM.width << " x " << vM.height << "? ";
            if (vM.width <= 1920 && vM.height <= 1200)
            {
                vidMode = vM;
                cout << "Using this!\n";
                break;
            }
            else
                cout << "Too big!\n";
        }
    }

    window.create(vidMode, windowTitle, sf::Style::Fullscreen);
}

void ResourceManager::createWindow(string windowTitle, int windowWidth, int windowHeight)
{
    // Create a normal window
    vidMode = sf::VideoMode(windowWidth, windowHeight);
    window.create(vidMode, windowTitle, sf::Style::Close);
}
