#include "animationcomponent.h"
#include <iostream>

std::map<const std::string, Animation*> AnimationComponent::animations;
std::map<const std::string, sf::Texture*> AnimationComponent::animationTextures;
std::map<const std::string, AnimationSet*> AnimationComponent::animationSets;
std::map<const std::string, std::vector<sf::Texture*>> AnimationComponent::animationSetTextures;
std::vector<Animation> AnimationComponent::animationStorage;
std::vector<AnimationSet> AnimationComponent::animationSetStorage;
std::vector<std::vector<sf::Texture>> AnimationComponent::textureStorage;

int AnimationComponent::totalAnimations = 0;
int AnimationComponent::totalAnimationSets = 0;

AnimationComponent::AnimationComponent()
{
    boundingBox = sf::FloatRect(0, 0, 0, 0);
    spriteBoxOffset = sf::Vector2f(0, 0);
}

AnimationComponent::~AnimationComponent()
{
    //dtor
}

sf::FloatRect AnimationComponent::getBoundingBox() const
{
    return boundingBox;
}

void AnimationComponent::setSpriteBoundsOffset(const sf::Vector2f& offset)
{
    spriteBoxOffset = offset;
}

void AnimationComponent::setPosition(const sf::Vector2f& newPos)
{
    sprite.setPosition(newPos.x - spriteBoxOffset.x, newPos.y - spriteBoxOffset.y);
}

sf::Vector2f AnimationComponent::getSpritePosition() const
{
    return sprite.getPosition();
}

void AnimationComponent::setSpriteColor(const sf::Color& sprColor)
{
    sprite.setColor(sprColor);
}


///First parameter: Name used to reference the animation. Second Parameter: File to load the animation's texture from
void AnimationComponent::addAnimation(const std::string& animationName, const std::string& animTextureFile, float frameTime, bool looped, int totalFrames, sf::Vector2f frameSize)
{
    if(animations.find(animationName) == animations.end())
    {
        std::string animName = animationName;

        //Resize the texture vector so we can hold the added textures
        textureStorage.resize(totalAnimations + 1);
        textureStorage[totalAnimations].resize(1);

        animationStorage.resize(totalAnimations + 1);

        std::cout << "Loading animation texture: " << animTextureFile << std::endl;

        if(!textureStorage[totalAnimations][0].loadFromFile(animTextureFile))
            exit(100);
        else
            std::cout << "Finished loading " << animTextureFile << std::endl;

        animationStorage[totalAnimations].createAnimation(frameTime, looped, totalFrames, frameSize);
        animationTextures[animName] = &textureStorage[totalAnimations][0];
        animations[animName] =  &animationStorage[totalAnimations];

        totalAnimations++;
    }
    else
    {
        std::cout << "The animation " << animationName << " already exists\n";
    }


}

void AnimationComponent::addAnimationSet(const std::string& setName, std::vector<std::string> animTextureFiles, float frameTime, bool looped, int totalFrames, sf::Vector2f frameSize)
{
    //If there is the correct amount of texture files and the animation name is not already in use
    if(animTextureFiles.size() == ANIMS_PER_SET && animationSets.find(setName) == animationSets.end())
    {
        std::vector<sf::Texture*> builder;
        //Add another row to the table of textures
        textureStorage.resize(totalAnimationSets + 1);
        //Resize the new row to fit all textures in the animation set
        textureStorage[totalAnimationSets].resize(ANIMS_PER_SET);


        std::cout << "Total textures " << animTextureFiles.size() << std::endl;

        for(int i = 0; i < animTextureFiles.size(); i++)
            std::cout << animTextureFiles[i] << std::endl;
        animationSetStorage.resize(totalAnimationSets + 1);

        //Load the animation set textures into the empty row of the table
        for(int i = 0; i < ANIMS_PER_SET; i++)
        {

            if(!textureStorage[totalAnimationSets][i].loadFromFile(animTextureFiles[i]))
                exit(100 + i);
            else
                std::cout << "Finished loading \n" << animTextureFiles[i] << std::endl;

            builder.push_back(&textureStorage[totalAnimationSets][i]);
     //       std::cout << "Finished Adding to vector \n" << animTextureFiles[i] << std::endl;

        }


        animationSetStorage[totalAnimationSets].loadAnimations(frameTime, looped, totalFrames, frameSize);
        std::cout << "Adding to storage " <<  std::endl;;
        animationSets[setName] = &animationSetStorage[totalAnimationSets];
        animationSetTextures[setName] = builder;
        totalAnimationSets++;
    }
    else
    {
        std::cout << "Could not add animation. Not " << ANIMS_PER_SET << " animation textures or the animation name is already in use.\n";
    }
}

void AnimationComponent::changeAnimation(const std::string& animationName)
{
    currentTexture = animationTextures[animationName];
    currentAnimation = animations[animationName];

    sprite.setTexture(*currentTexture);
}

void AnimationComponent::changeAnimationSet(const std::string& animationName, int direction)
{
    if(direction < ANIMS_PER_SET)
    {
        //Change the current animation set only if the desired animation exists
        if((currentAnimationSet == animationSets[animationName] && currentOrientation == direction) || animationSets.find(animationName) == animationSets.end() )
        {
            //std::cout << "Not changing texture\n";
        }
        else
        {
            currentOrientation = direction;
            std::cout << "Changing animation to " << animationName << std::endl;
            std::cout << "Current Direction " << direction << std::endl;

            currentTexture = animationSetTextures[animationName][direction];
            currentAnimationSet = animationSets[animationName];

            sprite.setTexture(*currentTexture);
        }
    }
}

void AnimationComponent::resetAllAnimations()
{
    for(std::map<const std::string, Animation*>::iterator iter = animations.begin(); iter != animations.end(); iter++)
        iter->second->reset();
}

void AnimationComponent::resetCurrentAnimation()
{
    currentAnimation->reset();
}

bool AnimationComponent::isCurrentAnimationFinished()
{
    return currentAnimation->isFinished();
}

bool AnimationComponent::isCurrentAnimationSetFinished()
{
    return currentAnimationSet->isAnimFinished();
}

void AnimationComponent::updateCurrentAnimation(float elapsedTime, const sf::Vector2f& spritePos)
{
    sprite.setTexture(*currentTexture);
    sprite.setPosition(spritePos.x - spriteBoxOffset.x, spritePos.y - spriteBoxOffset.y);
    sf::IntRect frame = currentAnimation->update(elapsedTime);

    sprite.setTextureRect(frame);
}

void AnimationComponent::updateCurrentAnimationSet(float elapsedTime, const sf::Vector2f& spritePos)
{
    sprite.setTexture(*currentTexture);
    sprite.setPosition(spritePos.x - spriteBoxOffset.x, spritePos.y - spriteBoxOffset.y);
    sf::IntRect frame = currentAnimationSet->update(elapsedTime);

    sprite.setTextureRect(frame);
}

void AnimationComponent::drawCurrentFrame(sf::RenderWindow& window)
{
    window.draw(sprite);
}
