#ifndef VISIBLEOBJECT_H
#define VISIBLEOBJECT_H

#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include <iostream>
#include <fstream>
#include "AssetManager.h"
class VisibleObject : public GameObject, public sf::Drawable
{
public:

	VisibleObject(AssetManager& pAssets);
	//use set texture
	void setTexture(sf::Texture* pTex, std::string texName);
	bool occupiesPos(sf::Vector2f pos);
	//bool shouldDraw(sf::RenderWindow& window);

	virtual bool update(sf::Time dt);
	virtual void draw(sf::RenderTarget& render, sf::RenderStates states) const;
	sf::FloatRect getGlobalBounds();
	AssetManager& getAssets(){ return assets; }
	sf::Vector2f getSizeScaled();
	bool save(std::ofstream& saveFile);
	void load(std::ifstream& loadFile);
private:
	AssetManager& assets;
	sf::Texture tex;
	std::string textureName;
	sf::VertexArray verts;
};


#endif
