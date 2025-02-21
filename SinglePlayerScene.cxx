#include "SinglePlayerScene.hxx"
#include "KeyboardController1.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;
extern std::string username;

SinglePlayerScene::SinglePlayerScene(U32 startLevel)
{
    _controller = new KeyboardController1();
    _realPlayer = new RealPlayer();
	_realPlayer->set_controller(_controller);
    _realPlayer->set_level(startLevel);

    sf::Vector2f mainWindowSize(SCR_HEIGHT * 0.8, SCR_HEIGHT * 0.8);
	_window = new Window(mainWindowSize);
    _window->set_player_object(_realPlayer);
    sf::Vector2f mainWindowPosition((SCR_WIDTH - mainWindowSize.x) / 2, (SCR_HEIGHT - mainWindowSize.y) / 2);
	_window->set_position(mainWindowPosition);
	_window->set_username(username);

}

SinglePlayerScene::~SinglePlayerScene()
{
    delete _window;
    delete _realPlayer;
    delete _controller;
}

void SinglePlayerScene::update()
{
    _window->update();
}

void SinglePlayerScene::render() const
{
    _window->render();
}

tgui::Gui* SinglePlayerScene::get_gui_ptr() const
{
    return nullptr;
}

void SinglePlayerScene::exchange_data()
{
    return;
}