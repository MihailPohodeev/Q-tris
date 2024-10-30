#ifndef _SCENE_HXX_
#define _SCENE_HXX_

class Scene
{
public:
	virtual void update() = 0;
	virtual void render() const = 0;
	virtual void exchange_data() = 0;
};

#endif
