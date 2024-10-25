#include "GameField.hxx"

extern sf::RenderWindow* window;

// constructor
GameField::GameField(const sf::Vector2f& size) : _shape(size), _element(sf::Vector2f(size.x / 10, size.y / 20)) 
{
	_shape.setFillColor(sf::Color(50, 50, 50, 255));
}

// set matrix
void GameField::set_matrix(const Matrix& matrix)
{
	_matrix = matrix;
}

// get position of GameField.
sf::Vector2f GameField::get_position() const
{
	return _shape.getPosition();
}

// set new position.
void GameField::set_position(const sf::Vector2f& pos)
{
	_shape.setPosition(pos);
}

// render game field with elements.
void GameField::render() const
{
	window->draw(_shape);
	struct ElementData*** buf = _matrix.get_buffer();
	for(U8 i = 0; i < 10; i++)
	{
		for(U8 j = 0; j < 20; j++)
		{
			if (buf[i][j])
			{
				_element.set_color(buf[i][j]->color);
				_element.set_position(this->get_position() + sf::Vector2f(buf[i][j]->position.x * _element.get_size().x, buf[i][j]->position.y * _element.get_size().y));
				_element.render();
			}
		}
	}
}
