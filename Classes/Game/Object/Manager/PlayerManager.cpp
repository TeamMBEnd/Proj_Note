#include "PlayerManager.h"
#include "../Character/Player/Player.h"
#include "../../../Utility/Release/ReleaseInstance.h"
using namespace cocos2d;

PlayerManager::PlayerManager()
{
	mPlayerContainer.clear();
}

PlayerManager::~PlayerManager()
{
	for (auto player : mPlayerContainer)
	{
		ReleaseInstance(player);
	}
}

bool PlayerManager::init()
{
	if (!Node::init())
	{
		return false;
	}
	return true;
}

void PlayerManager::update(float deltaTime)
{
	for (auto player : mPlayerContainer)
	{
		player->update(deltaTime);
	}
}

void PlayerManager::add(const Vec2& position1P, const Vec2& position2P)
{
	auto player = Player::create("Helper1.png");
	player->setName("Player1");
	player->setPosition( position1P );
	mPlayerContainer.push_back( player );
	this->addChild(player);
	auto player2P = Player::create("Helper2.png");
	player2P->setName("Player2");
	player2P->setPosition( position2P );
	mPlayerContainer.push_back( player2P );
	this->addChild(player2P);
}

PlayerManager* PlayerManager::create()
{
	auto instance = new PlayerManager();
	if (instance&&instance->init())
	{
		return instance;
	}
	CC_SAFE_DELETE(instance);
	return nullptr;
}