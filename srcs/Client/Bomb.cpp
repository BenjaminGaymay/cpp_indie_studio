//
// EPITECH PROJECT, 2018
// student
// File description:
// 14/05/18
//

#include "Bomb.hpp"

/* std::vector<Bomb> bombs;
if (m_event.isKeyDown(irr::KEY_SPACE)) {
				Indie::Bomb bomb(2, 10);
				bomb.setTexture(_graphism->createTexture(*_graphism->getTexture(3), _playerObjects[0]->getPosition(), {0, 0, 0}, {100, 100, 100}, false));
				bombs.push_back(bomb);
 			}
 			bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](Indie::Bomb &row) {return row.boom();}), bombs.end());*/

bool Indie::Bomb::tictac()
{
	if (!_state && std::time(nullptr) >= _timeMax)
		_state = BOOM;
	return _state;
}