#include "Game.h"

Game::Game() : world(b2Vec2(0.0f, -20.0f))
{
    isLoaded = false;
    STATE = MENU;

    world.SetContactListener(&myContactListener);

    window.create(sf::VideoMode(1920, 1080), "Gra", sf::Style::Fullscreen);
	//window.create(sf::VideoMode(1500, 800), "Gra", sf::Style::Default);

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    if(!font.loadFromFile("data/Mecha.ttf"))
    {
        cout << "Could not load font data/Mecha.ttf" << endl;
        STATE = QUIT;
    }

    player = nullptr;
}

Game::~Game()
{
    removeData();
}

void Game::run()
{
    while(STATE != END)
    {
        switch(STATE)
        {
            case MENU:
            {
                displayMenu();
                break;
            }
            case RESUME:
            {
                play();
                break;
            }
            case NEW_GAME:
            {
                if(isLoaded)
                {
                    removeData();
                }
				level = 1;
                loadData(level);
                break;
            }
            case SELECT_LEVEL:
            {
                displaySelectLevel();
                break;
            }
            case INSTRUCTION:
            {
                displayInstruction();
                break;
            }
            case QUIT:
            {
                removeData();
                STATE = END;
                break;
            }
        }
    }
}

void Game::displayMenu()
{
    //Obliczenie view. View to nie to samo co window.
    sf::Vector2f sizeView = window.getView().getSize();
    sf::Vector2f positionView(window.getView().getCenter().x-sizeView.x/2, window.getView().getCenter().y-sizeView.y/2);
    sf::Vector2f centerView = window.getView().getCenter();

    //Przygotowanie menu
    const int n = 5;

    sf::String str[n] = {"RESUME", "NEW GAME", "SELECT LEVEL", "INSTRUCTION", "QUIT"};
    sf::Text text[n];

    for(int i = 0; i < n; i++)
    {
        text[i].setFont(font);
        text[i].setCharacterSize((sizeView.y-50)/n);
        text[i].setString(str[i]);
        text[i].setPosition(centerView.x-text[i].getLocalBounds().width/2, positionView.y +(sizeView.y-50)/n*i);
    }

	//Glowna petla menu
    while(STATE == MENU)
    {
		//Obliczenie pozycji kursora na view
        sf::Vector2f positionMouse(sf::Mouse::getPosition(window));
        sf::Vector2u sizeWindow = window.getSize();
        sf::Vector2f positionMouseOnView(positionView.x + positionMouse.x * sizeView.x/sizeWindow.x, positionView.y + positionMouse.y * sizeView.y/sizeWindow.y);

		//Obsluga zdarzen
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::MouseButtonReleased:
                {
                    if(text[0].getGlobalBounds().contains(positionMouseOnView) && event.key.code == sf::Mouse::Left && isLoaded)
                    {
                        STATE = RESUME;
                    }
                    else if(text[1].getGlobalBounds().contains(positionMouseOnView) && event.key.code == sf::Mouse::Left)
                    {
                        STATE = NEW_GAME;
                    }
                    else if(text[2].getGlobalBounds().contains(positionMouseOnView) && event.key.code == sf::Mouse::Left)
                    {
                        STATE = SELECT_LEVEL;
                    }
                    else if(text[3].getGlobalBounds().contains(positionMouseOnView) && event.key.code == sf::Mouse::Left)
                    {
                        STATE = INSTRUCTION;
                    }
                    else if(text[4].getGlobalBounds().contains(positionMouseOnView) && event.key.code == sf::Mouse::Left)
                    {
                        STATE = QUIT;
                    }
                    break;
                }
                case sf::Event::KeyPressed:
                {
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        STATE = QUIT;
                    }
                    break;
                }
                case sf::Event::Closed:
                {
                    STATE = QUIT;
                    break;
                }
            }
        }

        window.clear(sf::Color::Black);

		//Podswietlenie opcji, na ktora wskazuje kursor
        for(int i = 0; i < n; i++)
        {
            if(text[i].getGlobalBounds().contains(positionMouseOnView))
            {
				text[i].setFillColor(sf::Color::Cyan);
            }
			else
            {
				text[i].setFillColor(sf::Color::White);
            }
        }

		//Jesli gra nie jest zaladaowana, to nie mozna wznowic, dlatego jest inny kolor na RESUME
        if(!isLoaded)
        {
			text[0].setFillColor(sf::Color(128, 128, 128));
        }

		//Rysowanie
        for(int i = 0; i < n; i++)
        {
            window.draw(text[i]);
        }

        window.display();
    }
}

