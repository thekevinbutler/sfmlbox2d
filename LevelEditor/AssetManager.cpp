#include "AssetManager.h"

std::string filenames[] =
{
	"cliff1.png",
	"Earth_Platform1.png",
	"flower1.png",
	"grass1.png",
	"no.png",
	"platform1.png",
	"rock1.png",
	//"spike1.png"
};

AssetManager::AssetManager()
{
	int count = sizeof(filenames) / sizeof(std::string);
	for (int i = 0; i < count; i++)
	{
		addTexture(filenames[i]);
	}
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