#include "World.h"

World::World(sf::RenderWindow& pwindow, b2World& pWorld) : window(pwindow), world(pWorld), physLayer(pwindow, pWorld), assets(pWorld)
{
	activeLayer = EL_PLAYGROUND_MID;
	//doesn't matter which is denoted forground and background, int index + enum will clarify
	for (int i = 0; i < ELayer::EL_TOTAL; i++)
	{
		layers.emplace_back(Layer(pwindow,assets));
	}
}

//return false if you want to change worlds
bool World::update(sf::Time dt)
{
	for (int i = 0; i < EL_TOTAL; i++)
	{
		layers[i].update(dt);
	}
	//think about it
	//physLayer.update(dt);
	return true;
}

//drawn only specified layer since window view needs to be set for each distinct layer
void World::draw(ELayer layerID)
{
	if (layerID == EL_PHYS)
	{
		physLayer.draw();
	}
	else
	{
		layers[layerID].draw();
	}
}

Layer& World::getActiveLayer()
{
	return layers[activeLayer];
}
Layer& World::getLayer(ELayer layerToGet)
{
	return layers[layerToGet];
}
int World::getActiveLayerID()
{
	return activeLayer;
}

AssetManager& World::getAssets()
{
	return assets;
}

void World::setActiveLayer(ELayer active)
{
	activeLayer = active;
}

bool World::save(std::string filename)
{
	std::ofstream saveFile(filename);
	if (saveFile.is_open())
	{
		//save texture count
		saveFile << assets.getTextureCount() << std::endl;

		//for loop through texture names and save them
		std::vector<std::string> texNames = assets.getTextureNames();
		for (int i = 0; i < assets.getTextureCount(); i++)
		{
			saveFile << texNames[i] << std::endl;

		}

		//for through all layers and save objects
		for (int i = 0; i < EL_TOTAL; i++)
		{
			layers[i].save(saveFile);
		}

		//save the physics layer
		physLayer.save(saveFile);
	}

	saveFile.close();
	return true;
}

void World::load(std::string filename)
{
	clear();
	std::ifstream loadFile(filename);
	if (loadFile.is_open())
	{
		//get texture count
		int texCount = 0;
		loadFile >> texCount;

		//for through the texCount and load each name of file
		for (int i = 0; i < texCount; i++)
		{
			std::string name;
			loadFile >> name;
			assets.addTexture(name);
		}

		//for through all layers and load them
		for (int i = 0; i < EL_TOTAL; i++)
		{
			layers[i].load(loadFile);
		}

		//load phys Layer
		physLayer.load(loadFile);
	}
	loadFile.close();
}

void World::clear()
{
	physLayer.clear();
	for (int i = 0; i < EL_TOTAL; i++)
	{
		layers[i].clear();
	}

	///move down!! clear assets after dependent object are destroyed
	assets.clear();
}