/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** a
*/

#include <irrlicht/irrlicht.h>

int main(int ac, char **av)
{
	irr::IrrlichtDevice *device = irr::createDevice(irr::video::EDT_OPENGL,
		irr::core::dimension2d<irr::u32>(800,600), 32, false, true, false, 0);
	irr::video::IVideoDriver *driver = device->getVideoDriver();
	irr::scene::ISceneManager *sceneManager = device->getSceneManager();

	// sceneManager->addCameraSceneNode(0, irr::core::vector3d<irr::f32>(0.0f, 0.0f, 0.0f), irr::core::vector3df(5, 0, 0));

	device->getCursorControl()->setVisible(false);
	device->setWindowCaption(L"floating");

	irr::scene::IMeshSceneNode *cube = sceneManager->addCubeSceneNode(10.0f, 0, -1, irr::core::vector3df(0.0f, 0.0f, 20.0f));
	cube->setMaterialFlag(irr::video::EMF_WIREFRAME, true);

	//MODELE
	irr::scene::IAnimatedMeshSceneNode *sydney = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("assets/sydney.md2"));
	sydney->setMD2Animation(irr::scene::EMAT_STAND);
	sydney->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sydney->setMaterialTexture(0, driver->getTexture("assets/sydney.bmp"));
	sydney->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);

	irr::scene::IAnimatedMeshSceneNode *sphere = sceneManager->addAnimatedMeshSceneNode(sceneManager->getMesh("assets/earth.x"));
	sphere->setPosition(irr::core::vector3df(20,20,20));
	sphere->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	sphere->setMaterialFlag(irr::video::EMF_FOG_ENABLE, true);



	// CAMERA
	irr::SKeyMap keyMap[5];
	keyMap[0].Action = irr::EKA_MOVE_FORWARD;
	keyMap[0].KeyCode = irr::KEY_KEY_W;
	keyMap[1].Action = irr::EKA_MOVE_BACKWARD;
	keyMap[1].KeyCode = irr::KEY_KEY_S;
	keyMap[2].Action = irr::EKA_STRAFE_LEFT;
	keyMap[2].KeyCode = irr::KEY_KEY_A;
	keyMap[3].Action = irr::EKA_STRAFE_RIGHT;
	keyMap[3].KeyCode = irr::KEY_KEY_D;
	keyMap[4].Action = irr::EKA_JUMP_UP;
	keyMap[4].KeyCode = irr::KEY_SPACE;

	sceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.1f, -1, keyMap, 5);
	irr::video::SColor color(255, 255, 255, 255);
	while (device->run()) {
		driver->beginScene(true, true, color);
		sceneManager->drawAll();
		driver->endScene();
	}
	device->drop();
	return 0;
}