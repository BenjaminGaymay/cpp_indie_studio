#include <Player.hpp>
#include <iostream>

/*
** EPITECH PROJECT, 2018
** student
** File description:
** 14/05/18
*/

#include <iostream>
#include "Core.hpp"

void Indie::Core::setCollision(irr::scene::ISceneNode *wall,
							irr::scene::ISceneNode *target)
{
	irr::scene::IMetaTriangleSelector *metaSelector = m_core.m_sceneManager->createMetaTriangleSelector();
	irr::scene::ITriangleSelector *selector = 0;
	selector = m_core.m_sceneManager->createTriangleSelectorFromBoundingBox(wall);
	wall->setTriangleSelector(selector);
	metaSelector->addTriangleSelector(selector);

	const irr::core::aabbox3d<irr::f32>& box = target->getBoundingBox();
	irr::core::vector3df radius = box.getCenter();

	irr::scene::ISceneNodeAnimatorCollisionResponse *anim = m_core.m_sceneManager->createCollisionResponseAnimator(
			metaSelector, target, (radius),
			irr::core::vector3df(0.0f, 0.0f, 0.0f));
	target->addAnimator(anim);
	anim->drop();
}