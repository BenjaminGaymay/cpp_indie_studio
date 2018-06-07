//
// EPITECH PROJECT, 2018
// cpp_indie_studio
// File description:
// Chat
//

#pragma once

#include "Window.hpp"
#include "Options.hpp"
#include "Events.hpp"
#include "Clock.hpp"
#include "Socket.hpp"

namespace Indie {

	struct s_message {
		std::string _string;
		Clock _clock;
	};

	class Chat {
	public:
		Chat() : _getch(false) {}
		void manageTchat(Events &, std::unique_ptr<Socket> &);
		void printTchat(Window &, Options &);
		bool _getch;
		std::vector<s_message> _messages;
		irr::gui::IGUIEditBox *_textBox;
	};
}