/*                                                                              
** EPITECH PROJECT, 2018                                                        
** student                                                                             
** File description:                                                            
** student                                                                             
*/

#include "Core.hpp"

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createPalmier(irr::core::vector3df position, irr::core::vector3df rotation)
{
	irr::scene::IAnimatedMeshSceneNode *object = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/palmier/palmier.obj"));
	object->setMD2Animation(irr::scene::EMAT_WAVE);
	object->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	object->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/palmier/palmier.bmp"));
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(irr::core::vector3df(0.01, 0.003, 0.01));
	//object->updateAbsolutePosition();
	return object;
}

void Indie::Core::createIsland(irr::core::vector3df position, irr::core::vector3df rotation)
{
	irr::scene::IAnimatedMeshSceneNode *object = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh("assets/models/island/island.3ds"));
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	object->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/island/island.jpg"));
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(irr::core::vector3df(15, 30, 15));
	object->addChild(createPalmier(irr::core::vector3df(+2, 2, -1), irr::core::vector3df(0, 0, 0)));
	object->addChild(createPalmier(irr::core::vector3df(-4, 2, 1), irr::core::vector3df(0, 0, 0)));
	object->addChild(createPalmier(irr::core::vector3df(-3, 2, -3), irr::core::vector3df(0, 30, 0)));
	object->addChild(createPalmier(irr::core::vector3df(0, 3, -5), irr::core::vector3df(0, 60, 0)));
	object->addChild(createPalmier(irr::core::vector3df(2, 3, -7), irr::core::vector3df(0, 60, 0)));
	object->addChild(createPalmier(irr::core::vector3df(-2, 3, -9), irr::core::vector3df(0, 0, 0)));
	object->addChild(createPalmier(irr::core::vector3df(5, 3, -12), irr::core::vector3df(0, 0, 0)));
	object->updateAbsolutePosition();
}

void Indie::Core::buildDecor()
{
	createIsland(irr::core::vector3df(250, -60, 250), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(-250, -60, -250), irr::core::vector3df(0, 55, 0));
}