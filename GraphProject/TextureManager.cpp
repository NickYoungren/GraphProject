#include "TextureManager.h"

unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(const string &fileName) {
    string path = "C:/GraphProject/images/";
    path += fileName + ".png";

    textures[fileName].loadFromFile(path);
}

sf::Texture &TextureManager::GetTexture(const string& textureName) {
    if (textures.find(textureName) == textures.end()){
        LoadTexture(textureName);
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear();
}
