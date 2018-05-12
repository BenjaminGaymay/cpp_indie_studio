/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <iostream>
#include "Core.hpp"

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
		std::cout << "FPS: " << lastFps << std::endl;
	}
}

void Indie::Core::processEvents(const Events &event)
{
	if (event.isKeyDown(irr::KEY_ESCAPE))
		m_run = false;
	if (event.isKeyDown(irr::KEY_KEY_A))
		std::cout << event.MouseState.Position.X << " : " << event.MouseState.Position.Y << std::endl;
}

void Indie::Core::run()
{
	Events event;
	Map map;
	int lastFps = -1;
	irr::video::SColor color(255, 168, 201, 255);

	m_core.initWindow(event);
	m_run = true;
	map.initMap("assets/maps/map2.txt");
	map.load(m_core.m_device);

	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0,255.0,255.0));
	buildDecor();
	/*irr::scene::IAnimatedMeshSceneNode *player = createTexture("assets/models/sydney.md2", "assets/models/sydney.bmp", {300, 80, 300}, {0, 0, 0}, {1, 1, 1});*/
	while (m_core.m_device->run() && m_run) {
		if (m_core.m_device->isWindowActive()) {
			processEvents(event);
			m_core.m_driver->beginScene(true, true, color);
			m_core.m_sceneManager->drawAll();
			/*if (player) {
				auto position = player->getPosition();
				if (event.isKeyDown(irr::KEY_RIGHT)) {
					position.X += 10;
				} else if (event.isKeyDown(irr::KEY_LEFT)) {
					position.X -= 10;
				} else if (event.isKeyDown(irr::KEY_DOWN)) {
					position.Z -= 10;
				} else if (event.isKeyDown(irr::KEY_UP)) {
					position.Z += 10;
				}
				moveTexture(player, position);
			}*/
			m_core.m_driver->endScene();
			drawCaption(lastFps);
		} else
			m_core.m_device->yield();
	}
}
