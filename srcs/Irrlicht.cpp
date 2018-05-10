/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include "Irrlicht.hpp"

Indie::Irrlicht::Irrlicht()
{}

Indie::Irrlicht::~Irrlicht()
{
	m_device->drop();
}

void Indie::Irrlicht::initIrrlicht()
{
	irr::core::vector3df vec;

	m_device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(800,600), 32, false, true, false, 0);
	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_device->getCursorControl()->setVisible(false);
	m_device->setWindowCaption(L"floating");
	m_camera.initCamera(m_sceneManager, vec);
}

// std::unique_ptr<irr::IrrlichtDevice> Indie::Irrlicht::getDevice() const
// {
// 	return std::make_unique<irr::IrrlichtDevice>(m_device);
// }

// std::unique_ptr<irr::video::IVideoDriver> Indie::Irrlicht::getDriver() const
// {
// 	return std::make_unique<irr::video::IVideoDriver>(m_driver);
// }

// std::unique_ptr<irr::scene::ISceneManager> Indie::Irrlicht::getSceneManager() const
// {
// 	return std::make_unique<irr::scene::ISceneManager>(m_sceneManager);
// }