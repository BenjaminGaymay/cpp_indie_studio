/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include <iostream>
#include <Player.hpp>
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
	irr::u32 then = m_core.m_device->getTimer()->getTime();
	Indie::Player player(createTexture(_texturesMap[10], {300, 80, 300}, {0, 0, 0}, {1, 1, 1}));
	player.getPlayer()->setFrameLoop(0, 13);
	player.getPlayer()->setAnimationSpeed(15);
	// This is the movemen speed in units per second.
	while (m_core.m_device->run() && m_run) {
		if (m_core.m_device->isWindowActive()) {
			processEvents(event);
			m_core.m_driver->beginScene(true, true, color);
			const irr::u32 now = m_core.m_device->getTimer()->getTime();
			player.move(event, now, then);
			/*if (event.isKeyDown(irr::KEY_KEY_Q)) {
				if (player.isStanding()) player.getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
				player.setStanding(false);
				nodePosition.Z += MOVEMENT_SPEED * frameDeltaTime;
			} else if(event.isKeyDown(irr::KEY_KEY_D)) {
				if (player.isStanding()) player.getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
				player.setStanding(false);
				nodePosition.Z -= MOVEMENT_SPEED * frameDeltaTime;
			} else if(event.isKeyDown(irr::KEY_KEY_S)) {
				if (player.isStanding()) player.getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
				player.setStanding(false);
				nodePosition.X -= MOVEMENT_SPEED * frameDeltaTime;
			} else if(event.isKeyDown(irr::KEY_KEY_Z)) {
				if (player.isStanding()) player.getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
				player.setStanding(false);
				nodePosition.X += MOVEMENT_SPEED * frameDeltaTime;
			} else {
				if (!player.isStanding()) player.getPlayer()->setMD2Animation(irr::scene::EMAT_STAND);
				player.setStanding(true);
			}
			rotationWithMove(player.getPlayer(), nodePosition);
			player.getPlayer()->setPosition(nodePosition);*/
			m_core.m_sceneManager->drawAll();
			m_core.m_driver->endScene();
			drawCaption(lastFps);
		} else
			m_core.m_device->yield();
	}
}
