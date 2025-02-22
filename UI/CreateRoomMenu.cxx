#include "CreateRoomMenu.hxx"
#include "../setup.hxx"
#include "MultiplayerMenu.hxx"
#include "Lobby.hxx"
#include "../Server.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;
extern Server* server;

CreateRoomMenu::CreateRoomMenu() :  _gui(*window)
{
    //auto font = tgui::Font::loadFromFile("Fonts/GASAGRANDE.ttf"); 

	_playersCountLabel = tgui::Label::create("Players Count : ");
    _gameModeLabel     = tgui::Label::create("Game Mode : ");
    _startLevelLabel   = tgui::Label::create("Start Level : ");
    _playersCountSlider = tgui::Slider::create();
    _sameModeRadioButton = tgui::RadioButton::create();
    _diffModeRadioButton = tgui::RadioButton::create();
    _startLevelEditBox = tgui::EditBox::create();
    
    _sameModeRadioButton->setText("Same");
    _diffModeRadioButton->setText("Different");

    sf::Vector2i posLabels = sf::Vector2i(SCR_WIDTH * 0.2, SCR_HEIGHT * 0.2);
    _playersCountLabel->setPosition(posLabels.x, posLabels.y);
    _playersCountSlider->setPosition(posLabels.x, posLabels.y * 1.3);
    _gameModeLabel->setPosition(posLabels.x, posLabels.y * 1.6);
    _sameModeRadioButton->setPosition(posLabels.x * 2, posLabels.y * 1.6);
    _diffModeRadioButton->setPosition(posLabels.x * 3, posLabels.y * 1.6);
    _startLevelLabel->setPosition(posLabels.x, posLabels.y * 2.2);
    _startLevelEditBox->setPosition(posLabels.x * 1.7, posLabels.y * 2.1);

    _sameModeRadioButton->setEnabled(true);
    
    //_playersCountLabel->setTextColor(tgui::Color::White); // Устанавливаем цвет текста
    //_playersCountLabel->setFont(font); // Устанавливаем шрифт
    int textSize = (SCR_WIDTH + SCR_HEIGHT) / 80;
    _playersCountLabel->setTextSize(textSize);
    _gameModeLabel->setTextSize(textSize);
    _startLevelLabel->setTextSize(textSize);
    _playersCountSlider->setSize((SCR_WIDTH + SCR_HEIGHT) / 10, (SCR_WIDTH + SCR_HEIGHT) / 80);
    _sameModeRadioButton->setSize((SCR_WIDTH + SCR_HEIGHT) / 80, (SCR_WIDTH + SCR_HEIGHT) / 80);
    _diffModeRadioButton->setSize((SCR_WIDTH + SCR_HEIGHT) / 80, (SCR_WIDTH + SCR_HEIGHT) / 80);
    _sameModeRadioButton->setTextSize(textSize);
    _diffModeRadioButton->setTextSize(textSize);
    _startLevelEditBox->setSize((SCR_WIDTH + SCR_HEIGHT) / 30, (SCR_WIDTH + SCR_HEIGHT) / 40);
    _startLevelEditBox->setTextSize(textSize);

    _playersCountSlider->setMinimum(2);
    _playersCountSlider->setMaximum(4);
    _playersCountSlider->setValue(2);

    _createRoomButton = tgui::Button::create("Create new Room");
	_backButton = tgui::Button::create("Back");

    _playersCountLabel->getRenderer()->setTextColor(tgui::Color::White);
    _gameModeLabel->getRenderer()->setTextColor(tgui::Color::White);
    _startLevelLabel->getRenderer()->setTextColor(tgui::Color::White);

    int sizeX = SCR_WIDTH / 5;
	int sizeY = sizeX / 4;
	_createRoomButton->setSize(sizeX, sizeY);
	_backButton->setSize(sizeX, sizeY);

    _createRoomButton->setTextSize(textSize);
    _backButton->setTextSize(textSize);

	int posX = (SCR_WIDTH - sizeX) / 4;
	int posY = (SCR_HEIGHT) * 0.75;
	_createRoomButton->setPosition(posX, posY);
	_backButton->setPosition(posX * 3, posY);
    _createRoomButton->onClick([&]()
    {
        struct GameParameter gp {(U8)_playersCountSlider->getValue(), 0, _sameModeRadioButton->isEnabled()};
        I32 roomID = server->create_room(gp);
        std::cout << "RoomID : " << roomID << '\n';
        nextScene = new Lobby();
    });
    _backButton->onClick([&](){nextScene = new MultiplayerMenu();});

    _gui.add(_playersCountLabel);
    _gui.add(_gameModeLabel);
    _gui.add(_startLevelLabel);
    _gui.add(_createRoomButton);
	_gui.add(_backButton);
    _gui.add(_playersCountSlider);
    _gui.add(_sameModeRadioButton);
    _gui.add(_diffModeRadioButton);
    _gui.add(_startLevelEditBox);
}

void CreateRoomMenu::update()
{
    _playersCountLabel->setText("Players Count : " + std::to_string((I16)_playersCountSlider->getValue()));
}

void CreateRoomMenu::render() const
{
    _gui.draw();
}

tgui::Gui* CreateRoomMenu::get_gui_ptr() const
{
    return &_gui;
}

void CreateRoomMenu::exchange_data()
{
    return;
}