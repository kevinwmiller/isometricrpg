#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H
#include "animationset.h"
#include <vector>
#include <map>

class AnimationComponent
{
    public:
        AnimationComponent();
        ~AnimationComponent();

        static const int ANIMS_PER_SET = 8;

        sf::FloatRect getBoundingBox() const;
        void setSpriteBoundsOffset(const sf::Vector2f&);
        void setPosition(const sf::Vector2f&);
        void setSpriteColor(const sf::Color&);

        sf::Vector2f getSpritePosition() const;
        std::string getCurrentAnimationKey() const;
        std::string getCurrentAnimationSetKey() const;

        ///First parameter: Name used to reference the animation. Second Parameter: File to load the animation's texture from
        static void addAnimation(const std::string&, const std::string&, float, bool, int, sf::Vector2f);
        static void addAnimationSet(const std::string&, std::vector<std::string>, float, bool, int, sf::Vector2f);

        void changeAnimation(const std::string&);
        void changeAnimationSet(const std::string&, int);

        void resetAllAnimations();
        void resetCurrentAnimation();

        bool isCurrentAnimationFinished();
        bool isCurrentAnimationSetFinished();

        void updateCurrentAnimation(float, const sf::Vector2f&);
        void updateCurrentAnimationSet(float, const sf::Vector2f&);
        void drawCurrentFrame(sf::RenderWindow&);

    private:


        sf::Texture* currentTexture;
        Animation* currentAnimation;
        AnimationSet* currentAnimationSet;

        ///Textures and animations are referenced by the name given to them
        static std::map<const std::string, Animation*> animations;
        static std::map<const std::string, sf::Texture*> animationTextures;

        static std::map<const std::string, AnimationSet*> animationSets;
        static std::map<const std::string, std::vector<sf::Texture*>> animationSetTextures;


        static std::vector<Animation> animationStorage;
        static std::vector<AnimationSet> animationSetStorage;

        //Textures for individual animations as well as animation sets
        static std::vector<std::vector<sf::Texture>> textureStorage;


        sf::FloatRect boundingBox;
        sf::Vector2f spriteBoxOffset;
        int currentOrientation;

        static int totalAnimations;
        static int totalAnimationSets;

        sf::Color spriteColor;
        sf::Sprite sprite;

};

#endif // ANIMATIONCOMPONENT_H
