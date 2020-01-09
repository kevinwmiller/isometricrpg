#ifndef ANIMATIONSET_H
#define ANIMATIONSET_H

#include <vector>
#include "animation.h"

class AnimationSet
{
    public:
        AnimationSet();
        ~AnimationSet();

        //void loadAnimations(float, bool, int, sf::Vector2f, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&, std::string&);
        //void loadAnimations(float, bool, int, sf::Vector2f, sf::Image&, sf::Image&, sf::Image&, sf::Image&, sf::Image&, sf::Image&, sf::Image&, sf::Image&);
        void loadAnimations(float, bool, int, sf::Vector2f);


        void playAnimation();
        void pauseAnimation();
        sf::IntRect getCurrentFrame();
        bool isAnimFinished() const;

        void resetAllAnimations();
        void resetCurrentAnimation();
        void incrementFrame();
        void decrementFrame();

        sf::IntRect update(float);

        /*
            0 = North
            1 = East
            2 = South
            3 = West
            4 = NorthWest
            5 = NorthEast
            6 = SouthEast
            7 = SouthWest
        */
        void changeDirection(int);

    private:
        int frameTime;
        int direction;

        std::vector<Animation> animations;
};

#endif // ANIMATIONSET_H
