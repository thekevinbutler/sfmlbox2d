#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "SFML\Graphics.hpp"
#include <map>
#include <string>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	bool addTexture(std::string filemane);
	bool addTexFromFullPath(std::string filepath, std::string filename);
	void removeTexture(std::string name);
	int getTextureCount() const;
	sf::Texture* getTexture(std::string name) const;
	std::vector<std::string> getTextureNames();
private:
	std::map<std::string, sf::Texture*> textures;

	struct TextureDeallocator
	{
		void operator()(const std::pair<std::string, sf::Texture*>& p) const
		{
			delete p.second;
		}
	};
};

#endif