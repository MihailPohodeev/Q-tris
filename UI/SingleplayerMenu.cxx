#include "CreateRoomMenu.hxx"
#include "../setup.hxx"
#include "SingleplayerMenu.hxx"
#include "../SinglePlayerScene.hxx"
#include "MainMenu.hxx"

extern int SCR_WIDTH;
extern int SCR_HEIGHT;
extern Scene* nextScene;
extern sf::RenderWindow* window;

SinglePlayerMenu::SinglePlayerMenu() :  _gui(*window)
{
    _startLevelLabel = tgui::Label::create("Start Level : ");
    _startLevelEditBox = tgui::EditBox::create();
    _startGameButton = tgui::Button::create("Start Game");
    _backButton = tgui::Button::create("Back");

    int textSize = (SCR_WIDTH + SCR_HEIGHT) / 80;
    sf::Vector2i labPos(SCR_WIDTH * 0.4, SCR_HEIGHT * 0.4);
    _startLevelLabel->setPosition(labPos.x, labPos.y);
    _startLevelLabel->setSize(100, 25);
    _startLevelLabel->setTextSize(textSize);

    _startLevelEditBox->setSize(50, 25);
    _startLevelEditBox->setPosition(labPos.x + 100, labPos.y * 0.99);
    _startLevelEditBox->setText("0");

    int sizeX = SCR_WIDTH / 5;
	int sizeY = sizeX / 4;
	_startGameButton->setSize(sizeX, sizeY);
	_backButton->setSize(sizeX, sizeY);

    _startGameButton->setTextSize(textSize);
    _backButton->setTextSize(textSize);

    _startLevelLabel->getRenderer()->setTextColor(tgui::Color::White);

	int posX = (SCR_WIDTH - sizeX) / 4;
	int posY = (SCR_HEIGHT) * 0.75;
	_startGameButton->setPosition(posX, posY);
	_backButton->setPosition(posX * 3, posY);
    _startGameButton->onClick([&](){nextScene = new SinglePlayerScene(std::stoi(_previousText != "" ? _previousText : "0"));});
    _backButton->onClick([&](){nextScene = new MainMenu();});

    _gui.add(_startGameButton);
    _gui.add(_startLevelLabel);
    _gui.add(_startLevelEditBox);
    _gui.add(_backButton);
}

void SinglePlayerMenu::update()
{
    _startLevelEditBox->onTextChange([&](const tgui::String& newText) {
        bool isValid = true;
        for (char c : newText.toStdString()) {
            if (!std::isdigit(c)) {
                isValid = false;
                break;
            }
        }

        // If the text is not valid, revert to the previous valid text
        if (!isValid)
        {
            _startLevelEditBox->setText(_previousText);
            return;
        } 
        else
        {
            // Update the previous valid text
            _previousText = newText.toStdString();
        }
    });
}

void SinglePlayerMenu::render() const
{
    _gui.draw();
}

tgui::Gui* SinglePlayerMenu::get_gui_ptr() const
{
    return &_gui;
}

void SinglePlayerMenu::exchange_data()
{
    return;
}