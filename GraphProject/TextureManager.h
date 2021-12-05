#pragma once
#include <SFML/Graphics.hpp>
#include<unordered_map>
#include <string>

using namespace std;

class TextureManager{
public:
    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(const string& fileName);
    static sf::Texture& GetTexture(const string& textureName);
    static void Clear();
    };


