#ifndef WORLD_H
#define WORLD_H

#include "SFML\Graphics.hpp"
#include "Layer.h"
#include <vector>
#include "AssetManager.h"
#include "PhysLayer.h"
#include <iostream>
#include <fstream>
#include "Box2D\Box2D.h"
#include "Player.h"
class World
{
public:
	enum ELayer
	{
		EL_BACKGROUND_BACK,	//art layer that will act as a backdrop. NOTE-- not for skybox
		EL_BACKGROUND_FRONT,//art layer that should have background props that occlude overall background
		EL_PLAYGROUND_BACK,	//art layer that will be occluded by player
		EL_PLAYGROUND_MID,	//where the player will stand
		EL_PLAYGROUND_FRONT,//art layer that will occlude player
		EL_PHYS,			//the physics layer that should be drawn and updated with PLAYGROUND_MID //NOT USED
		EL_TOTAL			//Total layers for world creation			
	};
	World() = delete;
	World(sf::RenderWindow& pwindow, b2World& pWorld);

	bool update(sf::Time dt);
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
	void load(std::string filename);
	void clear();
private:
	//load assets into manager
	AssetManager assets;
	b2World& world;
	ELayer activeLayer;
	sf::RenderWindow& window;
	std::vector<Layer> layers;
	PhysLayer physLayer;
};

#endif