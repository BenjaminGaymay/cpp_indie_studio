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
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false); // remove fog
	object->setMaterialFlag(irr::video::EMF_LIGHTING, true); // maybe map will be black
	if (!textures.second.empty() && textures.second != ".") {
		object->setMaterialTexture(0, m_core->m_driver->getTexture(textures.second));
	} else if (textures.second.empty()){
		object->setName("");
		object->setVisible(false);
	}
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(scale);
	//object->setDebugDataVisible(irr::scene::E_DEBUG_SCENE_TYPE::EDS_BBOX);
	(void) collision;
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
	/*createWater(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	createTexture(_texturesMap[52], {0, 0, 0}, {0, 0, 0}, {1, 1, 1}, false);*/
	//createTexture(_texturesMap[51], {300, 0, 0}, {0, 0, 0}, {0.1f, 0.1f, 0.1f}, false);
	_decors.push_back(createTexture(_texturesMap[52], {2000, -200, -600}, {270, 0, 0}, {50, 50, 50}, false));
}

//
// @brief Database of textures
//
void Indie::Graphism::generateTextureMap()
{
	_texturesMap[0] = textureElem("assets/models/cube/Crate1.3ds", ""); //invisible block
	_texturesMap[1] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/crate.jpg"); //basic block
	_texturesMap[2] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/sand.jpg"); //undermap block
	_texturesMap[3] = textureElem("assets/models/bomb/Bomb.obj", "assets/models/bomb/Albedo.png");
	_texturesMap[4] = textureElem("assets/models/lightning.md2", "assets/models/2D/yellow.png"); //SPEEDUP
	_texturesMap[5] = textureElem("assets/models/bombsBonus.3ds", "."); //BOMBUP
	_texturesMap[6] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/power.png"); //FIREUP
	_texturesMap[7] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/ghost.jpg"); //WALLPASSUP
	_texturesMap[8] = textureElem("assets/models/cube/Crate1.3ds", "assets/models/2D/wall.png"); //wall block
	_texturesMap[10] = textureElem("assets/models/sydney.md2", "assets/models/sydney.bmp");
	_texturesMap[50] = textureElem("assets/models/palmier/palmier.obj", "assets/models/palmier/palmier.bmp");
	//_texturesMap[51] = textureElem("lol/city/3DS/Camellia City.3ds", ".");
	_texturesMap[52] = textureElem("assets/models/Circuit/Luigi Circuit.obj", ".");
}