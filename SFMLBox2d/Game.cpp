#include "Game.h"
#include "util.h"


Game::Game() :world(b2Vec2(0.0f, 9.8f)), player(world), cam(window, player), gameWorld(window, world)
{
	//Window creation
	window.create(sf::VideoMode(1920, 1080), "Falling" /*sf::Style::Fullscreen*/);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	
	//init GUI view to default window dimensions and position
	viewGUI = window.getDefaultView();

	//IMPORTANT -- called after since we needed to create the window first
	cam.init();

	//init font and text object. set initial size
	if (!font.loadFromFile("consola.ttf"))
	{
		window.close();
	}
	debugText.setCharacterSize(18);
	debugText.setFont(font);
	
	//load world here
	gameWorld.load("world1.txt");
	player.setStartPos(gameWorld.getAssets().getPlayerStart());
}

int Game::run(int minFPS)
{
	//overall clock of game
	sf::Clock clock;
	//holds return value of elapsed clock time when calling clock.restart()
	sf::Time timeSinceLastUpdate;
	//fixed time of minFPS
	sf::Time TimePerFrame = sf::seconds(1.f / minFPS);
	while (window.isOpen()) 
	{
		processEvents();
		timeSinceLastUpdate = clock.restart();
		world.Step(/*1.0 / 60*/ timeSinceLastUpdate.asSeconds(), int32(8), int32(3));
		while (timeSinceLastUpdate > TimePerFrame) //lag would cause a greater dt so run "catch-up" updates 
		{
			timeSinceLastUpdate -= TimePerFrame; //hack away at big dt
			update(TimePerFrame); //use fixed minFPS for update
		}
		update(timeSinceLastUpdate);
		draw();
	}

	//deletion before exiting program
	
	return 0;
}

void Game::processEvents() 
{
	sf::Event event;
	player.processEvents();
	while (window.pollEvent(event)) {
		if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) 
		{
			window.close();
		}
		player.processEvent(event);
	}
}

void Game::update(sf::Time dt)
{
	cam.updatePos(dt);
	if (!player.update(dt))
	{
		gameWorld.load(player.getNextWorld() + ".txt");
	}
	gameWorld.update(dt);
}

void Game::draw()
{
	window.clear();
	cam.setView(LayeredView::EDrawView::DRAWVIEW_BACKGROUND);

	gameWorld.draw(World::ELayer::EL_BACKGROUND_BACK);
	gameWorld.draw(World::ELayer::EL_BACKGROUND_FRONT);

	cam.setView(LayeredView::EDrawView::DRAWVIEW_FOREGROUND);
	//eView.setView(EditorView::EDrawView::DRAWVIEW_FOREGROUND);
	gameWorld.draw(World::ELayer::EL_PLAYGROUND_BACK);

	player.draw(world, window);
	gameWorld.draw(World::ELayer::EL_PLAYGROUND_MID);

	gameWorld.draw(World::ELayer::EL_PLAYGROUND_FRONT);
	//gameWorld.draw(World::ELayer::EL_PHYS);


	window.setView(viewGUI);
	dMessage(player.sendDebug(), sf::Vector2f(0, 0));
	window.display();
}

void Game::dMessage(std::string msg, sf::Vector2f pos)
{
	debugText.setString(msg);
	debugText.setPosition(pos);
	window.draw(debugText);
}