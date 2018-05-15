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
#include "SplashScreen.hpp"

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
	Map map3d;
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);
	SplashScreen splash;
	m_core.initWindow(event);
	m_run = true;
	map3d.initMap("assets/maps/map2.txt");
	map3d.load(*this);

	m_core.m_sceneManager->setAmbientLight(
			irr::video::SColorf(255.0, 255.0, 255.0));
	splash.display(m_core.m_device);

	buildDecor();
	Indie::Player player(createTexture(_texturesMap[10], {0, 100, 0}, {0, 0, 0}, {0.25, 0.25, 0.25}, true));
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

const Indie::Core::textureElem &Indie::Core::getTexture(const int &nb)
{
	return _texturesMap[nb];
}