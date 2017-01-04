#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"

int main()
{
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600), "LIGHTING");
	sf::Texture tex;
	if (!tex.loadFromFile("../assets/no.png"))
	{
		return -1;
	}
	sf::Sprite sprite;
	sprite.setTexture(tex);
	sprite.setOrigin(tex.getSize().x / 2.0f, tex.getSize().y / 2.0f);
	sprite.setPosition(400, 300);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color(128, 128, 128, 255));
		window.draw(sprite);
		window.display();
	}


	return 0;
}


//used with lighting.frag
//int main()
//{
//	sf::RenderWindow window(sf::VideoMode(800, 600), "myshader");
//
//	sf::Shader shader;
//	if (shader.loadFromFile("lighting.frag", sf::Shader::Fragment))
//	{
//		shader.setParameter("texture", sf::Shader::CurrentTexture);
//		shader.setParameter("lcolor", sf::Color(255, 255, 255));
//
//		while (window.isOpen())
//		{
//			sf::Event event;
//			while (window.pollEvent(event))
//			{
//				switch (event.type)
//				{
//				case sf::Event::Closed:
//					window.close();
//					break;
//				}
//			}
//
//			sf::Vector2i mpos = sf::Mouse::getPosition(window);
//			shader.setParameter("light", sf::Vector3f(mpos.x, 600 - mpos.y, 100));
//
//			window.clear();
//
//			sf::RectangleShape rect(sf::Vector2f(800, 600));
//
//			window.draw(rect, &shader);
//			window.display();
//		}
//	}
//}

//#include <SFML\Graphics.hpp>
//#include <SFML\System.hpp>
//#include <SFML\Window.hpp>
//#include <iostream>

//void main()
//{
//	sf::RenderWindow _window(sf::VideoMode(800, 480, 32), "Lighting Test");
//	_window.setFramerateLimit(60);
//
//	sf::Shader lightingShader;
//	sf::RenderStates renderState;
//
//	sf::Texture texture;
//	texture.loadFromFile("image.png");
//
//	sf::Sprite sprite;
//	sprite.setTexture(texture);
//
//	sf::Texture backgroundTexture;
//	backgroundTexture.loadFromFile("light.png");
//
//	sf::Sprite background;
//	background.setTexture(backgroundTexture);
//
//	while (_window.isOpen())
//	{
//		int x = sf::Mouse::getPosition(_window).x;
//		int y = sf::Mouse::getPosition(_window).y;
//
//		lightingShader.loadFromFile("lightingShader.frag", sf::Shader::Fragment);
//		lightingShader.setParameter("exposure", 0.25f);
//		lightingShader.setParameter("decay", 0.97f);
//		lightingShader.setParameter("density", 0.97f);
//		lightingShader.setParameter("weight", 0.5f);
//		lightingShader.setParameter("lightPositionOnScreen", sf::Vector2f(0.5f, 0.5f));
//		lightingShader.setParameter("myTexture", sf::Shader::CurrentTexture);
//		renderState.shader = &lightingShader;
//
//		_window.clear(sf::Color::Black);
//		sprite.setPosition(x, y);
//		//sprite.setColor(sf::Color::Black);
//		//background.setPosition(400, 240);
//		_window.draw(background);
//		_window.draw(sprite, renderState);
//		_window.display();
//	}
//}
//
//int main()
//{
//	sf::RenderWindow renderWindow(sf::VideoMode(800, 600), "Normal maps, yo");
//
//	sf::Texture normalMap, colourMap;
//	normalMap.loadFromFile("car_normal.tga");
//	colourMap.loadFromFile("car_colour.png");
//
//	sf::Sprite sprite = sf::Sprite(colourMap);
//	sprite.setPosition(400, 300);
//	sf::Shader shader;
//	bool res = shader.loadFromFile("procedural.frag", sf::Shader::Fragment);
//
//	while (renderWindow.isOpen())
//	{
//		//poll input
//		sf::Event event;
//		while (renderWindow.pollEvent(event))
//		{
//			if (event.type == sf::Event::Closed)
//				renderWindow.close();
//		}
//
//
//		//update shader
//		shader.setParameter("normalMap", normalMap);
//		shader.setParameter("colourMap", colourMap);
//		shader.setParameter("light", sf::Vector3f(sf::Mouse::getPosition(renderWindow).x, 600.f - sf::Mouse::getPosition(renderWindow).y, 0.04f));
//
//		//draw
//		renderWindow.clear(sf::Color(128,128,128,255));
//		renderWindow.draw(sprite, &shader);
//		renderWindow.display();
//	}
//	return 0;
//}