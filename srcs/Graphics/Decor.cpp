

#include "Core.hpp"

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createTexture(const textureElem &textures, const irr::core::vector3df &position, const irr::core::vector3df &rotation, const irr::core::vector3df &scale, bool collision)
{
	auto object = m_core.m_sceneManager->addAnimatedMeshSceneNode(m_core.m_sceneManager->getMesh(textures.first));
	object->setMaterialFlag(irr::video::EMF_FOG_ENABLE, false);
	object->setMaterialTexture(0, m_core.m_driver->getTexture(textures.second));
	object->setPosition(position);
	object->setRotation(rotation);
	object->setScale(scale);
	object->setName(textures.first);
	if (collision)
		for (auto &node : _nodesList)
			setCollision(node, object);
	_nodesList.push_back(object);
	return object;
}

void Indie::Core::createArena()
{
	auto arena = createTexture(_texturesMap[1], {0, 0, 0}, {0, 0, 0}, {21, 1, 22}, false);
	auto cubeSize = arena->getBoundingBox().getExtent().X;
	arena->setPosition({0, 100 - cubeSize, 0});
}

/*irr::scene::IAnimatedMeshSceneNode *Indie::Core::createMoon(irr::core::vector3df position, irr::core::vector3df rotation)
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
}*/

irr::scene::IAnimatedMeshSceneNode *Indie::Core::createIsland(irr::core::vector3df position, irr::core::vector3df rotation)
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

void Indie::Core::createWater(irr::core::vector3df position,  irr::core::vector3df rotation)
{
	(void) position;
	(void) rotation;
	irr::scene::IAnimatedMesh *water = m_core.m_sceneManager->addHillPlaneMesh(
			"waterMesh", irr::core::dimension2d<irr::f32>(25, 25),
			irr::core::dimension2d<irr::u32>(50, 50), 0, 0,
			irr::core::dimension2d<irr::f32>(0, 0),
			irr::core::dimension2d<irr::f32>(30, 30));
	irr::scene::ISceneNode *node = m_core.m_sceneManager->addWaterSurfaceSceneNode(water->getMesh(0), 2.0f, 800.0f, 100.0f);
	node->setMaterialTexture(0, m_core.m_driver->getTexture("assets/models/water/water_tiny.png"));
	node->setPosition(irr::core::vector3df(15, 15, 0));
	node->setName("Water");
}

void Indie::Core::buildDecor()
{
	createArena();
	createWater(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(250, -60, 250), irr::core::vector3df(0, 0, 0));
	createIsland(irr::core::vector3df(-250, -60, -250), irr::core::vector3df(0, 55, 0));
	createTexture(_texturesMap[52], {400, -10, 400}, {0, 0, 0}, {4, 4, 4}, false);
	//createMoon(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	//auto sun = createSun(irr::core::vector3df(0, 0, 0), irr::core::vector3df(0, 0, 0));
	//object->getMaterial(0).setTexture(0, m_core.m_driver->getTexture("lol/rope.png"););
	//object->getMaterial(0).setTexture(0, m_core.m_driver->getTexture("lol/rope.png"););
}

void Indie::Core::generateTextureMap()
{
	_texturesMap[0] = textureElem("assets/models/cube.md2", "assets/models/2D/crate.jpg");
	_texturesMap[1] = textureElem("assets/models/cube.md2", "assets/models/2D/sand.jpg");
	_texturesMap[10] = textureElem("assets/models/sydney.md2", "assets/models/sydney.bmp");
	_texturesMap[50] = textureElem("assets/models/palmier/palmier.obj", "assets/models/palmier/palmier.bmp");
	_texturesMap[51] = textureElem("assets/models/island/island.3ds", "assets/models/island/island.jpg");
	_texturesMap[52] = textureElem("assets/models/vehicules/boat.obj", "assets/models/vehicules/boat.tga");
}