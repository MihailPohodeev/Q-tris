#include <SFML/Graphics.hpp>
#include <mutex>

#include "NetworkPlayer.hxx"
#include "Figures/Element.hxx"


NetworkPlayer::NetworkPlayer(I32 id) : PlayerObject(), _userID(id) {}

void NetworkPlayer::update()
{
	
}

void NetworkPlayer::exchange_data()
{
	struct ElementData elem;
	elem.color = sf::Color(192, 168, 1);
	elem.position = sf::Vector2i(5, 6);
	Matrix temp;
	temp.add_element(elem);
	std::cout << "matrix created and element added.\n";
	if (!_doubleFrame)
	{
		std::cerr << "_doubleFrame object is null!!!\n";
		exit(-1);
	}
	_doubleFrame->set_matrix(temp);
	_doubleFrame->swap_buffers();
}

// get id.
I32 NetworkPlayer::get_ID() const
{
	return _userID;
}
