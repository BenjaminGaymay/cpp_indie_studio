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

namespace Indie {
	class Window {
	public:
		Window();
		~Window();
		void initWindow();
		std::unique_ptr<irr::IrrlichtDevice> getDevice() const;
		std::unique_ptr<irr::video::IVideoDriver> getDriver() const;
		std::unique_ptr<irr::scene::ISceneManager> getSceneManager() const;
		irr::IrrlichtDevice *m_device;
		irr::video::IVideoDriver *m_driver;
		irr::scene::ISceneManager *m_sceneManager;

	private:
		Camera m_camera;
	};
}