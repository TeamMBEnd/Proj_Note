#ifndef _TESTLAYER_H_
#define _TESTLAYER_H_

//インクルード
#include "cocos2d.h"

//クラスの前方宣言
class Player;


/**************************************************

ファイル名 : TestLayer.h
作成者 : 小林勇輝

プレイヤー等の挙動確認のためのテストシーンです。

**************************************************/
class TestLayer : public cocos2d::Layer
{

protected:
	/********************************
	コンストラクタ
	*********************************/
	TestLayer();

	/********************************
	デストラクタ
	*********************************/
	~TestLayer();


public:
	/********************************
	初期化
	*********************************/
	virtual bool init() override;

	/*********************************
	更新
	**********************************/
	virtual void update(float deltaTime)override;

	/**********************************
	シーンの作成
	**********************************/
	static TestLayer* create();

private:
	Player* mKatsumi;
};

#endif