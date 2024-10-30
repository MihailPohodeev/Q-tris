#include "Button.hxx"

extern sf::Font* mainFont;
extern sf::RenderWindow* window;

Button::Button(const sf::Vector2f& size): _shape(size)
{
	_shape.setOutlineThickness((size.x + size.y) / 80.0);
	_shape.setOutlineColor(sf::Color::Black);

	_text.setFont(*mainFont);
	_text.setFillColor(sf::Color::Black);
	_text.setCharacterSize((size.x + size.y) / 10);
	_text.setString(L"Untitle");

	sf::Vector2f pos = sf::Vector2f(size.x / 2.0, (size.y - _text.getCharacterSize()) / 2.0);
	sf::Vector2f textSize = sf::Vector2f(_text.getCharacterSize() * _text.getString().getSize(), _text.getCharacterSize());
	pos -= sf::Vector2f(textSize.x / 3.0, 0.0);
	_text.setPosition(pos);
}

void Button::set_position(const sf::Vector2f& pos)
{
	_shape.setPosition(pos);

	sf::Vector2f Tpos = sf::Vector2f(pos.x + _shape.getSize().x / 2.0, pos.y + (_shape.getSize().y - _text.getCharacterSize()) / 2.0);
        sf::Vector2f textSize = sf::Vector2f(_text.getCharacterSize() * _text.getString().getSize(), _text.getCharacterSize());
        Tpos -= sf::Vector2f(textSize.x / 3.0, 0.0);
        _text.setPosition(Tpos);
}

sf::Vector2f Button::get_position() const
{
	return _shape.getPosition();
}

void Button::set_string(const std::string& str)
{
	_text.setString(str);
	sf::Vector2f Tpos = sf::Vector2f(_shape.getPosition().x + _shape.getSize().x / 2.0, _shape.getPosition().y + (_shape.getSize().y - _text.getCharacterSize()) / 2.0);
        sf::Vector2f textSize = sf::Vector2f(_text.getCharacterSize() * _text.getString().getSize(), _text.getCharacterSize());
        Tpos -= sf::Vector2f(textSize.x / 3.0, 0.0);
        _text.setPosition(Tpos);

}

sf::Vector2f Button::get_size() const
{
	return _shape.getSize();
}

void Button::update()
{

}

void Button::render() const
{
	window->draw(_shape);
	window->draw(_text);
}
