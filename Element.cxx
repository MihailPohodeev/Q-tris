#include "Element.hxx"

extern sf::RenderWindow* window;

Element::Element(const sf::Vector2f& size) : _shape(size) {}

void Element::set_color(const sf::Color& color)
{
	_shape.setFillColor(color);
}

sf::Color Element::get_color() const
{
	return _shape.getFillColor();
}

void Element::set_position(const sf::Vector2f& pos)
{
	_shape.setPosition(pos);
}

void Element::move(const sf::Vector2f& offset)
{
	_shape.move(offset);
}

sf::Vector2f Element::get_size() const
{
	return _shape.getSize();
}

void Element::set_size(const sf::Vector2f& size)
{
	_shape.setSize(size);
}

Element* Element::clone() const
{
	Element* result = new Element(_shape.getSize());
	(*result) = (*this);
	return result;
}

void Element::render() const
{
	window->draw(_shape);
}
