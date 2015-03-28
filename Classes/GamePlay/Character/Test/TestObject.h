#ifndef _TESTOBJECT_H_
#define _TESTOBJECT_H_

#include "cocos2d.h"


/********************************************
�v���C���[�̎��t���e�X�g�I�u�W�F�N�g
��ŏ����܂�
�쐬�ҁ@���їE�P
*********************************************/
class TestObject:public cocos2d::Node
{
public:
	TestObject();
	~TestObject();
	virtual bool init()override;
	virtual void update(float deltaTime)override;
	CREATE_FUNC(TestObject);
private:
	cocos2d::Sprite* mSprite;
};

#endif