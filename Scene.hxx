#ifndef _SCENE_HXX_
#define _SCENE_HXX_

#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class Scene
{
public:
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual tgui::Gui* get_gui_ptr() const = 0;
	virtual void exchange_data() = 0;
	virtual ~Scene() {}
};

#endif
