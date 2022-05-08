#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

#include "Assets.h"
#include "resource_identifiers.h"

// easy and simplified resource management
namespace Resources {
void loadTexture(const Textures::ID id, const std::string& path) {
    TextureHolder::Instance().load(id, path);
}
sf::Texture& getTexture(const Textures::ID id) {
    return TextureHolder::Instance().get(id);
}

void loadFont(const Fonts::ID id, const std::string& path) {
    FontHolder::Instance().load(id, path);
}
sf::Font& getFont(const Fonts::ID id) {
    return FontHolder::Instance().get(id);
}
};  // namespace Resources

#endif