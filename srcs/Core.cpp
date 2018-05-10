/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include "Core.hpp"

Indie::Core::Core()
{}

Indie::Core::~Core()
{}

void Indie::Core::run()
{
	m_core.initIrrlicht();
	irr::video::SColor color(255, 130, 255, 255);

	irr::scene::IMeshSceneNode *cube = m_core.m_sceneManager->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df(0.0f, 0.0f, 20.0f));
	cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

	irr::scene::IAnimatedMeshSceneNode *sydney = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/sydney.md2"));
	sydney->setMD2Animation(irr::scene::EMAT_STAND);
	sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sydney->setMaterialTexture(0, m_core.m_driver->getTexture("assets/sydney.bmp"));
	sydney->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	irr::scene::IAnimatedMeshSceneNode *sphere = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/earth.x"));
	sphere->setPosition(irr::core::vector3df(20,20,20));
	sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sphere->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	while (m_core.m_device->run()) {
		m_core.m_driver->beginScene(true, true, color);
		m_core.m_sceneManager->drawAll();
		m_core.m_driver->endScene();
	}
}
