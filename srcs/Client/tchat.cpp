//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// tchat
//

#include "Core.hpp"

void Indie::Core::manageTchat()
{
	if (m_event.isKeyDown(irr::KEY_ESCAPE)) {
		_tchat._getch = false;
		_tchat._toSend.clear();
		m_event.setKeyUp(irr::KEY_ESCAPE);
	}
	if (m_event.isKeyDown(irr::KEY_RETURN)) {
		m_event.setKeyUp(irr::KEY_RETURN);
		if (!_tchat._toSend.empty())
			dprintf(_socket->getFd(), "1:4:%s", _tchat._toSend.c_str());
		_tchat._toSend.clear();
	}
	if (m_event.isKeyDown(irr::KEY_BACK)) {
		m_event.setKeyUp(irr::KEY_BACK);
		_tchat._toSend.erase(_tchat._toSend.end() - 1);
	}
	for (auto i = 32 ; i < 127 ; i++) {
		if (m_event.isKeyDown(static_cast<irr::EKEY_CODE>(i))) {
			_tchat._toSend += static_cast<char>(i);
			m_event.setKeyUp(static_cast<irr::EKEY_CODE>(i));
		}
	}
}

void Indie::Core::printTchat() const
{
	int y = m_opts.getHeight() - 50;

	if (_tchat._getch) {
		m_core.m_font->draw(irr::core::stringw(">"), irr::core::rect<irr::s32>(50, y + 20, 0, 0), irr::video::SColor(255,255,255,255));
		m_core.m_font->draw(irr::core::stringw(_tchat._toSend.c_str()), irr::core::rect<irr::s32>(70, y + 20, 0, 0), irr::video::SColor(255,255,255,255));
	}
	for (int i = static_cast<int>(_tchat._messages.size()) - 1 ; i >= 0 ; i--) {
		m_core.m_font->draw(irr::core::stringw(_tchat._messages[i].c_str()), irr::core::rect<irr::s32>(50, y, 0, 0), irr::video::SColor(255,255,255,255));
		y -= 20;
	}
}
