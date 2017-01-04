#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "SFML\Graphics.hpp"
#include <map>
#include <string>
#include "Box2D\Box2D.h"
class AssetManager
{
public:
	AssetManager(b2World& pworld);
	~AssetManager();

	bool addTexture(std::string filemane);
	bool addTexFromFullPath(std::string filepath, std::string filename);
	void removeTexture(std::string name);
	int getTextureCount() const;
	sf::Texture* getTexture(std::string name) const;
	std::vector<std::string> getTextureNames();

	//for player start
	void setPlayerStart(sf::Vector2f newPos);
	sf::Vector2f getPlayerStart();
	b2World& getPhysWorld();
	void clear();
private:
	std::map<std::string, sf::Texture*> textures;

	//loaded as a game object so it is an asset
	sf::Vector2f playerStart;
	//to give vis objs a reference to the physics world
	b2World& world;
	struct TextureDeallocator
	{
		void operator()(const std::pair<std::string, sf::Texture*>& p) const
		{
			delete p.second;
		}
	};
};

#endif