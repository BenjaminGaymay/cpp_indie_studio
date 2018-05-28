/*
** EPITECH PROJECT, 2018
** cpp_indie_studio
** File description:
** EventManager
*/

#include "EventManager.hpp"

Indie::EventManager::EventManager()
{}

Indie::EventManager::~EventManager()
{}

void Indie::EventManager::init(Core &core)
{
	m_core = &core;
}