#include "RestGimmick.h"
#include "../ObjectType.h"

using namespace cocos2d;

RestGimmick::RestGimmick() : mGimmickData(GimmickData()) {

}

RestGimmick::~RestGimmick() {
	this->disableCollision( this->getName() );
}

RestGimmick* RestGimmick::create(const std::string& nodeName, const GimmickData& data) {
	auto inst = new RestGimmick();

	if (inst && inst->init(nodeName, data))
	{
		inst->autorelease();
		return inst;
	}

	CC_SAFE_DELETE(inst);
	return nullptr;
}

bool RestGimmick::init( const std::string& nodeName, const GimmickData& data ) {
	if (!Sprite::initWithFile( data.gimmickTextureName + ".png" ) ) {
		return false;
	}

	mGimmickData = data;

	this->setName( nodeName );
	this->enableCollision( nodeName );
	this->setPosition(Vec2(mGimmickData.positionX, mGimmickData.positionY));

	initPhysics();

	auto action = JumpBy::create(5,Vec2::ZERO,700,1);

	RepeatForever* reForever = RepeatForever::create(action);

	this->runAction(reForever);

	return true;
}

void RestGimmick::onContactBegin(Node* contactNode) {

}

void RestGimmick::initPhysics() {

	auto size = cocos2d::Size(this->getContentSize().width, this->getContentSize().height);

	mPhysicsBody = PhysicsBody::createBox(size, mPhysicsMaterial);
	mPhysicsBody->setDynamic(true);
	mPhysicsBody->setGravityEnable(false);
	mPhysicsBody->setCategoryBitmask(converter::toInt(ObjectType::OBJECT_GIMMICK_REST));
	mPhysicsBody->setContactTestBitmask(converter::toInt(ObjectType::OBJECT_ALL));
	mPhysicsBody->setCollisionBitmask(converter::toInt(ObjectType::OBJECT_ALL));
	this->setPhysicsBody(mPhysicsBody);
}