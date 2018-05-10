/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include <vector>
#include "Core.hpp"

Indie::Core::Core()
{}

Indie::Core::~Core()
{}

void Indie::Core::run()
{
	m_core.initWindow();
	irr::video::SColor color(255, 130, 255, 255);

	// irr::scene::IMeshSceneNode *cube = m_core.m_sceneManager->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df(0.0f, 0.0f, 20.0f));
	// cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

	m_core.m_sceneManager->setAmbientLight(irr::video::SColorf(1.0, 1.0, 5.0, 0.0));
	irr::scene::IAnimatedMesh *room = m_core.m_sceneManager->getMesh("assets/room.3ds");
	irr::scene::IMeshSceneNode *Nroom = m_core.m_sceneManager->addMeshSceneNode(room->getMesh(0));
	Nroom->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	m_core.m_sceneManager->getMeshManipulator()->makePlanarTextureMapping(room->getMesh(0), 0.04f);
	Nroom->setMaterialTexture(0, m_core.m_driver->getTexture("assets/sydney.bmp"));

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
	for (int i = 0;i < 10; i++) {
		cubes.push_back(m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/cube.md2")));
		cubes[i]->setMaterialTexture(0, m_core.m_driver->getTexture("assets/crate.jpg"));
		cubes[i]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		cubes[i]->setPosition(irr::core::vector3df(i*10,i*10,i*10));
	}
	// irr::scene::IAnimatedMeshSceneNode *cube = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/cube.md2"));
	// cube->setMaterialTexture(0, m_core.m_driver->getTexture("assets/crate.jpg"));
	// cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	while (m_core.m_device->run()) {
		m_core.m_driver->beginScene(true, true, color);
		m_core.m_sceneManager->drawAll();
		m_core.m_driver->endScene();
	}
}
