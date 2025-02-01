#include "MultiplayerScene.hxx"
#include "KeyboardController1.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;

MultiplayerScene::MultiplayerScene(U8 playersCount, bool isSameQueue, U8 startLevel) : _windows(playersCount)
{
	// check if players count is unavalible.
	if (playersCount < 2)
		throw TooFewPlayersException(playersCount);
	else if (playersCount > 4)
		throw TooManyPlayersException(playersCount);
	
	// create controller and real player.
	_controller = new KeyboardController1();
	_realPlayer = new RealPlayer();

	sf::Vector2f mainWindowSize = sf::Vector2f(SCR_HEIGHT * 0.7, SCR_HEIGHT * 0.7);
	_windows[0] = new Window(mainWindowSize);
	int offset = (SCR_HEIGHT - mainWindowSize.x) * 0.5;
	_windows[0]->set_player_object(_realPlayer);
	_windows[0]->set_position(sf::Vector2f(offset * 0.5, offset));

	U8 netPlayersCount = playersCount - 1;
	if (SCR_WIDTH / (float)SCR_HEIGHT < 1.5f)
	{
		float xSize = SCR_WIDTH - (mainWindowSize.x + offset);
		xSize = xSize * 0.9;
		float ySize = (mainWindowSize.y / netPlayersCount) * 0.9;
		float minimalSize = xSize < ySize ? xSize : ySize;
		sf::Vector2f netWindowSize(minimalSize, minimalSize);

		float posX = (mainWindowSize.x + offset + SCR_WIDTH - minimalSize) / 2;
		for (U8 i = 1; i < _windows.size(); i++)
		{
			_windows[i] = new Window(netWindowSize);
			float smallOffset = mainWindowSize.y - minimalSize * netPlayersCount;
			smallOffset /= (netPlayersCount + 1);
			_windows[i]->set_position(sf::Vector2f(posX, offset \ 
					+ smallOffset * i + minimalSize * (i - 1)));
		}
	}
	else
	{

	}
}

MultiplayerScene::~MultiplayerScene()
{
	delete _realPlayer;
	delete _controller;
}

void MultiplayerScene::update()
{
	return;
}

void MultiplayerScene::render() const
{
	for (U8 i = 0; i < _windows.size(); i++)
		if (_windows[i]) _windows[i]->render();
}

void MultiplayerScene::exchange_data()
{
	return;
}
