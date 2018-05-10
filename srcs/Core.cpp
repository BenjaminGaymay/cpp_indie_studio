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
	m_core.initWindow();
	irr::video::SColor color(255, 130, 255, 255);
	std::vector<std::string> map = {
		"##########",
		"#        #",
		"#  ###   #",
		"#        #",
		"#        #",
		"#     ####",
		"#        #",
		"# ####   #",
		"#        #",
		"##########"
	};

	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(255.0,255.0,255.0));
	irr::scene::IAnimatedMesh* ground;
	irr::scene::IMeshSceneNode* ground_node;

	irr::scene::IMeshSceneNode *room = m_core.m_sceneManager->addMeshSceneNode(m_core.m_sceneManager->getMesh("assets/room.3ds"));
	room->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	m_core.m_sceneManager->getMeshManipulator()->makePlanarTextureMapping(m_core.m_sceneManager->getMesh("assets/room.3ds"), 0.04f);
	room->setMaterialTexture(0, m_core.m_driver->getTexture("assets/sydney.bmp"));

	irr::scene::IAnimatedMeshSceneNode *sydney = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/sydney.md2"));
	sydney->setMD2Animation(irr::scene::EMAT_STAND);
	sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sydney->setMaterialTexture(0, m_core.m_driver->getTexture("assets/sydney.bmp"));
	sydney->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);
	sydney->setPosition(irr::core::vector3df(20, 60, 0));

	irr::scene::IAnimatedMeshSceneNode *sphere = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/earth.x"));
	sphere->setPosition(irr::core::vector3df(20,20,20));
	sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sphere->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	std::vector<irr::scene::IAnimatedMeshSceneNode *> cubes;
	int h = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '#') {
				cubes.push_back(m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/cube.md2")));
				cubes[h]->setMaterialTexture(0, m_core.m_driver->getTexture("assets/crate.jpg"));
				cubes[h]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
				cubes[h]->setPosition(irr::core::vector3df(i*cubes[h]->getBoundingBox().getExtent().X,100,j*cubes[h]->getBoundingBox().getExtent().X));
				h+=1;
			}
		}
	}



	int lastFps = -1;
	while (m_core.m_device->run()) {
		if (m_core.m_device->isWindowActive()) {
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
			}
		} else
			m_core.m_device->yield();
	}
}
