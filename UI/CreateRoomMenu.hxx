#ifndef _CREATE_ROOM_MENU_HXX_
#define _CREATE_ROOM_MENU_HXX_

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

#include "../Scene.hxx"

class CreateRoomMenu : public Scene
{
	mutable tgui::Gui _gui;

    tgui::Label::Ptr _playersCountLabel;
    tgui::Label::Ptr _gameModeLabel;
    tgui::Label::Ptr _startLevelLabel;

    tgui::Slider::Ptr _playersCountSlider;
    tgui::RadioButton::Ptr _sameModeRadioButton;
    tgui::RadioButton::Ptr _diffModeRadioButton;
    tgui::EditBox::Ptr _startLevelEditBox;

	tgui::Button::Ptr _createRoomButton;
	tgui::Button::Ptr _backButton;
public:
    CreateRoomMenu();
	void update() override;
	void render() const override;
	virtual tgui::Gui* get_gui_ptr() const override;
	void exchange_data() override;
};

#endif