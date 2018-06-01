//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Camera
//

#pragma once

#include <irrlicht.h>
#include <vector>

namespace Indie {
	class Camera {
	public:
		enum Mode {
			FPS,
			BASIC
		};
		Camera();
		~Camera();
		void initCamera(irr::scene::ISceneManager *, irr::core::vector3df &);
		void change(irr::scene::ISceneManager *);
		void change(irr::scene::ISceneManager *sceneManager, Camera::Mode);
		void reset();
		Mode getMode() const;

	public:
		std::vector<irr::scene::ICameraSceneNode *> m_cameras;

	private:
		irr::SKeyMap m_keyMap[5];
		irr::scene::ISceneManager *m_sceneManager;
		Mode m_mode;
	};
}