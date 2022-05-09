#include "Resources.h"

#include <SFML/Graphics.hpp>

void Resources::loadTexture(const Textures::ID id, const std::string& path){
    TextureHolder::Instance().load(id, path);
}

sf::Texture& Resources::getTexture(const Textures::ID id) {
    return TextureHolder::Instance().get(id);
}

void Resources::loadFont(const Fonts::ID id, const std::string& path) {
    FontHolder::Instance().load(id, path);
}

sf::Font& Resources::getFont(const Fonts::ID id) {
    return FontHolder::Instance().get(id);
}