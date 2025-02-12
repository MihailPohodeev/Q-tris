#include "Window.hxx"

Window::Window(const sf::Vector2f& size) : _gameField(sf::Vector2f(size.x / 2, size.y)), _scoreTable(sf::Vector2f(size.x / 2, size.y)), _size(size)
{
	_player = nullptr;
	this->set_position(sf::Vector2f(0.0f, 0.0f));
}

void Window::set_player_object(PlayerObject* player)
{
	_player = player;
	_player->set_double_frame(&_doubleFrame);
}

void Window::set_position(const sf::Vector2f& pos)
{
	_gameField.set_position(pos);
	_scoreTable.set_position(sf::Vector2f(pos.x + _size.x / 2.f + _size.x * 0.01f, pos.y));
}

void Window::update()
{
	if (!_player)
	{
		std::cerr << "Player object in Window is null :(\n";
		exit(-1);
	}
	_player->update();
	//std::cout << "player updated!\n";
	_scoreTable.set_score(_player->get_score());
	_scoreTable.set_lines(_player->get_lines());
	_scoreTable.set_level(_player->get_level());
	//std::cout << "score table updated!\n";
	_gameField.set_matrix(_doubleFrame.get_matrix());
	//std::cout << "gameField matrix - got";
	
	//Matrix mat = _doubleFrame.get_matrix();
	//struct ElementData*** buff = mat.get_buffer();
}

void Window::render() const
{
	_gameField.render();
	_scoreTable.render();
}

// set username.
void Window::set_username(const std::string& str)
{
	_scoreTable.set_username(str);
}
