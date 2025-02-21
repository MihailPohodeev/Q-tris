#include "RealPlayer.hxx"
#include "Server.hxx"
#include "json.hpp"

using json = nlohmann::json;

extern Figure** figuresArray;
extern Server* server;
extern std::string modeQueue;

// contructor.
RealPlayer::RealPlayer() : PlayerObject(), _incrementForLevel(10), _currentLevelIncrementState(0)
{
	_get_new_figures_to_queue();
	_currentFigure = nullptr;
	//_update_the_figure();
}

// push into queue new figures.
void RealPlayer::_update_the_figure()
{
	if (_currentFigure)
		delete _currentFigure;

	U8 index;
	do
	{
		if (_figuresIndecesQueue.size() <= 20 && _clockReceivingFigures.getElapsedTime().asMilliseconds() > 3'00)
		{
			std::lock_guard<std::mutex> lock(_figuresIndecesQueueGuard);
			_get_new_figures_to_queue();
			_clockReceivingFigures.restart();
		}
	}
	while (_figuresIndecesQueue.size() < 2);

	{
		std::lock_guard<std::mutex> lock(_figuresIndecesQueueGuard);
		index = _figuresIndecesQueue.front();
		_figuresIndecesQueue.pop();
	}

	_currentFigure = figuresArray[index]->clone();
	_currentFigure->set_position(sf::Vector2i(4, -1));
}

// set controller for figure movement.
void RealPlayer::set_controller(Controller* cntrlr)
{
	_controller = cntrlr;
}

// set level.
void RealPlayer::set_level(U32 level)
{
	_level = level;
}

// set new figures.
void RealPlayer::set_new_figures(const std::vector<U8>& vec)
{
	std::lock_guard<std::mutex> lock(_figuresIndecesQueueGuard);
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		_figuresIndecesQueue.push((U8)*it);
	}
}

// fill queue by new figures.
void RealPlayer::_get_new_figures_to_queue()
{
	if (modeQueue == "Same")
	{
		json requestJSON;
		requestJSON["Command"] = "GetNewFigures";
		server->send_data(requestJSON.dump());
	}
	else
	{
		for (U8 i = 0; i < 30; i++)
		{
			U8 j = (U8)(random() % 7);
			_figuresIndecesQueue.push(j);
			std::cout << j;
		}
	}
}

// get next index of figure.
U8 RealPlayer::get_next_figure_index()
{
	std::lock_guard<std::mutex> lock(_figuresIndecesQueueGuard);
	if (_figuresIndecesQueue.size() < 1)
		return 0;
	U8 result = _figuresIndecesQueue.front();
	return result;
}

