#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>

#include "Assets.h"
#include "resource_identifiers.h"

// easy and simplified resource management
namespace Resources {
void loadTexture(const Textures::ID id, const std::string& path);
sf::Texture& getTexture(const Textures::ID id);

void loadFont(const Fonts::ID id, const std::string& path);
sf::Font& getFont(const Fonts::ID id);
};  // namespace Resources

#endif