//
// EPITECH PROJECT, 2018
// student
// File description:
// 13/05/18
//

#include "Player.hpp"

//
// @brief texture of the player
// @param node
//
Indie::Player::Player(const int &id, irr::scene::IAnimatedMeshSceneNode *node, s_tchat &tchat)
: _id(id), _stand(true), _player(node),
  _speed(1.5f), _tchat(tchat), _power(1), _bombNumber(1), _wallUp(false), _alive(true)
{
	_player->setMD2Animation(irr::scene::EMAT_STAND);
}

//
// @brief destroy
//
Indie::Player::~Player() = default;

//
// @brief set the futur position of player
// @param event
// @return
//
irr::core::vector3df Indie::Player::move(Events &event)
{
	irr::core::vector3df nodePosition = _player->getPosition();

	if (_tchat._getch)
		return nodePosition;
	if (event.isKeyDown(irr::KEY_KEY_Q)) {
		if (isStanding()) _player->setMD2Animation(irr::scene::EMAT_RUN);
		setStanding(false);
		nodePosition.Z += _speed;
	} else if(event.isKeyDown(irr::KEY_KEY_D)) {
		if (isStanding()) _player->setMD2Animation(irr::scene::EMAT_RUN);
		setStanding(false);
		nodePosition.Z -= _speed;
	} else if(event.isKeyDown(irr::KEY_KEY_S)) {
		if (isStanding()) _player->setMD2Animation(irr::scene::EMAT_RUN);
		setStanding(false);
		nodePosition.X -= _speed;
	} else if(event.isKeyDown(irr::KEY_KEY_Z)) {
		if (isStanding()) _player->setMD2Animation(irr::scene::EMAT_RUN);
		setStanding(false);
		nodePosition.X += _speed;
	} else {
		if (!isStanding()) _player->setMD2Animation(irr::scene::EMAT_STAND);
		setStanding(true);
	}
	rotationWithMove(_player, nodePosition);
	return nodePosition;
}

//
// @brief change rotation of player when moving
// @param node
// @param newPosition
//
void Indie::Player::rotationWithMove(irr::scene::ISceneNode *node,
					const irr::core::vector3df &newPosition)
{
	irr::core::vector3df position = node->getPosition();
	irr::core::vector3df rotation = node->getRotation();
	if (position.X < newPosition.X)
		rotation.Y = 0;
	else if (position.X > newPosition.X)
		rotation.Y = 180;
	else if (position.Z > newPosition.Z)
		rotation.Y = 90;
	else if (position.Z < newPosition.Z)
		rotation.Y = 270;
	else
		return;
	node->setRotation(rotation);
}