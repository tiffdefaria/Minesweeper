#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::unordered_map;
using namespace sf;
using namespace std;

class TextureManager{
    static unordered_map<string, Texture> textures;
    static void LoadTexture(string file);
public:
    static Texture& GetTexture(string file);
    static void Clear();
};
