#ifndef WORLD_H
#define WORLD_H

#include "SFML\Graphics.hpp"
#include "Layer.h"
#include <vector>
#include "AssetManager.h"
#include "PhysLayer.h"
#include <iostream>
#include <fstream>
class World
{
public:
	//TO DO: three layer world with worldCenter to make perspective
	enum ELayer
	{
		EL_BACKGROUND_BACK,	//art layer that will act as a backdrop. NOTE-- not for skybox
		EL_BACKGROUND_FRONT,//art layer that should have background props that occlude overall background
		EL_PLAYGROUND_BACK,	//art layer that will be occluded by player
		EL_PLAYGROUND_MID,	//where the player will stand
		EL_PLAYGROUND_FRONT,//art layer that will occlude player
		EL_PHYS,			//the physics layer that should be drawn and updated with PLAYGROUND_MID
		EL_TOTAL			//Total layers for world creation			
	};
	World() = delete;
	World(sf::RenderWindow& pwindow);

	void draw(ELayer layerID);

	Layer& getActiveLayer();
	Layer& getLayer(ELayer layerToGet);
	PhysLayer& getPhysLayer(){ return physLayer; }
	int getActiveLayerID();
	void setActiveLayer(ELayer active);
	AssetManager& getAssets();
	bool isLayerBG(){ return activeLayer == EL_BACKGROUND_BACK || activeLayer == EL_BACKGROUND_FRONT; }
	bool loadTexture(std::string filename){ return assets.addTexture(filename); }

	bool save(std::string filename);

private:
	//load assets into manager
	AssetManager assets;
	ELayer activeLayer;
	sf::RenderWindow& window;
	std::vector<Layer> layers;
	PhysLayer physLayer;
};

#endif