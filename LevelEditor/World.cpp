#include "World.h"

World::World(sf::RenderWindow& pwindow) : window(pwindow), physLayer(pwindow)
{
	activeLayer = EL_PLAYGROUND_MID;
	//doesn't matter which is denoted forground and background, int index + enum will clarify
	for (int i = 0; i < ELayer::EL_TOTAL; i++)
	{
		layers.emplace_back(Layer(pwindow));
	}
	VisibleObject* tempObj = new VisibleObject();
	tempObj->setPosition(100, 100);
	tempObj->setTexture(assets.getTexture("no.png"), "no.png");
	layers[EL_BACKGROUND_BACK].addObj(tempObj);

	VisibleObject* tempObj2 = new VisibleObject();
	tempObj2->setTexture(assets.getTexture("no.png"), "no.png");
	layers[EL_BACKGROUND_BACK].addObj(tempObj2);

	VisibleObject* tempObj3 = new VisibleObject();
	tempObj3->setTexture(assets.getTexture("no.png"), "no.png");
	tempObj3->setPosition(0,0);
	layers[EL_PLAYGROUND_MID].addObj(tempObj3);
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