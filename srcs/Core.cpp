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
	int lastFps = -1;
	m_run = true;
	Events event;
	m_core.initWindow(event);
	Map map;
	map.initMap("assets/maps/map2.txt");
	map.load(m_core.m_device);
	irr::video::SColor color(255, 130, 255, 255);

	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0,255.0,255.0));

	irr::scene::IMeshSceneNode *room = m_core.m_sceneManager->addMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/room.3ds"));
	room->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	m_core.m_sceneManager->getMeshManipulator()->makePlanarTextureMapping(m_core.m_sceneManager->getMesh("assets/models/room.3ds"), 0.04f);
	room->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/sydney.bmp"));

	irr::scene::IAnimatedMeshSceneNode *bomber = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/bigbomber.obj"));
	bomber->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bomber->setPosition(irr::core::vector3df(-20, 55, 0));

	while (m_core.m_device->run() && m_run) {
		if (m_core.m_device->isWindowActive()) {
			processEvents(event);
			m_core.m_driver->beginScene(true, true, color);
			m_core.m_sceneManager->drawAll();
			m_core.m_driver->endScene();
			drawCaption(lastFps);
		} else
			m_core.m_device->yield();
	}
}
