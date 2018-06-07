//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#include "Window.hpp"

Indie::Window::Window()
{}

Indie::Window::~Window()
{}

void Indie::Window::editMapView()
{
	irr::core::vector3df vec = {0, 450, 100};

	m_camera.initCamera(m_sceneManager, vec);
}

void Indie::Window::initWindow(Events &evt, const Options &opt)
{
	irr::core::vector3df vec(50, 50, 50);
	irr::core::dimension2d<irr::u32> dimension(opt.getWidth(), opt.getHeight());

	m_device = irr::createDevice(irr::video::EDT_OPENGL, dimension, 64, opt.getFullScreen(), true, false, &evt);
	m_driver = m_device->getVideoDriver();
	m_sceneManager = m_device->getSceneManager();
	m_device->getCursorControl()->setVisible(false);
	m_device->setWindowCaption(L"floating");
	m_gui = m_device->getGUIEnvironment();
	m_camera.initCamera(m_sceneManager, vec);
	m_font = m_device->getGUIEnvironment()->getFont("assets/fonts/font.xml");
}

irr::video::IVideoDriver *Indie::Window::getDriver() const
{
	return m_device->getVideoDriver();
}

irr::scene::ISceneManager *Indie::Window::getSceneManager() const
{
	return m_device->getSceneManager();
}

Indie::Camera Indie::Window::getCamera() const
{
	return m_camera;
}

irr::gui::IGUIEnvironment *Indie::Window::getGuiEnv() const
{
	return m_device->getGUIEnvironment();
}

irr::core::vector3df Indie::Window::getCameraPosition() const
{
	return m_camera.m_cameras[m_camera.getMode()]->getPosition();
}