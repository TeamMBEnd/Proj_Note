#ifndef _PLAYER_H_
#define _PLAYER_H_


//インクルード
#include "cocos2d.h"

/**********************************************

ファイル名: Player.h
作成者: 小林 勇輝

***********************************************/
class Player:public cocos2d::Node
{
protected:

	/******************************************
	コンストラクタ
	*******************************************/
	Player();

	/*******************************************
	デストラクタ
	********************************************/
	~Player();

public:
	/*******************************************
	初期化
	********************************************/
	virtual bool init() override;

	/********************************************
	更新
	deltaTime: デルタタイム
	*********************************************/
	virtual void update(float deltaTime) override;

	/*********************************************
	プレイヤーの生成
	**********************************************/
	static Player* createCharacter();

private:
	cocos2d::Sprite* mSprite;
};

#endif