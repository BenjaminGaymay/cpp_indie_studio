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

void Indie::Core::createPalmier(irr::core::vector3df position)
{
	irr::scene::IAnimatedMeshSceneNode *object = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/palmier/palmier.obj"));
	object->setMD2Animation(irr::scene::EMAT_WAVE);
	object->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	object->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/palmier/palmier.bmp"));
	object->setPosition(position);
	object->setScale(irr::core::vector3df(0.1, 0.04, 0.1));
}

void Indie::Core::buildDecor()
{
	createPalmier(irr::core::vector3df(200, 20, 200));
	createPalmier(irr::core::vector3df(220, 20, 210));
	createPalmier(irr::core::vector3df(190, 20, 230));

	createPalmier(irr::core::vector3df(-180, 20, -300));
	createPalmier(irr::core::vector3df(-220, 20, -310));
	createPalmier(irr::core::vector3df(-190, 20, -330));
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

	/*irr::scene::IMeshSceneNode *room = m_core.m_sceneManager->addMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/room.3ds"));
	room->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	m_core.m_sceneManager->getMeshManipulator()->makePlanarTextureMapping(m_core.m_sceneManager->getMesh("assets/models/room.3ds"), 0.04f);
	room->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/sydney.bmp"));*/

	/*irr::scene::IAnimatedMeshSceneNode *bomber = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("test/rocket_ICBM.3ds"));
	//irr::scene::IAnimatedMeshSceneNode *bomber = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/bomberman_1.0.9.obj"));
	bomber->setMD2Animation(irr::scene::EMAT_WAVE);
	bomber->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	bomber->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	bomber->setMaterialTexture(0, m_core.m_driver->getTexture("test/tip.bmp"));
	bomber->setPosition(irr::core::vector3df(20, 100, 0));
	bomber->setScale(irr::core::vector3df(1, 1, 1));*/

	/*irr::scene::IAnimatedMeshSceneNode *sphere = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/earth.x"));
	sphere->setPosition(irr::core::vector3df(20,20,20));
	sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sphere->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);*/


	irr::scene::IAnimatedMesh *water = m_core.m_sceneManager->addHillPlaneMesh("waterMesh",
									  irr::core::dimension2d<irr::f32>(30, 30),
									  irr::core::dimension2d<irr::u32>(30,30), 0, 0,
									  irr::core::dimension2d<irr::f32>(0, 0),
									  irr::core::dimension2d<irr::f32>(10, 10));
	water->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	irr::scene::ISceneNode *node = m_core.m_sceneManager->addWaterSurfaceSceneNode(water->getMesh(0), 3.0f, 300.0f, 30.0f);
	node->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/water/water.jpg"));
	node->setPosition(irr::core::vector3df(15, 15, 0));

	buildDecor();
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
