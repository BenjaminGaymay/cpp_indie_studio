//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// tchat
//

#include "Core.hpp"

void Indie::Chat::manageTchat(Events &m_event, std::unique_ptr<Socket> &socket)
{
	auto tmp = _textBox->getText();

	if (m_event.isKeyDown(irr::KEY_ESCAPE)) {
		m_event.setKeyUp(irr::KEY_ESCAPE);
		_getch = false;
		_textBox->setVisible(false);
		_textBox->setText(L"");
	}
	if (m_event.isKeyDown(irr::KEY_RETURN)) {
		m_event.setKeyUp(irr::KEY_RETURN);
		_getch = true;
		if (wcslen(tmp) != 0)
			dprintf(socket->getFd(), "1:4:%ls\n", tmp);
		_textBox->setText(L"");
	}
}

void Indie::Chat::printTchat(Window &m_core, Options &m_opts)
{
	int y = m_opts.getHeight() - 80;

	for (int i = static_cast<int>(_messages.size()) - 1 ; i >= 0 ; i--) {
		if (_messages[i]._clock.getElapsedTime() > 5000)
			_messages.erase(_messages.begin() + i);
	}

	for (int i = static_cast<int>(_messages.size()) - 1 ; i >= 0 ; i--) {
		m_core.m_font->draw(irr::core::stringw(_messages[i]._string.c_str()), irr::core::rect<irr::s32>(50, y, 0, 0), irr::video::SColor(255,255,255,255));
		y -= 30;
	}
}

void Indie::Core::serverMessage(const std::vector<std::string> &message)
{
	std::string msg;

	for (auto &line : message)
		msg += line + ":";
	msg[msg.size() - 1] = '\0';
	_chat._messages.push_back({msg, Clock()});

	if (_chat._messages.size() > 20)
	 	_chat._messages.erase(_chat._messages.begin(), _chat._messages.end() - 20);
}