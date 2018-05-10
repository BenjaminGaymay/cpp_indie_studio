/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Core
*/

#include "Window.hpp"

Indie::Window::Window()
{}

Indie::Window::~Window()
{
	m_device->drop();
}

void Indie::Window::initWindow()
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


irr::video::IVideoDriver *Indie::Window::getDriver() const
{
	return m_device->getVideoDriver();
}

irr::scene::ISceneManager *Indie::Window::getSceneManager() const
{
	return m_device->getSceneManager();
}