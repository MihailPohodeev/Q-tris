#include "Window.hxx"

extern sf::RenderWindow* window;
extern sf::Font* mainFont;

Window::Window(const sf::Vector2f& size) : _gameField(sf::Vector2f(size.x / 2, size.y)), _scoreTable(sf::Vector2f(size.x / 2, size.y)), _size(size), _notification(sf::Vector2f(size.x * 0.5, size.y * 0.2))
{
	_player = nullptr;
	this->set_position(sf::Vector2f(0.0f, 0.0f));
	
	U16 characterSize = static_cast<int>((_size.x + _size.y) / 25.f);
	_gameOverHeader.setFont(*mainFont);
	_gameOverHeader.setString("Game Over");
	_gameOverHeader.setFillColor(sf::Color::White);
	_gameOverHeader.setCharacterSize(characterSize);

	_notification.setFillColor(sf::Color(128, 128, 128, 230));
	_notification.setOutlineColor(sf::Color::Black);
	_notification.setOutlineThickness(1.f);
	set_position(sf::Vector2f(0.0, 0.0));
}

void Window::set_player_object(PlayerObject* player)
{
	_player = player;
	_player->set_double_frame(&_doubleFrame);
}

void Window::set_position(const sf::Vector2f& pos)
{
	_gameField.set_position(pos);
	_notification.setPosition(sf::Vector2f(pos.x + _size.x / 2 - _size.x * 0.25 , pos.y + _size.y * 0.5));
	_gameOverHeader.setPosition(sf::Vector2f(_gameOverHeader.getCharacterSize() * .6f + pos.x + _size.x / 2 - _size.x * 0.25, pos.y + _size.y * 0.55));
	_scoreTable.set_position(sf::Vector2f(pos.x + _size.x / 2.f + _size.x * 0.01f, pos.y));
}

void Window::update()
{
	//std::cout << "Start update!\n";
	if (!_player)
	{
		std::cerr << "Player object in Window is null :(\n";
		exit(-1);
	}
	if (!_player->is_game_over())
		_player->update();
	//std::cout << "player updated!\n";
	_scoreTable.set_score(_player->get_score());
	_scoreTable.set_lines(_player->get_lines());
	_scoreTable.set_level(_player->get_level());
	//std::cout << "score table updated!\n";
	Matrix mat = _doubleFrame.get_matrix();
	//std::cout << "retrieved matrix!\n";
	_gameField.set_matrix(mat);
	//std::cout << "Finish update!\n";
	//Matrix mat = _doubleFrame.get_matrix();
	//struct ElementData*** buff = mat.get_buffer();
}

void Window::render() const
{
	_gameField.render();
	_scoreTable.render();
	if (_player->is_game_over())
	{
		window->draw(_notification);
		window->draw(_gameOverHeader);
	}
}

// set username.
void Window::set_username(const std::string& str)
{
	_scoreTable.set_username(str);
}
