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
    textureStorage.clear();
    animationSets.clear();
    animationSetStorage.clear();
    animations.clear();
    animationStorage.clear();
    currentOrientation = 0;
    totalAnimations = 0;
    totalAnimationSets= 0;
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

void AnimationComponent::addAnimationSet(const std::string& setName, std::vector<std::string> animTextureFiles, float frameTime, bool looped, int totalFrames, sf::Vector2f frameSize)
{

    //Total textures for a single animation set
    if( animTextureFiles.size() == ANIMS_PER_SET && animationSets.find(setName) == animationSets.end() )
    {
        std::vector<sf::Texture*> builder;
        //Add another row to the table of textures
        //std::cout << textureStorage.size() << "\n\n\n";
        textureStorage.resize(totalAnimationSets + 1);
        //Resize the new row to fit all textures in the animation set
        textureStorage[totalAnimationSets].resize(ANIMS_PER_SET);


        std::cout << "Total textures " << animTextureFiles.size() << std::endl;

       // for( unsigned int i = 0; i < animTextureFiles.size(); i++ )
       //     std::cout << animTextureFiles[i] << std::endl;
        animationSetStorage.resize(totalAnimationSets + 1);
    //    std::cout << "Row " << totalAnimationSets;
        //Load the animation set textures into the empty row of the table
        for(int i = 0; i < ANIMS_PER_SET; ++i)
        {


        //    std::cout << "  Col " << i << ", ";
            if(!textureStorage[totalAnimationSets][i].loadFromFile(animTextureFiles[i]))
                exit(100 + i);
            else
           //     std::cout << "Finished loading \n" << animTextureFiles[i] << std::endl;

            builder.push_back(&textureStorage[totalAnimationSets][i]);


        }
     //   std::cout <<"\n";
        std::cout << "Finished Adding to vector \n" << textureStorage.size() << std::endl;
        animationSetStorage[totalAnimationSets].loadAnimations(frameTime, looped, totalFrames, frameSize);
  //      std::cout << "Adding to storage " <<  std::endl;;
        animationSets[setName] = &animationSetStorage[totalAnimationSets];
        animationSetTextures[setName] = builder;
       // std::cout << "Ani Textures " << animationSets.size() << std::endl;

        totalAnimationSets++;

    }
    else
    {
        std::cout << ANIMS_PER_SET << " needed to create an animation set or animation already exists\n";
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
  /*  std::cout << "animation set" << animationSets.size() << std::endl;
    std::cout << "textures animation set" << animationSetTextures.size() << std::endl;
    std::cout << "textures" << textureStorage.size() << std::endl;*/
    if(direction < ANIMS_PER_SET)
    {
        //Change the current animation set only if the desired animation exists
        if( (currentAnimationSet == animationSets[animationName] && currentOrientation == direction) || animationSets.find(animationName) == animationSets.end() )
        {
            std::cout << "Not changing texture\n";
        }
        else
        {
            currentOrientation = direction;
            std::cout << "Changing animation to " << animationName << std::endl;
            std::cout << "Current Direction " << direction << std::endl;


            currentTexture = animationSetTextures[animationName][direction];
            //currentAnimationSet = animationSets[animationName];
            std::cout << "Before " << currentAnimationSet << std::endl;
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

    sprite.setPosition(spritePos.x - spriteBoxOffset.x, spritePos.y - spriteBoxOffset.y);
    sf::IntRect frame = currentAnimation->update(elapsedTime);

    sprite.setTextureRect(frame);
}

void AnimationComponent::updateCurrentAnimationSet(float elapsedTime, const sf::Vector2f& spritePos)
{

    sprite.setPosition(spritePos.x - spriteBoxOffset.x, spritePos.y - spriteBoxOffset.y);
  // std::cout << "After " << currentAnimationSet << std::endl;
    //sf::IntRect frame = currentAnimationSet->update(elapsedTime);
//std::cout << "Size " << animationSets.size() << std::endl;
   // sprite.setTextureRect(frame);
}

void AnimationComponent::drawCurrentFrame(sf::RenderWindow& window)
{
    window.draw(sprite);
}
