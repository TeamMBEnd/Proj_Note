#ifndef _PLAYERMANAGER_H_
#define	_PLAYERMANAGER_H_

#include "cocos2d.h"
#include <vector>

class Player;
class BlockManager;
class UiObjectLayer;

using PlayerContainer = std::vector < Player* >;

class PlayerManager:public cocos2d::Node
{
public:
	static PlayerManager* create();
	virtual bool init()override;
	virtual void update(float deltaTime);
	void add(const cocos2d::Vec2& position1P, const cocos2d::Vec2& position2P,float jumpTime1P,float jumpTime2P);
	Player* getPlayer(int index){ return mPlayerContainer[index]; }

protected:
	PlayerManager();
	~PlayerManager();

private:
	
	PlayerContainer mPlayerContainer;
};

#endif