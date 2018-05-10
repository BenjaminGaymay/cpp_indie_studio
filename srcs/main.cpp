//
// EPITECH PROJECT, 2018
// dd
// File description:
// dd
//

#include <irrlicht/irrlicht.h>
#include "Core.hpp"

int main(int ac, char **av)
{
	Indie::Core core;

	core.run();
	// irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL,
	// 	irr::core::dimension2d<irr::u32>(800,600), 32, false, true, false, 0);
	// irr::video::IVideoDriver *driver = device->getVideoDriver();
	// irr::scene::ISceneManager *sceneManager = device->getSceneManager();
	// Indie::Camera camera;
	// // sceneManager->addCameraSceneNode(0, irr::core::vector3d<irr::f32>(0.0f, 0.0f, 0.0f), irr::core::vector3df(5, 0, 0));

	// device->getCursorControl()->setVisible(false);
	// device->setWindowCaption(L"floating");

	// //MODELE
	// irr::scene::IMeshSceneNode *cube = sceneManager->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df(0.0f, 0.0f, 20.0f));
	// cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

	// irr::scene::IAnimatedMeshSceneNode *sydney = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("assets/sydney.md2"));
	// sydney->setMD2Animation(irr::scene::EMAT_STAND);
	// sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// sydney->setMaterialTexture(0, driver->getTexture("assets/sydney.bmp"));
	// sydney->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	// irr::scene::IAnimatedMeshSceneNode *sphere = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("assets/earth.x"));
	// sphere->setPosition(irr::core::vector3df(20,20,20));
	// sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	// sphere->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);



	// irr::core::vector3df pos;
	// camera.initCamera(sceneManager, pos);
	// irr::video::SColor color(255, 255, 255, 255);
	// while (device->run()) {
	// 	driver->beginScene(true, true, color);
	// 	sceneManager->drawAll();
	// 	driver->endScene();
	// }
	// device->drop();
	return 0;
}
