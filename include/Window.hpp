//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Window
//

#pragma once

#include <memory>
#include "Camera.hpp"
#include "Events.hpp"
#include "Options.hpp"

namespace Indie {
	class Window {
	public:
		Window();
		~Window();
		void initWindow(Events &, const Options &);
		irr::video::IVideoDriver *getDriver() const;
		irr::scene::ISceneManager *getSceneManager() const;
		irr::gui::IGUIEnvironment *getGuiEnv() const;
		Camera getCamera() const;
		irr::core::vector3df getCameraPosition() const;
		void editMapView();

	public:
		irr::IrrlichtDevice *m_device;
		irr::video::IVideoDriver *m_driver;
		irr::scene::ISceneManager *m_sceneManager;
		irr::gui::IGUIEnvironment *m_gui;
		irr::gui::IGUIFont *m_font;

	private:
		Camera m_camera;
	};
}