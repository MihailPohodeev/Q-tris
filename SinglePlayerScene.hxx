#ifndef _SINGLE_PLAYER_SCENE_HXX_
#define _SINGLE_PLAYER_SCENE_HXX_

#include <string>

#include "Scene.hxx"
#include "RealPlayer.hxx"
#include "Window.hxx"

class SinglePlayerScene : public Scene
{
	Controller* _controller;
	RealPlayer* _realPlayer;
	Window* _window;

public:
	// constructor.
	// parameters: players count, isSameQueue, start level.
	SinglePlayerScene(U32);
	void update() override;
	void render() const override;
	virtual tgui::Gui* get_gui_ptr() const override;
	void exchange_data() override;
	~SinglePlayerScene();
};

#endif