#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation();
        Animation(float, bool, int, sf::Vector2f);
        ~Animation();

        void createAnimation(float, bool, int, sf::Vector2f);
        void addFrame(sf::IntRect);
        void previousFrame();
        void nextFrame();
        sf::IntRect update(float);
        void play();
        void pause();
        sf::IntRect getFrame();
        bool isFinished() const;

        void reset();

    private:

        int currentFrame;
        int totalFrames;
        bool paused;
        bool looped;
        bool finished;

        float frameTime;
        float currentTime;

        //std::vector<sf::Texture> frames;
        std::vector<sf::IntRect> frames;
        //sf::Texture animation;

};

#endif // ANIMATION_H
