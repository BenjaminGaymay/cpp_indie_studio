/*
** EPITECH PROJECT, 2018
** student
** File description:
** 13/05/18
*/

#include "Player.hpp"

/**
 * @brief texture of the player
 * @param node
 */
Indie::Player::Player(irr::scene::IAnimatedMeshSceneNode *node)
: _stand(true), _player(node), _speed(0.5f), _id(-1)
{
	_player->setMD2Animation(irr::scene::EMAT_STAND);
}

Indie::Player::Player(int id, irr::scene::IAnimatedMeshSceneNode *node)
: _stand(true), _player(node), _speed(0.5f), _id(id)
{
	_player->setMD2Animation(irr::scene::EMAT_STAND);
}

/**
 * @brief destroy
 */
Indie::Player::~Player() = default;

/**
 * @brief For 2D movement, in FPS mode, key must be updated
 * @param event
 * @param now
 * @param then
 */
irr::core::vector3df Indie::Player::move(const Events &event)
{
	irr::core::vector3df lastP = _player->getPosition();
	irr::core::vector3df lastR = _player->getRotation();
	irr::core::vector3df nodePosition = _player->getPosition();

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
	return nodePosition;
	// rotationWithMove(_player, nodePosition);
	// _player->setPosition(nodePosition);
	/*if (!_player->()) {
		_player->setPosition(lastP);
		_player->setRotation(lastR);
		_player->setMD2Animation(irr::scene::EMAT_STAND);
		setStanding(true);
		return ;
	}*/
}

/**
 * @brief change rotation of player when moving
 * @param node
 * @param newPosition
 */
void Indie::Player::rotationWithMove(irr::scene::IAnimatedMeshSceneNode *node,
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

/**
 * @brief return player object
 * @return IAnimatedMeshSceneNode
 */
irr::scene::IAnimatedMeshSceneNode *Indie::Player::getPlayer()
{
	return _player;
}

/**
 * @brief return if the player is doing action like running
 * @return bool
 */
bool Indie::Player::isStanding()
{
	return _stand;
}

/**
 * @brief change state
 * @param state
 */
void Indie::Player::setStanding(bool state)
{
	_stand = state;
}