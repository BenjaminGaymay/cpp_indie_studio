//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// PlayerActions
//

#include "Core.hpp"
#include "Player.hpp"

void Indie::Core::comPlayer(const ObjectsEvents &event, std::vector<std::string> &infos)
{
	try {
		auto id = std::stoi(infos[0]);

		switch (event) {
			case STAND: standPlayer(id); break;
			case DEAD: removePlayer(id, DEAD); break;
			case SUICIDE: removePlayer(id, SUICIDE); break;
			case APPEAR: addPlayer(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2]))); break;
			case MOVE: movePlayer(id, irr::core::vector2di(stoi(infos[1]), std::stoi(infos[2])), irr::core::vector3df(std::stof(infos[3]), std::stof(infos[4]), std::stof(infos[5])), std::stof(infos[6])); break;
			default: break;
		}
	} catch (const std::exception &e) {}
}

void Indie::Core::standPlayer(int id)
{
	for (auto &p : _playerObjects)
		if (p->getId() == id && p->isAlive()) {
			if (!p->isStanding())
				p->getPlayer()->setMD2Animation(irr::scene::EMAT_STAND);
			p->setStanding(true);
			return;
		}
}

void Indie::Core::addPlayer(int id, const irr::core::vector2di &pos2d)
{
	auto pos3d = _mapper->get3dBlock(pos2d)->getPosition();

	std::cout << pos3d.X << ":" << pos3d.Y << ":" << pos3d.Z << std::endl;
	std::unique_ptr<Player> newPlayer = std::make_unique<Player>(id, static_cast<irr::scene::IAnimatedMeshSceneNode *>(_graphism->createTexture(*_graphism->getTexture(10), pos3d, {0, 0, 0}, {2, 2, 2}, true)), _chat);
	_graphism->resizeNode(newPlayer->getPlayer(), _mapper->getSize());
	newPlayer->setSpeed(1);
	newPlayer->setPos2d(pos2d);
	_playerObjects.push_back(std::move(newPlayer));
}

void Indie::Core::removePlayer(int id, const ObjectsEvents &event)
{
	if (id == _playerObjects[0]->getId()) {
		if (event == SUICIDE) {
			auto sound = _engine->play2D("music/suicide.wav", false, false, true);
			sound->setVolume(2);
		}
		_playerObjects[0]->getPlayer()->remove();
		_playerObjects[0]->setPlayer(nullptr);
		_playerObjects[0]->setAlive(false);
		m_state = SPEC;
		return;
	}
	for (auto &p : _playerObjects) {
		if (p->getId() == id) {
			p->getPlayer()->remove();
			p->setPlayer(nullptr);
			auto pPos = std::find(_playerObjects.begin(), _playerObjects.end(), p);
			pPos->reset();
			_playerObjects.erase(pPos);
			return;
		}
	}
}

void Indie::Core::movePlayer(int id, const irr::core::vector2di &pos2d, const irr::core::vector3df &pos, const irr::f32 &rota)
{
	for (auto &p : _playerObjects)
		if (p->getId() == id && p->isAlive()) {
			if (p->isStanding())
				p->getPlayer()->setMD2Animation(irr::scene::EMAT_RUN);
			p->setStanding(false);
			p->getPlayer()->setRotation({0, rota, 0});
			p->setPosition(pos);
			p->setPos2d(pos2d);
			return;
		}
}