void Game::displaySelectLevel()
{
	//Obliczenie view. View to nie to samo co window.
	sf::Vector2f sizeView = window.getView().getSize();
	sf::Vector2f positionView(window.getView().getCenter().x - sizeView.x / 2, window.getView().getCenter().y - sizeView.y / 2);
	sf::Vector2f centerView = window.getView().getCenter();

	int n = 0;
	while (true)
	{
		string filePath = "data/levels/level_";
		filePath += intToStr(n + 1);
		filePath += ".png";

		ifstream file(filePath);
		if (file.good())
		{
			n++;
		}
		else
		{
			break;
		}
		file.close();
	}

	vector<sf::String> str(n);
	vector<sf::Text> text(n);

	int x = 30;
	int y = 30;
	for (int i = 0; i < n; i++)
	{
		str[i] = to_string(i + 1);
		text[i].setFont(font);
		text[i].setCharacterSize(48);
		text[i].setString(str[i]);
		text[i].setPosition(positionView.x + x, positionView.y + y);

		x += 150;
		if (x > sizeView.x - 80)
		{
			x = 30;
			y += 100;
		}
	}

	while (STATE == SELECT_LEVEL)
	{
		////Obliczenie pozycji myszy na view
		sf::Vector2f positionMouse(sf::Mouse::getPosition(window));
		sf::Vector2u sizeWindow = window.getSize();
		sf::Vector2f positionMouseOnView(positionView.x + positionMouse.x * sizeView.x / sizeWindow.x, positionView.y + positionMouse.y * sizeView.y / sizeWindow.y);

		//Obsluga zdarzen
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::MouseButtonReleased:
				{
					for (unsigned int i = 0; i < text.size(); i++)
					{
						if (text[i].getGlobalBounds().contains(positionMouseOnView) && event.key.code == sf::Mouse::Left)
						{
							if (isLoaded == true)
							{
								removeData();
							}
							level = i + 1;
							loadData(level);
						}
					}
				}
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						STATE = MENU;
					}
					break;
				}
				case sf::Event::Closed:
				{
					STATE = QUIT;
					break;
				}
			}
		}

		window.clear(sf::Color::Black);

		//Podswietlenie opcji, na ktora wskazuje kursor
		for (int i = 0; i < n; i++)
		{
			if (text[i].getGlobalBounds().contains(positionMouseOnView))
			{
				text[i].setFillColor(sf::Color::Cyan);
			}
			else
			{
				text[i].setFillColor(sf::Color::White);
			}
		}

		//Rysowanie
		for (int i = 0; i < n; i++)
		{
			window.draw(text[i]);
		}

		window.display();
	}
}

void Game::displayInstruction()
{
	//Obliczenie view. View to nie to samo co window.
	sf::Vector2f sizeView = window.getView().getSize();
	sf::Vector2f positionView(window.getView().getCenter().x - sizeView.x / 2, window.getView().getCenter().y - sizeView.y / 2);
	sf::Vector2f centerView = window.getView().getCenter();

	//Przygotowanie menu
	const int n = 3;

	sf::String str[n] = { "<- / -> - Walk", "SPACE - Jump", "Z - Shot" };
	sf::Text text[n];

	for (int i = 0; i < n; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize((sizeView.y - 400) / n);
		text[i].setString(str[i]);
		text[i].setPosition(centerView.x - text[i].getLocalBounds().width / 2, positionView.y + (sizeView.y - 400) / n * i);
		text[i].setFillColor(sf::Color::White);
	}

	while (STATE == INSTRUCTION)
	{
		//Obsluga zdarzen
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::KeyPressed:
				{
					if (event.key.code == sf::Keyboard::Escape)
					{
						STATE = MENU;
					}
					break;
				}
				case sf::Event::Closed:
				{
					STATE = QUIT;
					break;
				}
			}
		}

		//Rysowanie
		window.clear(sf::Color::Black);

		for (int i = 0; i < n; i++)
		{
			window.draw(text[i]);
		}

		window.display();
	}
}

