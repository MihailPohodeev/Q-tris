#include <string>
#include "ScoreTable.hxx"

extern sf::RenderWindow* window;
extern sf::Font* mainFont;

// constructor.
ScoreTable::ScoreTable(const sf::Vector2f& size)
{
	_shape.setFillColor(sf::Color(75, 75, 75, 255));
	_nextFigureShape.setFillColor(sf::Color(125, 125, 125, 255));

	_score = 0;
	_lines = 0;
	_level = 0;
	
	_usernameHeader.setFont(*mainFont);
	_nextFigureHeader.setFont(*mainFont);
	_scoreHeader.setFont(*mainFont);
	_linesHeader.setFont(*mainFont);
	_levelHeader.setFont(*mainFont);

	_usernameHeader.setString("Without Name");
	_nextFigureHeader.setString("Next Figure :");
	_scoreHeader.setString("SCORE : 0");
	_linesHeader.setString("LINES : 0");
	_levelHeader.setString("LEVEL : 0");

	_usernameHeader.setFillColor(sf::Color::Red);

	set_size(size);
	set_position(sf::Vector2f(0.0f, 0.0f));
}

// set new size.
void ScoreTable::set_size(const sf::Vector2f& size)
{
	_shape.setSize(size);
	_nextFigureShape.setSize(sf::Vector2f(size.x * 0.55, size.x * 0.55));
	U16 characterSize = static_cast<int>((size.x + size.y) / 25.f);
	_usernameHeader.setCharacterSize(characterSize);
	_nextFigureHeader.setCharacterSize(characterSize);
    _scoreHeader.setCharacterSize(characterSize);
    _linesHeader.setCharacterSize(characterSize);
    _levelHeader.setCharacterSize(characterSize);
}

// return current size.
sf::Vector2f ScoreTable::get_size() const
{
	return _shape.getSize();
}

// set new position.
void ScoreTable::set_position(const sf::Vector2f& pos)
{
	_shape.setPosition(pos);
	sf::Vector2f size = _shape.getSize();
	sf::Vector2f nfsize = _nextFigureShape.getSize();
	_usernameHeader.setPosition(sf::Vector2f(pos.x + size.x * 0.1f, pos.y + size.y * 0.075));
	_scoreHeader.setPosition(sf::Vector2f(pos.x + size.x * 0.1f, pos.y + size.y * 0.15f));
	_linesHeader.setPosition(sf::Vector2f(pos.x + size.x * 0.1f, pos.y + size.y * 0.225f));
	_levelHeader.setPosition(sf::Vector2f(pos.x + size.x * 0.1f, pos.y + size.y * 0.30f));
	_nextFigureHeader.setPosition(sf::Vector2f(pos.x + size.x * 0.1f, pos.y + size.y * 0.375f));
	_nextFigureShape.setPosition(sf::Vector2f(pos.x + (size.x - nfsize.x) / 2, pos.y + size.y * 0.5f));
}

// return position of ScoreTable.
sf::Vector2f ScoreTable::get_position() const
{
	return _shape.getPosition();
}

// set username.
void ScoreTable::set_username(const std::string& str)
{
	_usernameHeader.setString(str);
}

// set and get score.
void ScoreTable::set_score(U64 score)
{
	_score = score;
	std::string str = "SCORE : ";
	str += std::to_string(score);
	_scoreHeader.setString(str);
}

U64 ScoreTable::get_score() const
{
	return _score;
}

// set and get lines.
void ScoreTable::set_lines(U32 lines)
{
	_lines = lines;
	std::string str = "LINES : ";
	str += std::to_string(lines);
	_linesHeader.setString(str);
}

U32 ScoreTable::get_lines() const
{
	return _lines;
}

// set and get level.
void ScoreTable::set_level(U32 level)
{
	_level = level;
	std::string str = "LEVEL : ";
	str += std::to_string(level);
	_levelHeader.setString(str);
}

U32 ScoreTable::get_level() const
{
	return _level;
}

// render ScoreTable.
void ScoreTable::render() const
{
	window->draw(_shape);
	window->draw(_usernameHeader);
	window->draw(_scoreHeader);
	window->draw(_linesHeader);
	window->draw(_levelHeader);
	window->draw(_nextFigureHeader);
	window->draw(_nextFigureShape);
}
