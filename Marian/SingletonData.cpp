#include "SingletonData.h"

SingletonData::SingletonData()
{
    if(!image.loadFromFile("data/textures/simples_pimples.png"))
    {
        cout << "Could not load data/textures/simples_pimples.png" << endl;
        good = false;
		return;
    }

    image.createMaskFromColor(sf::Color(90, 82, 104));
    texture.loadFromImage(image);
    good = true;
}

sf::Texture * SingletonData::getTexture()
{
    return &texture;
}

bool SingletonData::isGood()
{
    return good;
}
