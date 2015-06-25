#ifndef STARTANIMATION_H
#define STARTANIMATION_H

#include "cocos2d.h"

class StartAnimation : public cocos2d::Node
{
protected:
	StartAnimation() = default;
	~StartAnimation() = default;
public:

	static StartAnimation* create();

	//�X�^�[�g�����쐬
	void set();

	/*
		�X�^�[�g�A�j���[�V�����p��Sprite���쐬
	*/
	cocos2d::Sprite* createStartAnim(cocos2d::Size winSize,cocos2d::Sequence* action);

	/*
		�X�^�[�g�A�j���[�V�����p�̃A�N�V�������쐬
	*/
	cocos2d::Sequence* createSequence();
};

#endif
