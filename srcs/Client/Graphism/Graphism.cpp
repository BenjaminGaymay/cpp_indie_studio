//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Core
//

#include "Graphism.hpp"

Indie::Graphism::Graphism(Indie::Window *core)
: m_core(core)
{
	generateTextureMap();
	//buildDecor();
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
	std::cerr << "size:" <<_nodesList.size() << std::endl;
	if (_nodesList.empty())
		return ;
	/*for (auto &node : _nodesList)
		node->remove();*/
	_nodesList.clear();
	std::cerr << "size:" <<_nodesList.size() << std::endl;
}