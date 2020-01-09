#include "animationset.h"
#include <iostream>
AnimationSet::AnimationSet()
{
    direction = 0;
    animations.resize(8);
}

AnimationSet::~AnimationSet()
{
   // std::cout << "AnimationSet destructor called\n";
}

/*void AnimationSet::loadAnimations(float fTime, bool looped, int frames, sf::Vector2f frameSize, std::string& nFile, std::string& eFile, std::string& sFile, std::string& wFile, std::string& nwFile, std::string& neFile, std::string& seFile, std::string& swFile)
{

    if (!nImg.loadFromFile(nFile))
        exit(100);
    else
        animations[0].createAnimation(fTime, looped, frames, frameSize, nImg);

    if (!eImg.loadFromFile(eFile))
        exit(101);
    else
        animations[1].createAnimation(fTime, looped, frames, frameSize, eImg);

    if (!sImg.loadFromFile(sFile))
        exit(102);
    else
        animations[2].createAnimation(fTime, looped, frames, frameSize, sImg);

    if (!wImg.loadFromFile(wFile))
        exit(103);
    else
        animations[3].createAnimation(fTime, looped, frames, frameSize, wImg);

    if (!nwImg.loadFromFile(nwFile))
        exit(104);
    else
        animations[4].createAnimation(fTime, looped, frames, frameSize, nwImg);

    if (!neImg.loadFromFile(neFile))
        exit(105);
    else
        animations[5].createAnimation(fTime, looped, frames, frameSize, neImg);

    if (!seImg.loadFromFile(seFile))
        exit(106);
    else
        animations[6].createAnimation(fTime, looped, frames, frameSize, seImg);

    if (!swImg.loadFromFile(swFile))
        exit(107);
    else
        animations[7].createAnimation(fTime, looped, frames, frameSize, swImg);

}*/

//void AnimationSet::loadAnimations(float fTime, bool looped, int frames, sf::Vector2f frameSize, sf::Image& nImg, sf::Image& eImg, sf::Image& sImg, sf::Image& wImg, sf::Image& nwImg, sf::Image& neImg, sf::Image& seImg, sf::Image& swImg)
void AnimationSet::loadAnimations(float fTime, bool looped, int frames, sf::Vector2f frameSize)
{
    animations[0].createAnimation(fTime, looped, frames, frameSize);

    animations[1].createAnimation(fTime, looped, frames, frameSize);

    animations[2].createAnimation(fTime, looped, frames, frameSize);

    animations[3].createAnimation(fTime, looped, frames, frameSize);

    animations[4].createAnimation(fTime, looped, frames, frameSize);

    animations[5].createAnimation(fTime, looped, frames, frameSize);

    animations[6].createAnimation(fTime, looped, frames, frameSize);

    animations[7].createAnimation(fTime, looped, frames, frameSize);
}

void AnimationSet::playAnimation()
{
    animations[direction].play();
}

void AnimationSet::pauseAnimation()
{
    animations[direction].pause();
}

sf::IntRect AnimationSet::getCurrentFrame()
{
    return animations[direction].getFrame();
}

void AnimationSet::resetAllAnimations()
{
    for(int i = 0; i < animations.size(); i++)
        animations[i].reset();
}

void AnimationSet::resetCurrentAnimation()
{
    animations[direction].reset();
}

void AnimationSet::incrementFrame()
{
    animations[direction].nextFrame();
}

void AnimationSet::decrementFrame()
{
    animations[direction].previousFrame();
}

bool AnimationSet::isAnimFinished() const
{
    return animations[direction].isFinished();
}

sf::IntRect AnimationSet::update(float deltaTime)
{
    //std::cout << "Direction: " <<direction <<std::endl;
    return animations[direction].update(deltaTime);
}

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
void AnimationSet::changeDirection(int dir)
{
    resetCurrentAnimation();
    if(dir >= 0 && dir <= 7)
        direction = dir;
}
