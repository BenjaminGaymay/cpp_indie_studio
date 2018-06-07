//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#include "Graphism.hpp"

Indie::Graphism::Graphism(Indie::Window *core) :
	m_core(core)
{
	generateTextureMap();
}

Indie::Graphism::~Graphism()
{}

irr::f32 Indie::Graphism::resizeNode(irr::scene::ISceneNode *node, const float &size)
{
	irr::f32 cubeSize = (node->getBoundingBox().getExtent().Z) * node->getScale().Z;

	if (cubeSize != size)
		node->setScale({size / cubeSize, size / cubeSize, size / cubeSize});
	cubeSize = (node->getBoundingBox().getExtent().Z) * node->getScale().Z;
	return cubeSize;
}

const Indie::Graphism::textureElem *Indie::Graphism::getTexture(const int &nb)
{
	if (_texturesMap.find(nb) != _texturesMap.end())
		return &_texturesMap[nb];
	return nullptr;

}

void Indie::Graphism::clearNode()
{
	if (_decors.empty())
		return ;
	for (auto &node : _decors)
		node->remove();
	_decors.clear();
}