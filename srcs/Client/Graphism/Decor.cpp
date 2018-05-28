//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Decor
//

#include "Graphism.hpp"

//
// @brief create texture
// @param textures 1: obj texture 2: material texture
// @param position
// @param rotation
// @param scale 2: size
// @param collision must me true for dynamic object (player)
// @return
//
irr::scene::ISceneNode *Indie::Graphism::createTexture(const textureElem &textures, const irr::core::vector3df &position,
															   const irr::core::vector3df &rotation, const irr::core::vector3df &scale,
															   bool collision)
{
	auto object = m_core->m_sceneManager->addAnimatedMeshSceneNode(m_core->m_sceneManager->getMesh(textures.first));
	object->setName(textures.first);
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	if (!textures.second.empty())
		object->setMaterialTexture(0, m_core->m_driver->getTexture(textures.second));
	else {
		object->setName("");
		object->setVisible(false);
	}
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(scale);
	//object->setDebugDataVisible(irr::scene::E_DEBUG_SCENE_TYPE::EDS_BBOX);
	(void) collision;
	/*if (collision)
		addCollision(object);*/
	_nodesList.push_back(object);
	return object;
}

//
// @brief create one island
// @param position
// @param rotation
// @return
//
irr::scene::ISceneNode *Indie::Graphism::createIsland(irr::core::vector3df position, irr::core::vector3df rotation)
{
	auto object = createTexture(_texturesMap[51], position, rotation, {15, 30, 15}, false);
	irr::core::vector3df scale = {0.01, 0.003, 0.01};

	object->addChild(createTexture(_texturesMap[50], {+2, 2, -1}, {0, 0, 0}, scale, false));
	object->addChild(createTexture(_texturesMap[50], {-4, 2, 1}, {0, 0, 0}, scale, false));
	object->addChild(createTexture(_texturesMap[50], {-3, 2, -3}, {0, 30, 0}, scale, false));
	object->addChild(createTexture(_texturesMap[50], {0, 3, -5}, {0, 60, 0}, scale, false));
	object->addChild(createTexture(_texturesMap[50], {2, 3, -7}, {0, 60, 0}, scale, false));
	object->addChild(createTexture(_texturesMap[50], {-2, 3, -9}, {0, 0, 0}, scale, false));
	object->addChild(createTexture(_texturesMap[50], {5, 3, -12}, {0, 0, 0}, scale, false));
	object->setName("Island");
	return object;
}

//
// @brief create the water under the map
// @param position
// @param rotation
//
void Indie::Graphism::createWater(irr::core::vector3df position,  irr::core::vector3df rotation)
{
	(void) position;
	(void) rotation;
	irr::scene::IAnimatedMesh *water = m_core->m_sceneManager->addHillPlaneMesh(
			"waterMesh", irr::core::dimension2d<irr::f32>(25, 25),
			irr::core::dimension2d<irr::u32>(50, 50), 0, 0,
			irr::core::dimension2d<irr::f32>(0, 0),
			irr::core::dimension2d<irr::f32>(30, 30));
	irr::scene::ISceneNode *node = m_core->m_sceneManager->addWaterSurfaceSceneNode(water->getMesh(0), 2.0f, 800.0f, 100.0f);
	node->setMaterialTexture(0, m_core->m_driver->getTexture("assets/models/water/water_tiny.png"));
	node->setPosition(irr::core::vector3df(15, 15, 0));
	node->setName("Water");
}

//
// @brief build decor
//
void Indie::Graphism::buildDecor()
{
//	createArena();
	createWater(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(450, -60, 250), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(-350, -60, -350), irr::core::vector3df(0, 55, 0));
	//createMoon(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	//auto sun = createSun(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	//object->getMaterial(0).setTexture(0, m_core.m_driver->getTexture("lol/rope.png"););
	//object->getMaterial(0).setTexture(0, m_core.m_driver->getTexture("lol/rope.png"););
}

//
// @brief Database of textures
//
void Indie::Graphism::generateTextureMap()
{
	_texturesMap[0] = textureElem("assets/models/cube/Crate1.3ds", "");
	_texturesMap[1] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/crate.jpg");
	_texturesMap[2] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/sand.jpg");
	_texturesMap[3] = textureElem("assets/models/bomb/Bomb.obj", "assets/models/bomb/Albedo.png");
	_texturesMap[4] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/red.png");
	_texturesMap[10] = textureElem("assets/models/sydney.md2", "assets/models/sydney.bmp");
	_texturesMap[50] = textureElem("assets/models/palmier/palmier.obj", "assets/models/palmier/palmier.bmp");
	_texturesMap[51] = textureElem("assets/models/island/island.3ds", "assets/models/island/island.jpg");
}