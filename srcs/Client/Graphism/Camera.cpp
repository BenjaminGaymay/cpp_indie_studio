//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Camera
//

#include "Camera.hpp"

Indie::Camera::Camera()
{
	m_keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	m_keyMap[0].KeyCode = irr::KEY_UP;
	m_keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
	m_keyMap[1].KeyCode = irr::KEY_DOWN;
	m_keyMap[2].Action = irr::EKA_STRAFE_LEFT;
	m_keyMap[2].KeyCode = irr::KEY_LEFT;
	m_keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
	m_keyMap[3].KeyCode = irr::KEY_RIGHT;
  	m_mode = BASIC;
}

Indie::Camera::~Camera()
{}

void Indie::Camera::initCamera(irr::scene::ISceneManager *sceneManager, irr::core::vector3df &pos)
{
	m_cameras.resize(2);
	m_cameras[FPS] = sceneManager->addCameraSceneNodeFPS(nullptr, 100, 0.5, -1, m_keyMap, 4);
	m_cameras[FPS]->setPosition({0, 500, 0});
	m_cameras[FPS]->setRotation({0, 90, 0});

	m_cameras[BASIC] = sceneManager->addCameraSceneNode();
	m_cameras[BASIC]->setPosition(pos);
	m_cameras[BASIC]->setRotation(irr::core::vector3df(0, 20, 0));
}

void Indie::Camera::change(irr::scene::ISceneManager *sceneManager)
{
	if (m_mode == BASIC) {
		m_mode = FPS;
		sceneManager->setActiveCamera(m_cameras[m_mode]);
	} else {
		m_mode = BASIC;
		sceneManager->setActiveCamera(m_cameras[m_mode]);
	}
}

void Indie::Camera::change(irr::scene::ISceneManager *sceneManager, Indie::Camera::Mode mode)
{
	m_mode = mode;
	sceneManager->setActiveCamera(m_cameras[m_mode]);
}

Indie::Camera::Mode Indie::Camera::getMode() const
{
	return m_mode;
}