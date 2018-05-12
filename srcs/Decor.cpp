#include "Core.hpp"

/*
** EPITECH PROJECT, 2018
** student
** File description:
** student
*/

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createTexture(const irr::io::path &mesh, const irr::io::path &texture)
{
	irr::scene::IAnimatedMeshSceneNode *object = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh(mesh));
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	object->setMaterialTexture(0, m_core.m_driver->getTexture(texture));
	return object;
}

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createPalmier(irr::core::vector3df position, irr::core::vector3df rotation)
{
	irr::scene::IAnimatedMeshSceneNode *object = createTexture("assets/models/palmier/palmier.obj", "assets/models/palmier/palmier.bmp");
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(irr::core::vector3df(0.01, 0.003, 0.01));
	return object;
}

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createMoon(irr::core::vector3df position, irr::core::vector3df rotation)
{
	irr::scene::IAnimatedMeshSceneNode *object = createTexture("assets/models/moon/moon.obj", "assets/models/moon/moon.png");
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(irr::core::vector3df(16, 16, 16));
	return object;
}

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createSun(irr::core::vector3df position, irr::core::vector3df rotation)
{
	irr::scene::IAnimatedMeshSceneNode *object = createTexture("assets/models/sun/sun.3ds", "assets/models/sun/sun.jpg");
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
	return object;
}

void Indie::Core::createIsland(irr::core::vector3df position, irr::core::vector3df rotation)
{
	irr::scene::IAnimatedMeshSceneNode *object = createTexture("assets/models/island/island.3ds", "assets/models/island/island.jpg");
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
	//object->updateAbsolutePosition();
}

void Indie::Core::createWater(irr::core::vector3df position,  irr::core::vector3df rotation)
{
	(void) position;
	(void) rotation;
	irr::scene::IAnimatedMesh *water = m_core.m_sceneManager->addHillPlaneMesh(
			"waterMesh", irr::core::dimension2d<irr::f32>(50, 50),
			irr::core::dimension2d<irr::u32>(50, 50), 0, 0,
			irr::core::dimension2d<irr::f32>(0, 0),
			irr::core::dimension2d<irr::f32>(30, 30));
	water->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	irr::scene::ISceneNode *node = m_core.m_sceneManager->addWaterSurfaceSceneNode(water->getMesh(0), 5.0f, 500.0f, 50.0f);
	node->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/water/water.jpg"));
	node->setPosition(irr::core::vector3df(15, 15, 0));
}

void Indie::Core::buildDecor()
{
	createWater(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(250, -60, 250), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(-250, -60, -250), irr::core::vector3df(0, 55, 0));
	//createMoon(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	//auto sun = createSun(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
}
