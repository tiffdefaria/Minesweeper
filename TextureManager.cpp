#include "TextureManager.h"

unordered_map<string, Texture> TextureManager::textures;

void TextureManager::LoadTexture(string file){
    string path = "./images/";
    path += file + ".png";
    textures[file].loadFromFile(path);
}
Texture& TextureManager::GetTexture(string file){
    if(textures.find(file) == textures.end()){
        LoadTexture(file);
    }
    return textures[file];
}

void TextureManager::Clear() {
    textures.clear();
}


