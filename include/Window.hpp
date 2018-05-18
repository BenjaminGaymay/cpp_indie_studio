/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Window
*/

#pragma once

#include <irrlicht/irrlicht.h>
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
		Camera getCamera() const;
		irr::core::vector3df getCameraPosition() const;

	public:
		irr::IrrlichtDevice *m_device;
		irr::video::IVideoDriver *m_driver;
		irr::scene::ISceneManager *m_sceneManager;

	private:
		Camera m_camera;
	};
}