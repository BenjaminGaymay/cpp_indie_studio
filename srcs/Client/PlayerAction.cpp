/*
** EPITECH PROJECT, 2018
** student
** File description:
** 28/05/18
*/

#include "Player.hpp"
#include "Core.hpp"

void Indie::Core::moveEvent(irr::core::vector3df &pos)
{
	irr::core::vector3df newPos = _playerObjects[0]->move(m_event);

	if (pos.X != newPos.X || pos.Y != newPos.Y || pos.Z != newPos.Z) {
		irr::core::vector2di pos2d = _mapper->get2dBlock(newPos + _mapper->getSize() / 2);
		_socket->sendInfos(Indie::PLAYER, Indie::MOVE,
						   std::to_string(_playerObjects[0]->getId()) + ':' +
						   std::to_string(pos2d.X) + ':' +
						   std::to_string(pos2d.Y) + ':' +
						   std::to_string(newPos.X) + ':' +
						   std::to_string(newPos.Y) + ':' +
						   std::to_string(newPos.Z) + ':' +
						   std::to_string(_playerObjects[0]->getRotation().Y));
	}
}

void Indie::Core::dropBombEvent(irr::core::vector3df &pos)
{
	if (!m_event.isKeyDown(irr::KEY_SPACE))
		return ;
	irr::core::vector2di pos2d = _mapper->get2dBlock(pos + _mapper->getSize() / 2);

	_socket->sendInfos(Indie::PLAYER, Indie::DROPBOMB,
					   std::to_string(_playerObjects[0]->getId()) + ':' +
					   std::to_string(pos2d.X) + ':' +
					   std::to_string(pos2d.Y) + ':' +
					   std::to_string(pos.X) + ':' +
					   std::to_string(pos.Y) + ':' +
					   std::to_string(pos.Z) + ':' +
					   std::to_string(_playerObjects[0]->getPower() + ':'));
}