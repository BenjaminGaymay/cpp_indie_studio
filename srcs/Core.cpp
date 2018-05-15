/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <iostream>
#include <Player.hpp>
#include <Bomb.hpp>
#include <algorithm>
#include "Core.hpp"
#include "Map.hpp"

Indie::Core::Core()
{
	generateTextureMap();
}

Indie::Core::~Core()
{}

void Indie::Core::drawCaption(int &lastFps)
{
	int fps = m_core.m_driver->getFPS();

	if (lastFps != fps) {
		irr::core::stringw str = L"Irrlicht Engine - Bomberman [";
		str += m_core.m_driver->getName();
		str += "] FPS:";
		str += fps;
		m_core.m_device->setWindowCaption(str.c_str());
		lastFps = fps;
		//std::cout << "FPS: " << lastFps << std::endl;
	}
}

void Indie::Core::processEvents(const Events &event)
{
	if (event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (event.isKeyDown(irr::KEY_KEY_A))
		std::cout << event.MouseState.Position.X << " : "
				  << event.MouseState.Position.Y << std::endl;
}

void Indie::Core::run()
{
	Events event;
	Map map3d(20.00f, 100.00f);
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);

	m_core.initWindow(event);
	m_run = true;
	map3d.initMap("assets/maps/map2.txt");
	map3d.load(*this);

	m_core.m_sceneManager->setAmbientLight(
			irr::video::SColorf(255.0, 255.0, 255.0));

	buildDecor();
	Indie::Player player(createTexture(_texturesMap[10], {0, map3d.getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true));
	resizeNode(player.getPlayer(), map3d.getSize());
	std::vector<Indie::Bomb> bombs;
	while (m_core.m_device->run() && m_run) {
		if (m_core.m_device->isWindowActive()) {
			processEvents(event);
			m_core.m_driver->beginScene(true, true, color);
			/*if (event.isKeyDown(irr::KEY_SPACE)) {
				for (std::size_t i = 0 ; i < 5 ; ++i) {
					*//*sauto pos = player.getPlayer()->getPosition();
					pos.X += (map.getMap()[0]->getBoundingBox().getExtent().Z) * i;
					createTexture(_texturesMap[2],  pos, {0, 0, 0}, {10, 10, 10}, false);*//*
				}
				//Indie::Bomb bomb(5, 10);
				*//*bomb.setTexture(createTexture(_texturesMap[2], player.getPlayer()->getPosition(), {0, 0, 0}, {1, 1, 1}, false));
				bombs.push_back(bomb);*//*
			}
			//bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Indie::Bomb &row) {return row.boom();}), bombs.end());*/
			player.move(event);
			m_core.m_sceneManager->drawAll();
			m_core.m_driver->endScene();
			drawCaption(lastFps);
		} else
			m_core.m_device->yield();
	}
}

irr::f32 Indie::Core::resizeNode(irr::scene::IAnimatedMeshSceneNode *node, const float &size)
{
	irr::f32 cubeSize = (node->getBoundingBox().getExtent().Z) * node->getScale().Z;
	if (cubeSize != size)
		node->setScale({size / cubeSize, size / cubeSize, size / cubeSize});
	cubeSize = (node->getBoundingBox().getExtent().Z) * node->getScale().Z;
	return cubeSize;
}

const Indie::Core::textureElem *Indie::Core::getTexture(const int &nb)
{
	if (_texturesMap.find(nb) != _texturesMap.end())
		return &_texturesMap[nb];
	return nullptr;

}