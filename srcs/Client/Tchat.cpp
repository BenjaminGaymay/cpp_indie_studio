//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// tchat
//

#include "Core.hpp"

void Indie::Core::manageTchat()
{
	auto tmp = _tchat._textBox->getText();

	if (m_event.isKeyDown(irr::KEY_ESCAPE)) {
		_tchat._getch = false;
		_tchat._textBox->setVisible(false);
		_tchat._textBox->setText(L"");
		m_event.setKeyUp(irr::KEY_ESCAPE);
	}
	if (m_event.isKeyDown(irr::KEY_RETURN)) {
		_tchat._getch = true;
		m_event.setKeyUp(irr::KEY_RETURN);
		if (wcslen(tmp) != 0)
			dprintf(_socket->getFd(), "1:4:%ls", tmp);
		_tchat._textBox->setText(L"");
	}
}

void Indie::Core::printTchat()
{
	int y = m_opts.getHeight() - 80;

	for (int i = static_cast<int>(_tchat._messages.size()) - 1 ; i >= 0 ; i--) {
		if (_tchat._messages[i]._clock.getElapsedTime() > 7500)
			_tchat._messages.erase(_tchat._messages.begin() + i);
	}

	for (int i = static_cast<int>(_tchat._messages.size()) - 1 ; i >= 0 ; i--) {
		m_core.m_font->draw(irr::core::stringw(_tchat._messages[i]._string.c_str()), irr::core::rect<irr::s32>(50, y, 0, 0), irr::video::SColor(255,255,255,255));
		y -= 30;
	}
}

