#include "AssetManager.h"

AssetManager::AssetManager(b2World& pworld) : world(pworld)
{
}
AssetManager::~AssetManager()
{
	std::for_each(textures.begin(), textures.end(), TextureDeallocator());
}

//returns whether or not it failed to load texture
bool AssetManager::addTexture(std::string filename)
{
	sf::Texture* tex = new sf::Texture();
	if (tex->loadFromFile("../assets/textures/" + filename)) //if succeeds then insert else no texture
	{
		textures.insert(std::pair<std::string, sf::Texture*>(filename, tex));
		return true;
	}
	return false;

}
bool AssetManager::addTexFromFullPath(std::string filepath, std::string filename)
{
	sf::Texture* tex = new sf::Texture();
	if (tex->loadFromFile(filepath)) //if succeeds then insert else no texture
	{
		textures.insert(std::pair<std::string, sf::Texture*>(filename, tex));
		return true;
	}
	return false;
}

sf::Texture* AssetManager::getTexture(std::string name) const
{
	std::map<std::string, sf::Texture*>::const_iterator results = textures.find(name);
	if (textures.end() == results)
	{
		return NULL;
	}
	return results->second;
}

std::vector<std::string> AssetManager::getTextureNames()
{
	std::map<std::string, sf::Texture*>::iterator iter;
	std::vector<std::string>results;
	for (iter = textures.begin(); iter != textures.end(); ++iter)
	{
		results.emplace_back(iter->first);
	}
	return results;
}
void AssetManager::removeTexture(std::string name)
{
	std::map<std::string, sf::Texture*>::iterator results = textures.find(name);
	if (textures.end() != results)
	{
		delete results->second;
		textures.erase(results);
	}
}
int AssetManager::getTextureCount() const
{
	return textures.size();
}

void AssetManager::setPlayerStart(sf::Vector2f newPos)
{
	playerStart = newPos;
}
sf::Vector2f AssetManager::getPlayerStart()
{
	return playerStart;
}

b2World& AssetManager::getPhysWorld()
{
	return world;
}
void AssetManager::clear()
{
	textures.clear();
	playerStart = sf::Vector2f(0.0f, 0.0f);
}