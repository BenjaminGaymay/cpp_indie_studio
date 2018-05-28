/*
** EPITECH PROJECT, 2018
** student
** File description:
** 22/05/18
*/
#ifndef BOMBERMAN_RESPONSE_HPP
#define BOMBERMAN_RESPONSE_HPP
namespace Indie {
	enum messageType {
		PLAYER_MOVE,
		PLAYER_LEAVE,
		BOMB_DROP,
		TYPE_LAST // don't use it
	};
	typedef struct s_data {
		irr::core::vector2df _pos2d;
		irr::core::vector3df _pos3d;
		float _rotation;
		enum messageType type;
	} Data;

	class Response {
	public:
		Response(const std::string &str)
		{
			serialize(str);
		};

		~Response() = default;

		void serialize(const std::string &str)
		{
			std::vector<std::string> tab = ManageStrings::splitString(str, ':');

			_data.type = static_cast<messageType>(atoi(tab[0].c_str()));
			_data._pos2d = irr::core::vector2df(std::stof(tab[1]),
												std::stof(tab[2]));
			_data._pos3d = irr::core::vector3df(std::stof(tab[3]),
												std::stof(tab[4]),
												std::stof(tab[5]));
			_data._rotation = std::stof(tab[6]);
		};

		std::string unserialize()
		{
			std::stringstream ss;

			ss << _data._pos2d.X << ":" << _data._pos3d.Y << ":"
			   << _data._pos3d.Z << ":" << _data._pos2d.X << ":"
			   << _data._pos2d.Y << ":" << _data._rotation << std::endl;
			return ss.str();
		};
		Data _data;
	};
}
#endif //BOMBERMAN_RESPONSE_HPP
