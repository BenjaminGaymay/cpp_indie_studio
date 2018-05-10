/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Camera
*/

#pragma once

#include <irrlicht/irrlicht.h>

namespace Indie {
	class Camera {
	public:
		Camera();
		~Camera();
		void initCamera(irr::scene::ISceneManager *, irr::core::vector3df &);

	private:
		irr::scene::ICameraSceneNode *m_camera;
	};
}