#pragma once
#ifndef resources_identifiers_h
#define resources_identifiers_h

#include "resource_holder.h"
#include "Assets.h"

// Forward declaration of SFML classes
namespace sf
{
	class Texture;
	class Font;
}

// Forward declaration and a few type definitions
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID>			TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID>					FontHolder;

#endif