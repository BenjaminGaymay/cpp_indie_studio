//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// SplashScreen
//

#include "SplashScreen.hpp"

Indie::SplashScreen::SplashScreen()
{}

Indie::SplashScreen::~SplashScreen()
{}

bool Indie::SplashScreen::fadeIn()
{
	irr::core::dimension2di imgSize = {713 - 68, 381 - 223};
	int w = m_driver->getScreenSize().Width;
	int h = m_driver->getScreenSize().Height;

	m_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	m_driver->draw2DImage(m_texture, irr::core::position2d<irr::s32>(w / 2 - imgSize.Width / 2, h / 2 - imgSize.Height / 2),
		irr::core::recti(86,223,700,381), 0,
		irr::video::SColor(255, 255, 255, 255), true);
	m_gui->drawAll();
	m_driver->endScene();
	return true;
}

bool Indie::SplashScreen::fadeOut()
{
	irr::core::dimension2di imgSize = {713 - 68, 381 - 223};
	int w = m_driver->getScreenSize().Width;
	int h = m_driver->getScreenSize().Height;

	m_driver->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
	m_driver->draw2DImage(m_texture, irr::core::position2d<irr::s32>(w / 2 - imgSize.Width / 2, h / 2 - imgSize.Height / 2),
		irr::core::recti(86,223,700,381), 0,
		irr::video::SColor(255, 255, 255, 255), true);
	m_gui->drawAll();
	m_driver->endScene();
	if (m_clock.getElapsedTime() >= 2)
		return false;
	return true;
}

void Indie::SplashScreen::display(irr::IrrlichtDevice *device, Events &event)
{
	m_gui = device->getGUIEnvironment();
	m_fader = m_gui->addInOutFader();
	m_driver = device->getVideoDriver();
	m_texture = m_driver->getTexture("assets/models/menu/splashscreen.png");

	m_fader->setColor(irr::video::SColor(0, 0, 0, 0));
	m_fader->fadeIn(2000);
	m_fader->isReady();

	while (device->run()) {
		if (event.isKeyDown(irr::KEY_SPACE) or
			event.isKeyDown(irr::KEY_RETURN))
			break;
		fadeIn();
		if (m_clock.getElapsedTime() >= 4000) {
			m_fader->fadeOut(2000);
			m_fader->isReady();
			m_clock.reset();
			while (device->run()) {
				if (event.isKeyDown(irr::KEY_SPACE) or
					event.isKeyDown(irr::KEY_RETURN)) {
					m_fader->fadeIn(0);
					break;
				}
				if (!fadeOut())
					break;
				}
			break;
		}
	}
	m_fader->fadeIn(0);
}