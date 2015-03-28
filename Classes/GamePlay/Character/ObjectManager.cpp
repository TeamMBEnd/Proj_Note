#include "ObjectManager.h"
#include "GamePlay/Character/Player/Player.h"
#include "GamePlay/Character/Test/TestObject.h"
#include "DistanceCheck.h"

using namespace cocos2d;

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

bool ObjectManager::init()
{
	if (!Node::init())
	{
		return false;
	}

	mKatsumi = Player::create();
	mKatsumi->setPosition(200, 200);
	this->addChild(mKatsumi);

	//�ȉ��A�e�X�g�I�u�W�F�N�g����
	mObject = TestObject::create();
	mObject->setPosition(300,500);
	this->addChild(mObject);
}

void ObjectManager::update(float deltaTime)
{
	mKatsumi->update(deltaTime);

	if (distanceCheck())
	{
		mKatsumi->Jump(mObject->getPosition());
	}
}

ObjectManager* ObjectManager::create()
{
	auto instance = new ObjectManager();

	if (instance && instance->init())
	{
		instance->autorelease();
		return instance;
	}

	CC_SAFE_DELETE(instance);
	return nullptr;
}

void ObjectManager::onTouchBegan(Vec2 touchPoint)
{
	mObject->setPosition(touchPoint);
}

bool ObjectManager::distanceCheck()
{
	float distance = DistanceCheck::Check(mKatsumi, mObject);
	const float maximumDistance = 200;	//�W�����v�ł���ő勗��
	const float minDistance = 50;		//�߂�����ƃW�����v���Ȃ�
	if (distance > maximumDistance||
		distance < minDistance)
	{
		return false;
	}
	return true;
}