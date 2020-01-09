#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <vector>
#include <SFML/Graphics.hpp>

class ImageManager
{
    public:
        ImageManager();
        ~ImageManager();

        void loadImages();
        void loadAnimations();

    private:
        std::vector<sf::Image> pl_unarmedWalking;
        std::vector<sf::Image> pl_unarmedStanding;


};

#endif // IMAGEMANAGER_H
