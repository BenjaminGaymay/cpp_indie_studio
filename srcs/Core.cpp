/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include "Player.hpp"
#include "Bomb.hpp"
#include "Graphism.hpp"
#include "Core.hpp"
#include "Map.hpp"

Indie::Core::Core()
{}

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
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);

	m_core.initWindow(event);
	m_run = true;
	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0, 255.0, 255.0));
	Graphism graphism(m_core);
	Map map3d(20.00f, 100.00f);
	map3d.initMap("assets/maps/map2.txt");
	map3d.load(graphism);

	graphism.buildDecor();
	Indie::Player player(graphism.createTexture(*graphism.getTexture(10), {0, map3d.getHeight(), 0}, {0, 0, 0}, {2, 2, 2}, true));
	graphism.resizeNode(player.getPlayer(), map3d.getSize());
	player.setSpeed(1);
	while (m_core.m_device->run() && m_run) {
		if (m_core.m_device->isWindowActive()) {
			processEvents(event);
			m_core.m_driver->beginScene(true, true, color);
			//auto mdr = map3d.get3dBlock(player.getPlayer()->getPosition());
			player.move(event);
			m_core.m_sceneManager->drawAll();
			m_core.m_driver->endScene();
			drawCaption(lastFps);
		} else
			m_core.m_device->yield();
	}
}