#pragma once

#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"

///Class which provides managing data on only one instance
class SingletonData
{
    private:
		///Constructor
        SingletonData();
		///Constructor
        SingletonData(const SingletonData &);

        bool good;
        sf::Image image;
        sf::Texture texture;

    public:
		///Returns singleton
        static SingletonData & getSingletonData()
        {
            static SingletonData singletonData;
            return singletonData;
        }

		///Returns texture
        sf::Texture * getTexture();
        ///Indicates if everything  is ok
		bool isGood();
};