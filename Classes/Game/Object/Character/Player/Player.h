﻿#ifndef _PLAYER_H_
#define _PLAYER_H_


//インクルード
#include "cocos2d.h"
#include "Utility/Collision/Collider.h"
#include "PlayerState.h"

enum class ObjectType : int;

class Note;

/**********************************************

ファイル名: Player.h
作成者: 小林 勇輝
***********************************************/
class Player :public cocos2d::Node , public Collider
{
protected:

	/******************************************
	コンストラクタ
	*******************************************/
	Player(ObjectType type,float jumpTime);

	/*******************************************
	デストラクタ
	********************************************/
	~Player();

public:
	/*******************************************
	初期化
	********************************************/
	virtual bool init(const std::string& fileName, ObjectType type);

	/********************************************
	更新
	deltaTime: デルタタイム
	*********************************************/
	virtual void update(float deltaTime) override;

	/*********************************************
	プレイヤーの生成
	**********************************************/
	static Player* create(const std::string& fileName, ObjectType type,float jumpTime);

	/********************************************
	ジャンプ
	後に別クラスに以降させると思います
	********************************************/
	void jump(cocos2d::Vec2 targetPosition);

	void changeJumpTime(float speed);

	void onContactBegin(cocos2d::Node* contactNode) override;

	virtual void setPosition(const cocos2d::Vec2& pos)override;

	virtual const cocos2d::Vec2& getPosition()const override;

	void stop(){ mSprite->stopAllActions(); };

	unsigned int jumpCount();

	void callDrawInit();
	void CallDrawEnd();

	PLAYERSTATE getState();

	void setState(PLAYERSTATE state){ mState = state; }

private:
	cocos2d::Sprite* mSprite;
   	float mDuration;
	float  mJumpTime;
	unsigned int mJumpCount;
	cocos2d::Vec2 mTargetPos;
	PLAYERSTATE mState;
};

#endif