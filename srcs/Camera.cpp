/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** Camera
*/

#include "Camera.hpp"

Indie::Camera::Camera()
{}

Indie::Camera::~Camera()
{}

void Indie::Camera::initCamera(irr::scene::ISceneManager *sceneManager, irr::core::vector3df &pos)
{
	irr::SKeyMap keyMap[5];

	keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = irr::KEY_KEY_Z;
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = irr::KEY_KEY_S;
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = irr::KEY_KEY_Q;
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = irr::KEY_KEY_D;
	keyMap[4].Action = irr::EKA_JUMP_UP;
	keyMap[4].KeyCode = irr::KEY_SPACE;
	m_camera = sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.5f, -1, keyMap, 5);
	m_camera->setPosition(irr::core::vector3df(0, 200, 20));
}