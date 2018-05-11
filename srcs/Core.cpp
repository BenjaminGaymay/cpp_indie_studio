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

void Indie::Core::run()
{
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

	irr::scene::IAnimatedMeshSceneNode *sydney = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/sydney.md2"));
	sydney->setMD2Animation(irr::scene::EMAT_DEATH_FALLBACK);
	sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sydney->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/sydney.bmp"));
	sydney->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	sydney->setPosition(irr::core::vector3df(20, 60, 0));

	irr::scene::IAnimatedMeshSceneNode *bomber = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/bomberman_1.0.9.obj"));
	bomber->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bomber->setPosition(irr::core::vector3df(-20, 55, 0));
	bomber->setScale(irr::core::vector3df(7,7,7));

	irr::scene::IAnimatedMeshSceneNode *sphere = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/earth.x"));
	sphere->setPosition(irr::core::vector3df(20,20,20));
	sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sphere->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);


	int lastFps = -1;
	bool run = true;
	while (m_core.m_device->run() && run) {
		if (m_core.m_device->isWindowActive()) {
			if (event.isKeyDown(irr::KEY_ESCAPE))
				run = false;
			if (event.isKeyDown(irr::KEY_KEY_A))
				std::cout << event.MouseState.Position.X << " : " << event.MouseState.Position.Y << std::endl;
			m_core.m_driver->beginScene(true, true, color);
			m_core.m_sceneManager->drawAll();
			m_core.m_driver->endScene();
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
		} else
			m_core.m_device->yield();
	}
}
