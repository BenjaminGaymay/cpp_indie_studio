/*
** EPITECH PROJECT, 2018
** student
** File description:
** 28/05/18
*/

#include <sstream>
#include <iomanip>
#include "Player.hpp"
#include "Core.hpp"

std::string floatToInt(float nb)
{
	std::stringstream ss;
	ss << std::fixed << std::setprecision(10) << nb;
	return ss.str();
}

void Indie::Core::moveEvent(irr::core::vector3df &pos)
{
	irr::core::vector2di pos2d;
	irr::core::vector3df newPos = _playerObjects[0]->move(m_event);

	if (pos.X != newPos.X || pos.Y != newPos.Y || pos.Z != newPos.Z) {
		try {
			pos2d = _mapper->get2dBlock(newPos + _mapper->getSize() / 2);
		} catch (std::logic_error &e) {
			return ;
		}
		_socket->sendInfos(Indie::PLAYER, Indie::MOVE,
					std::to_string(_playerObjects[0]->getId()) + ':' +
					std::to_string(pos2d.X) + ':' +
					std::to_string(pos2d.Y) + ':' +
					floatToInt(newPos.X) + ':' +
					floatToInt(newPos.Y) + ':' +
					floatToInt(newPos.Z) + ':' +
					std::to_string(_playerObjects[0]->getRotation().Y) + ':' +
					std::to_string(_playerObjects[0]->getWallUp()));
	}
}

void Indie::Core::dropBombEvent(irr::core::vector3df &pos)
{
	if (!m_event.isKeyDown(irr::KEY_KEY_B))
		return ;
	m_event.setKeyUp(irr::KEY_KEY_B);
	irr::core::vector2di pos2d = _mapper->get2dBlock(pos + _mapper->getSize() / 2);
	_socket->sendInfos(Indie::BOMB, Indie::CREATEBOMB,
					   std::to_string(_playerObjects[0]->getId()) + ':' +
					   std::to_string(pos2d.X) + ':' +
					   std::to_string(pos2d.Y) + ':' +
					   std::to_string(pos.X) + ':' +
					   std::to_string(pos.Y) + ':' +
					   std::to_string(pos.Z) + ':' +
					   std::to_string(_playerObjects[0]->getPower()) + ':' +
					   std::to_string(_playerObjects[0]->getBombNumber()));
}