// update player's state.
void RealPlayer::update()
{
	if (!_currentFigure)
		_update_the_figure();

	struct ElementData*** buffer = _matrixForWork.get_buffer();

	struct ElementData figureElements[4];
	_currentFigure->get_all_elements(figureElements);

	if (!_controller)
	{
		std::cerr << "Controller in RealPlayer is null :(\n";
		exit(-1);
	}
	// accelerate the figure - if player press button 'accelerate'.
	_speed = (_controller->is_accelerate()) ? 100'000 / (_level + 1) : 1'000'000 / (_level + 1);

	if (_clock.getElapsedTime().asMicroseconds() > _speed)
	{
		// destroy full lines.
		U8 countOfDestroyableLines = 0;
		for (U8 j = 0 ; j < 20; j++)
		{
			bool isDestroyLine = true;
			for (U8 i = 0; i < 10; i++)
			{
				if (!buffer[i][j])
					isDestroyLine = false;
			}
			if (isDestroyLine)
			{
				countOfDestroyableLines++;
				for (U8 m = j; m > 0; m--)
				{
					for (U8 n = 0; n < 10; n++)
					{
						if (buffer[n][m])
							delete buffer[n][m];
						buffer[n][m] = buffer[n][m - 1];
						buffer[n][m - 1] = nullptr;
						if (buffer[n][m])
							buffer[n][m]->position = sf::Vector2i(n, m);
					}
				}
			}
		}

		_lines += countOfDestroyableLines;
		switch (countOfDestroyableLines)
		{
			case(1):
				_score += 40 * (_level + 1);
				break;
			case(2):
				_score += 100 * (_level + 1);
				break;
			case(3):
				_score += 300 * (_level + 1);
				break;
			case(4):
				_score += 1200 * (_level + 1);
		}
		
		_currentLevelIncrementState += countOfDestroyableLines;
		if (_currentLevelIncrementState >= _incrementForLevel)
		{
			_level += 1;
			_currentLevelIncrementState -= _incrementForLevel;
			_incrementForLevel *= 1.2f;
		}
		
		// paste figure into matrix, if it touch the top of cup.
		for (U8 i = 0; i < 4; i++)
		{
			struct ElementData* currentElem = &figureElements[i];
			if (currentElem->position.x < 10 && currentElem->position.x >= 0 && currentElem->position.y >= 0 && currentElem->position.y < 20)
			{
				if (currentElem->position.y >= 19 || buffer[currentElem->position.x][currentElem->position.y + 1])
				{
					for (U8 i = 0; i < 4; i++)
					{
						struct ElementData* curElem = &figureElements[i];
						if (curElem->position.y <= 2)
							_isGameOver = true;
					}
					_matrixForWork.add_figure(*_currentFigure);
					_update_the_figure();
					break;
				}
			}
		}

		_currentFigure->move(sf::Vector2i(0, 1));

		_clock.restart();
	}
	else
	{
		if (_controller->is_move_right())
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

		if (_controller->is_move_left())
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

		
		if (_controller->is_rotate_right())
		{
			bool isCanRotateRight = true;
			sf::Vector2i pos = _currentFigure->get_position();
			_currentFigure->rotate_right();
			enum direction {NONE, LEFT, RIGHT} dir;
			dir = direction::NONE;

			struct ElementData elems[4];
			_currentFigure->get_all_elements(elems);
			for (U8 i = 1; i < 4; i++)
			{
				sf::Vector2i position = elems[i].position;
				if (position.x > 9)
				{
					if (dir == direction::LEFT)
					{
						isCanRotateRight = false;
						break;
					}
					dir = direction::RIGHT;
				}
				else if (position.x < 0)
				{
					if (dir == direction::RIGHT)
					{
						isCanRotateRight = false;
						break;
					}
					dir = direction::LEFT;
				}
				else if (buffer[position.x][position.y])
				{
					if (position.x <= elems[0].position.x)
					{
						if (dir == direction::RIGHT)
						{
							isCanRotateRight = false;
							break;
						}
						dir = direction::LEFT;
					}
					else if (position.x > elems[0].position.x)
					{
						if (dir == direction::LEFT)
						{
							isCanRotateRight = false;
							break;
						}
						dir = direction::RIGHT;
					}
				}
			}

			if (dir != direction::NONE)
			{
				if (dir == direction::RIGHT)
				{
					for (U8 i = 0; i < 4; i++)
					{
						sf::Vector2i position = elems[i].position;
						if (position.x < 10)
						{
							if (buffer[position.x - 1][position.y])
							{
								isCanRotateRight = false;
								break;
							}
						}
					}
					if (isCanRotateRight)
					{
						while(true)
						{
							_currentFigure->move(sf::Vector2i(-1, 0));
							_currentFigure->get_all_elements(elems);
							bool condition1 = true;
							bool condition2 = false;
							for (U8 i = 0; i < 4; i++)
							{
								sf::Vector2i position = elems[i].position;
								if (position.x >= 10 || buffer[position.x][position.y])
									condition1 = false;
								if (position.x <= 10 && buffer[position.x - 1][position.y])
									condition2 = true;
							}
							if (condition1)
								break;
							if (condition2)
							{
								isCanRotateRight = false;
								break;
							}
						}
					}
				}
				else if (dir == direction::LEFT)
				{
					for (U8 i = 0; i < 4; i++)
					{
						sf::Vector2i position = elems[i].position;
						if (position.x >= 0)
						{
							if (buffer[position.x + 1][position.y])
							{
								isCanRotateRight = false;
								break;
							}
						}
					}

					if (isCanRotateRight)
					{
						while(true)
						{
							_currentFigure->move(sf::Vector2i(1, 0));
							_currentFigure->get_all_elements(elems);
							bool condition1 = true;
							bool condition2 = false;
							for (U8 i = 0; i < 4; i++)
							{
								sf::Vector2i position = elems[i].position;
								if (position.x < 0 || buffer[position.x][position.y])
									condition1 = false;
								if (position.x >= 0 && buffer[position.x + 1][position.y])
									condition2 = true;
							}
							if (condition1)
								break;
							if (condition2)
							{
								isCanRotateRight = false;
								break;
							}
						}
					}
				}
			}

			if (!isCanRotateRight)
			{
				_currentFigure->rotate_left();
				_currentFigure->set_position(pos);
			}
		}

		if (_controller->is_drop())
		{
			sf::Vector2i offset(0, 20);
			for (U8 i = 0; i < 4; i++)
			{
				sf::Vector2i pos = figureElements[i].position;
				if (pos.x < 0 || pos.x >= 10 || pos.y < 0 || pos.y > 19)
					continue;
				U8 yOffset = 0;
				while(pos.y + yOffset < 19 && !buffer[pos.x][pos.y + yOffset + 1])
					yOffset++;
				if (yOffset < offset.y)
					offset.y = yOffset;
			}
			_currentFigure->move(offset);
		}
	}
	
	Matrix resultMatrix = _matrixForWork;
	resultMatrix.add_figure(*_currentFigure);
	_doubleFrame->set_matrix(resultMatrix);
	_doubleFrame->swap_buffers();
}

// share my data with other players.
void RealPlayer::exchange_data()
{
	if (_clockForDataSending.getElapsedTime().asMicroseconds() > 100'000.0)
	{
		json package;
		package["Command"] = "GameFrame";
		package["Score"] = _score;
		package["Level"] = _level;
		package["Lines"] = _lines;
		package["NextFigure"] = (U32)get_next_figure_index();
		package["Data"] = json::array();
	
		Matrix mat = _doubleFrame->get_matrix();
	
		struct ElementData*** buf = mat.get_buffer();
		for(U8 i = 0; i < 10; i++)
		{
			for(U8 j = 0; j < 20; j++)
			{
				json elemJSON;
				if (buf[i][j])
				{
					elemJSON["Col"]["R"] = buf[i][j]->color.r;
					elemJSON["Col"]["G"] = buf[i][j]->color.g;
					elemJSON["Col"]["B"] = buf[i][j]->color.b;
	
					elemJSON["Pos"]["X"] = buf[i][j]->position.x;
					elemJSON["Pos"]["Y"] = buf[i][j]->position.y;
					package["Data"].push_back(elemJSON);
	            }
	        }
	    }
		server->send_data(package.dump());
		_clockForDataSending.restart();
	}
}