void Game::loadData(int n)
{
    string filePath = "data/levels/level_";
    filePath += intToStr(n);
    filePath += ".png";

    sf::Image image;
    if(!image.loadFromFile(filePath.c_str()))
    {
        STATE = MENU;
		cout << "Could not load " + filePath << endl;
        isLoaded = false;
        return;
    }

    for(unsigned int i = 0; i < image.getSize().x; i++)
    {
        for(unsigned int j = 0; j < image.getSize().y; j++)
        {
            sf::Color color = image.getPixel(i, j);

            if(color == ID_EMPTY)
            {
                continue;
            }
            else if(color == ID_RED_BRICK)
            {
                RedBrick * redbrick = new RedBrick(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_PLAYER)
            {
                player = new Player(&world, sf::Vector2f(i * 64, j * 64));
				DynamicEntitites.push_back(player->body);
            }
            else if(color == ID_START)
            {
                Start * start = new Start(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_FINISH)
            {
                Finish * finish = new Finish(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_LAVA)
            {
                Lava * lava = new Lava(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_LAVA_UP)
            {
                Lava_Up * lava_up = new Lava_Up(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_WATER)
            {
                Water * water = new Water(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_WATER_UP)
            {
                Water_Up * water_up = new Water_Up(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_GROUND)
            {
                Ground * ground = new Ground(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_GRASS_LOW)
            {
                Grass_Low * grass_low = new Grass_Low(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_GRASS_HIGH)
            {
                Grass_High * grass_high = new Grass_High(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_WOOD)
            {
                Wood * wood = new Wood(&world, sf::Vector2f(i * 64, j * 64));
            }
            else if(color == ID_SKELETON_WEAK)
            {
                SkeletonWeak * skeleton_weak = new SkeletonWeak(&world, sf::Vector2f(i * 64, j * 64));
				DynamicEntitites.push_back(skeleton_weak->body);
            }
            else if(color == ID_SKELETON_AVERAGE)
            {
				SkeletonAverage * skeleton_average = new SkeletonAverage(&world, sf::Vector2f(i * 64, j * 64));
				DynamicEntitites.push_back(skeleton_average->body);
            }
            else if(color == ID_SKELETON_HARD)
            {
				SkeletonHard * skeleton_hard = new SkeletonHard(&world, sf::Vector2f(i * 64, j * 64));
				DynamicEntitites.push_back(skeleton_hard->body);
            }
            else if(color == ID_GHOST_WEAK)
            {
                GhostWeak * ghost_weak = new GhostWeak(&world, sf::Vector2f(i * 64, j * 64));
				DynamicEntitites.push_back(ghost_weak->body);
            }
            else if(color == ID_GHOST_AVERAGE)
            {

            }
            else if(color == ID_GHOST_HARD)
            {

            }
			else if (color == ID_COIN_1)
			{
				new Coin(1, &world, sf::Vector2f(i * 64, j * 64));
			}
			else if (color == ID_COIN_2)
			{
				new Coin(2, &world, sf::Vector2f(i * 64, j * 64));
			}
			else if (color == ID_COIN_3)
			{
				new Coin(5, &world, sf::Vector2f(i * 64, j * 64));
			}
			else if (color == ID_COIN_4)
			{
				new Coin(10, &world, sf::Vector2f(i * 64, j * 64));
			}
			else if (color == ID_COIN_5)
			{
				new Coin(20, &world, sf::Vector2f(i * 64, j * 64));
			}
            else
            {
                cout << "Did not recognize color " << (int)color.r << " " << (int)color.g << " " << (int)color.b << endl;
            }
        }
    }

    cout << "Loaded " << filePath << endl;
    isLoaded = true;
	STATE = RESUME;
}

void Game::play()
{
	//Do obliczen czasu
    sf::Clock clock;
    sf::Time time;
    float deltaTime = 0.0f;
    float accumulator = 0.0f;
    const float TIME_STEP = 1/60.0f;

	//Dokladnosc fizyki
    int velocityIt = 6;
    int positionIt = 2;

    sf::View view = window.getView();

	//Glowna petla
    while(STATE == RESUME)
    {
		//Sprawdzenie, czy trzeba wczytac nastepny poziom
		if (myContactListener.NextLevel)
		{
			removeData();
			loadData(++level);
			if (isLoaded == false)
			{
				//Nie udalo wczytac nastepnego poziomu, wiec koniec gry
				return;
			}
			myContactListener.NextLevel = false;
		}

        sf::Event event;

		//Te zmienne decyduja o tym jak blisko krawedzi ekranu musi byc gracz, zeby widok sie przesunal
        int z = view.getSize().x / 3;
		int k = view.getSize().x / 4;

		//Pobranie pozycji gracza
        sf::Vector2f positionPlayer(B2DtoSF(player->body->GetPosition().x), B2DtoSF(-player->body->GetPosition().y));
		//Srodek widoku
        sf::Vector2f centerView = view.getCenter();
		//Obliczenie ograniczenia na polozenie kamery
        sf::Vector2f limit(view.getSize().x/2-z, view.getSize().y/2-k);

		//Obliczanie polozenia kamery
        if(centerView.x > positionPlayer.x+limit.x)
            centerView.x = positionPlayer.x+limit.x;
        else if(centerView.x < positionPlayer.x-limit.x)
            centerView.x = positionPlayer.x-limit.x;

        if(centerView.y > positionPlayer.y+limit.y)
            centerView.y = positionPlayer.y+limit.y;
        else if(centerView.y < positionPlayer.y-limit.y)
            centerView.y = positionPlayer.y-limit.y;

		//Do znajdowania obecnie widocznych elementow (zeby nie aktualizowac wszystkich, nawet tych, ktorych nie widac).
		b2Vec2 positionPlayerBox2D = player->body->GetPosition();
		b2Vec2 positionRelativePlayerToCenterViewBox2D = b2Vec2(SFtoB2D(centerView.x - positionPlayer.x),
			-SFtoB2D(centerView.y - positionPlayer.y));
		b2Vec2 centerViewBox2D = positionPlayerBox2D + positionRelativePlayerToCenterViewBox2D;
		b2Vec2 viewSizeBox2DDividedBy2 = b2Vec2(SFtoB2D(view.getSize().x / 2), SFtoB2D(view.getSize().y / 2));

		//Aktualizacja polozenia kamery
        view.setCenter(sf::Vector2f(centerView.x, centerView.y));
        window.setView(view);

		//Obsluga zdarzen
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                {
                    if(event.key.code == sf::Keyboard::Escape)
                    {
                        STATE = MENU;
						return;
                    }
                    else if(event.key.code == sf::Keyboard::Key::Z)
                    {
                        Entity * bullet = player->shoot();
						if (bullet)
						{
							DynamicEntitites.push_back(bullet->body);
						}
                    }
                    break;
                }
                case sf::Event::Closed:
                {
					removeData();
                    STATE = QUIT;
                    break;
                }
            }
        }

        deltaTime = clock.getElapsedTime().asSeconds();
        accumulator += deltaTime;
        clock.restart();

        while(accumulator > TIME_STEP)
        {
			//Obsluga sterowania
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            {
                player->left();
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            {
                player->right();
            }
            else
            {
                player->stop();
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                player->jump();
            }

			//Obliczenia fizyki gry
            world.Step(TIME_STEP, velocityIt, positionIt);
            accumulator -= TIME_STEP;

			//Jesli gracz zginal, koniec gry
            if(player->toRemove == true)
            {
                removeData();
                STATE = MENU;
				return;
            }

			//Aktualizacja wazniejszych elementow
			for (list<b2Body *>::iterator iter = DynamicEntitites.begin(); iter != DynamicEntitites.end();)
			{
				Entity * entity = (Entity *)(*iter)->GetUserData();
				
				//Usuwnaie niepotrzebnych elementow
				if (entity->toRemove == true)
				{
					delete entity;
					iter = DynamicEntitites.erase(iter);
				}
				else
				{
					entity->update();
					iter++;
				}
			}
        }

		//Aktualizacja (do szukania widocznych elementow)
		positionPlayerBox2D = player->body->GetPosition();
		positionRelativePlayerToCenterViewBox2D = b2Vec2(SFtoB2D(centerView.x - positionPlayer.x),
			-SFtoB2D(centerView.y - positionPlayer.y));
		centerViewBox2D = positionPlayerBox2D + positionRelativePlayerToCenterViewBox2D;
		viewSizeBox2DDividedBy2 = b2Vec2(SFtoB2D(view.getSize().x / 2), SFtoB2D(view.getSize().y / 2));

		//Rysowanie
        window.clear(sf::Color::Black);

		//Znalezienie widocznych elementow typu WALL i ITEM. Aktualizacja i rysowanie.
		MyQueryCallback wallQuery;
		wallQuery.Type = WALL | ITEM;
		b2AABB aabb;
		aabb.upperBound = centerViewBox2D + viewSizeBox2DDividedBy2;
		aabb.lowerBound = centerViewBox2D - viewSizeBox2DDividedBy2;
		world.QueryAABB(&wallQuery, aabb);
        for(set<b2Body *>::iterator iter = wallQuery.FoundBodies.begin(); iter != wallQuery.FoundBodies.end(); iter++)
        {
			Entity * entity = (Entity *)(*iter)->GetUserData();

			//Usuwnaie niepotrzebnych elementow
			if (entity->toRemove == true)
			{
				delete entity;
			}
			else
			{
				entity->update();
				window.draw(*entity);
			}
        }

		//Znalezienie i narysowanie pozostalych elementow (wszystkich oprocz WALL). Tylko rysowanie, bo update bylo juz wczesniej na nich.
		MyQueryCallback otherEntitiesQuery;
		otherEntitiesQuery.Type = BULLET | ENEMY | PLAYER;
		world.QueryAABB(&otherEntitiesQuery, aabb);
		for (set<b2Body *>::iterator iter = otherEntitiesQuery.FoundBodies.begin(); iter != otherEntitiesQuery.FoundBodies.end(); iter++)
		{
			Entity * entity = (Entity *)(*iter)->GetUserData();
			window.draw(*entity);
		}

		sf::Sprite sprite[2];
		sprite[0].setTexture(*SingletonData::getSingletonData().getTexture());
		sprite[0].setTextureRect(sf::IntRect(sf::Vector2i(29 * 64, 47 * 64), sf::Vector2i(64, 64)));
		sprite[0].setPosition(centerView.x - view.getSize().x / 2, centerView.y - view.getSize().y / 2);
		
		sprite[1].setTexture(*SingletonData::getSingletonData().getTexture());
		sprite[1].setTextureRect(sf::IntRect(sf::Vector2i(27 * 64, 55 * 64), sf::Vector2i(64, 64)));
		sprite[1].setPosition(centerView.x - view.getSize().x / 2, centerView.y - view.getSize().y / 2 + 80);

		sf::String str[2];
		str[0] = to_string(player->coins);
		str[1] = to_string(player->health);
		sf::Text text[2];
		text[0].setFont(font);
		text[0].setCharacterSize(42);
		text[0].setString(str[0]);
		text[0].setPosition(centerView.x - view.getSize().x/2 + 80, centerView.y - view.getSize().y/2);
		text[0].setFillColor(sf::Color(255, 255, 0));

		text[1].setFont(font);
		text[1].setCharacterSize(42);
		text[1].setString(str[1]);
		text[1].setPosition(centerView.x - view.getSize().x / 2 + 80, centerView.y - view.getSize().y / 2 + 80);
		text[1].setFillColor(sf::Color(255, 0, 0));

		window.draw(text[0]);
		window.draw(text[1]);
		window.draw(sprite[0]);
		window.draw(sprite[1]);

        window.display();
    }
}

//Usuwanie danych
void Game::removeData()
{
	b2Body * body = world.GetBodyList();
	while (true)
	{
		b2Body * pom = body;
		if (pom == nullptr)
		{
			break;
		}
		else
		{
			body = body->GetNext();
			Entity * entity = (Entity *)pom->GetUserData();
			delete entity;
		}
	}

	DynamicEntitites.clear();

    player = nullptr;
    isLoaded = false;
}
