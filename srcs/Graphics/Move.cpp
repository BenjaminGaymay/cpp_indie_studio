//
// EPITECH PROJECT, 2018
// student
// File description:
// 12/05/18
//

#include "Core.hpp"

void Indie::Core::moveTexture(irr::scene::IAnimatedMeshSceneNode *node,
							  const irr::core::vector3df &newPosition)
{
	irr::core::vector3df position = node->getPosition();
	irr::core::vector3df rotation = node->getRotation();
	if (position.X < newPosition.X) {
		rotation.Y = 0;
	} else if (position.X > newPosition.X) {
		rotation.Y = 180;
	} else if (position.Z > newPosition.Z) {
		rotation.Y = 90;
	} else if (position.Z < newPosition.Z) {
		rotation.Y = 270;
	} else {
		node->setMD2Animation(irr::scene::EMAT_WAVE);
		return;
	}
	node->setMD2Animation(irr::scene::EMAT_RUN);
	node->setPosition(newPosition);
	node->setRotation(rotation);
}