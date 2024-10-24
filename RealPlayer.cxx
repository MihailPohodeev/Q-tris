#include "RealPlayer.hxx"

extern Figure** figuresArray;

RealPlayer::RealPlayer() : PlayerObject()
{
	_get_new_figures_to_queue();
	_currentFigure = nullptr;
	_update_the_figure();

	isMoveRight = isMoveLeft = false;
	isRotateRight = isRotateLeft = false;
	isDrop = isAccelerate = false;
}

void RealPlayer::_update_the_figure()
{
	if (_currentFigure)
		delete _currentFigure;
	U8 index = _figuresIndecesQueue.front();
	_figuresIndecesQueue.pop();
	_currentFigure = figuresArray[index]->clone();
	_currentFigure->set_position(sf::Vector2i(4, -1));
}

void RealPlayer::set_controller(Controller* cntrlr)
{
	_controller = cntrlr;
}

void RealPlayer::_get_new_figures_to_queue()
{
	for (U8 i = 0; i < 30; i++)
	{
		U8 j = (U8)(random() % 4);
		_figuresIndecesQueue.push(j);
		std::cout << j;
	}
}

void RealPlayer::update()
{
	struct ElementData*** buffer = _matrixForWork.get_buffer();

	struct ElementData figureElements[4];
	_currentFigure->get_all_elements(figureElements);

	if (_clock.getElapsedTime().asMicroseconds() > (1'000'000 / _level))
	{
		for (U8 i = 0; i < 4; i++)
		{
			struct ElementData* currentElem = &figureElements[i];
			if (currentElem->position.x < 10 && currentElem->position.x >= 0 && currentElem->position.y >= 0 && currentElem->position.y < 20)
			{
				if (currentElem->position.y >= 19 || buffer[currentElem->position.x][currentElem->position.y + 1])
				{
					_matrixForWork.add_figure(*_currentFigure);
					_update_the_figure();
				}
			}
		}

		_currentFigure->move(sf::Vector2i(0, 1));
		
		if (_figuresIndecesQueue.size() <= 20)
			_get_new_figures_to_queue();

		_clock.restart();
	}
	else
	{
		if (_controller->is_move_right())
		{
			if (!isMoveRight)
			{
				bool isCanMove = true;
				for (U8 i = 0; i < 4; i++)
				{
					sf::Vector2i pos = figureElements[i].position;
					if (pos.y >= 0 && (pos.x >= 9 || buffer[pos.x + 1][pos.y]))
						isCanMove = false;
				}
				if (isCanMove)
					_currentFigure->move(sf::Vector2i(1, 0));
			}
			isMoveRight = true;
		}
		else isMoveRight = false;

		if (_controller->is_move_left())
		{
			if (!isMoveLeft)
			{
				bool isCanMove = true;
				for (U8 i = 0; i < 4; i++)
				{
					sf::Vector2i pos = figureElements[i].position;
					if (pos.y >= 0 && (pos.x <= 0 || buffer[pos.x - 1][pos.y]))
						isCanMove = false;
				}
				if (isCanMove)
					_currentFigure->move(sf::Vector2i(-1, 0));
			}
			isMoveLeft = true;
		}
		else isMoveLeft = false;

		if (_controller->is_rotate_right())
		{
			if (!isRotateRight)
			{
				bool isCanRotate = true;
				// condition : TODO
				if (isCanRotate)
					_currentFigure->rotate_right();
			}
			isRotateRight = true;
		}
		else isRotateRight = false;
	}

	Matrix resultMatrix = _matrixForWork;
	resultMatrix.add_figure(*_currentFigure);
	_doubleFrame->set_matrix(resultMatrix);
	_doubleFrame->swap_buffers();



}

void RealPlayer::exchange_data()
{
	;// TODO
}
