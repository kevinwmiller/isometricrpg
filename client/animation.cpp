#include "animation.h"
#include <iostream>
Animation::Animation()
{
    currentFrame = 0;
    totalFrames = 0;
    currentTime = 0;
    frameTime = 0;
    paused = false;
    looped = false;
    finished = false;
}

Animation::Animation(float fTime, bool isLooped, int totFrames, sf::Vector2f frameSize)
{
    currentFrame = 0;
    totalFrames = 0;
    currentTime = 0;
    frameTime = 0;
    paused = false;
    looped = false;
    finished = false;
    createAnimation(fTime, isLooped, totFrames, frameSize);
}

Animation::~Animation()
{
   // std::cout << "Animation destructor called\n";
}

void Animation::createAnimation(float fTime, bool isLooped, int totFrames, sf::Vector2f frameSize)
{
    totalFrames = totFrames;
    frames.resize(totalFrames);

    frameTime = fTime;
    looped = isLooped;
//    animationFrames.loadFromImage(animationSet);

    for(int i = 0; i < totalFrames; i++)
    {
       // std::cout << "Loading Frame " << i << std::endl;
        //frames[i].loadFromImage(animationSet, sf::IntRect(i * frameSize.x, 0, frameSize.x, frameSize.y));
        frames[i].left = i * frameSize.x;
        frames[i].top = 0;
        frames[i].width = frameSize.x;
        frames[i].height = frameSize.y;
    }
}

void Animation::addFrame(sf::IntRect frame)
{
    frames.push_back(frame);
}

void Animation::previousFrame()
{
    if(currentFrame > 0)
        currentFrame--;
    else
        currentFrame = totalFrames - 1;
}

void Animation::nextFrame()
{

    if(currentFrame < totalFrames - 1)
        currentFrame++;
    else
    {
        currentFrame = 0;
        finished = true;
    }
         //std::cout << "Total Frames: " << totalFrames <<std::endl;
}

sf::IntRect Animation::update(float deltaTime)
{
    //std::cout << "Current Frame: " << currentFrame <<std::endl;
    if(!paused)
    {
        currentTime = currentTime + deltaTime;
        //std::cout << "Delta Time: " << deltaTime <<std::endl;

       // std::cout << "Current Time: " << currentTime <<std::endl;
       // std::cout << "frameTime: " <<frameTime <<std::endl;
        if(currentTime >= frameTime)
        {
            nextFrame();
            currentTime = 0;
        }

        if(currentFrame == totalFrames - 1 && !looped)
        {
            paused = true;
            currentFrame = 0;
        }
    }
    //std::cout << "Current Frame: " << currentFrame <<std::endl;
    return frames[currentFrame];
}

void Animation::play()
{
    if(paused)
    {
        currentTime = 0;
        paused = false;
    }
}

void Animation::pause()
{
    paused = true;
}


sf::IntRect Animation::getFrame()
{
    return frames[currentFrame];
}

bool Animation::isFinished() const
{
    return finished;
}

void Animation::reset()
{
   // currentFrame = 0;
    finished = false;
}
