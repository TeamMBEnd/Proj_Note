#include "GameDataMediator.h"
#include "Game/Object/UIObject/UiObjectLayer.h"
#include "Game/Object/Character/Player/Player.h"
#include "Utility/Action/Follow/CustomFollow.h"
#include "Game/Object/Character/Player/GoalAnimation.h"
#include "Game/Scene/GameMain/GameMainScene.h"
#include "Utility/SceneSupport/SceneCreator.h"



GameDataMediator* GameDataMediator::create(){
	auto ins = new GameDataMediator();

	if (ins && ins->init()){
		ins->autorelease();
		return ins;
	}
	CC_SAFE_DELETE(ins);
	return nullptr;
}

bool GameDataMediator::init(){
	if (!Node::init())
	{
		return false;
	}

	mPlayerManager = PlayerManager::create();
	mBlockManager = BlockManager::create();
	mGImmickManager = GimmickManager::create();
    
    timer.reset();
    timer.begin();
    
	mPlayerManager->add(cocos2d::Vec2(80, 210), cocos2d::Vec2(150, 210), 2, 2);

	this->addChild(mPlayerManager);
	this->addChild(mBlockManager);
	this->addChild(mGImmickManager);
    
    mCount = 0;

	return true;
}

void GameDataMediator::update(float dt, UiObjectLayer* uiLayer){

	mPlayerManager->update(dt);
    
    if(mPlayerManager->getPlayer(0)->getState() == DEAD  && mCount == 0) {
        mCount++;
        auto scene = SceneCreator::createPhysicsScene(GameMainScene::create(), cocos2d::Vect(0, -9.8f), 5.0f);
        auto fade	= cocos2d::TransitionFade::create( 1.5f, scene, cocos2d::Color3B::BLACK );
        cocos2d::Director::getInstance()->replaceScene( fade );
		
    }
    
    if(mPlayerManager->getPlayer(1)->getState() == DEAD && mCount == 0){
        mCount++;
        auto scene = SceneCreator::createPhysicsScene(GameMainScene::create(), cocos2d::Vect(0, -9.8f), 5.0f);
        auto fade	= cocos2d::TransitionFade::create( 1.5f, scene, cocos2d::Color3B::BLACK );
        cocos2d::Director::getInstance()->replaceScene( fade );
    
    }
    
    auto userDef = cocos2d::UserDefault::getInstance();
    bool isClear = userDef->getBoolForKey("isClear");
    
    if(isClear && mCount == 0){
        
        mCount++;
        
        Player* player = mPlayerManager->getPlayer(PLAYER1);
        Player* player2 = mPlayerManager->getPlayer(PLAYER2);
        
        player->setState(CLEAR);
        player2->setState(CLEAR);
        auto sprite1 = mPlayerManager->getPlayer(0)->getChildByName("Player");
        auto sprite2 =  mPlayerManager->getPlayer(1)->getChildByName("Player2");
        
        sprite1->getPhysicsBody()->setGravityEnable(false);
        sprite2->getPhysicsBody()->setGravityEnable(false);
        sprite1->getPhysicsBody()->setDynamic( false );
		sprite2->getPhysicsBody()->setDynamic( false );

		auto size = cocos2d::Director::getInstance()->getWinSize();

        GoalAnimation goal;
        goal.action(mBlockManager->getGoalPos(),
                    this,
                    mPlayerManager->getPlayer(0)->getChildByName("Player"),
                    mPlayerManager->getPlayer(1)->getChildByName("Player2"));
		
		
		auto BG = cocos2d::Sprite::create("Texture/GamePlay/GameStage/Goal.png");
		auto goalPos = cocos2d::Vec2(mBlockManager->getGoalPos().x, size.height / 2);
		BG->setPosition(goalPos);
		BG->setAnchorPoint(cocos2d::Vec2(0.5f,0.5f));
		addChild(BG);
		
		
        auto node = Node::create();
        auto func = cocos2d::CallFunc::create([&]() {
			auto userDef = cocos2d::UserDefault::getInstance();

			int  selectStage = userDef->getIntegerForKey("selectStage");
			int  clearStage = userDef->getIntegerForKey("clearStage");
			
			userDef->setIntegerForKey("clearStage", selectStage);
			userDef->setIntegerForKey("selectStage", selectStage + 1);
            userDef->setIntegerForKey("selectGimmick", selectStage + 1);

			mResult = ResultLayer::create(mBlockManager->getGoalPos());
            addChild(mResult,100);
        });
        auto delay = cocos2d::DelayTime::create(5.0f);
        auto seq = cocos2d::Sequence::create(delay, func, nullptr);
        node->runAction(seq);
        this->addChild(node);
        
        auto userDef = cocos2d::UserDefault::getInstance();
        userDef->setBoolForKey("isClear" , false);
        userDef->flush();

    }

	SlideBar* slideBar = uiLayer->getSlideBar();

    Player* player = mPlayerManager->getPlayer(PLAYER1);
    
    if (slideBar->isTouch("p1", uiLayer)){
        player->changeJumpTime(slideBar->getValue("p1", uiLayer));
    }
    
    if (player->getState() != JUMP)
    {
        player->jump(mBlockManager->getBlockPos(player->jumpCount()));
    }
    
    if (timer.getTime() <= 30)
    {
        timer.update();
        return;
    }
    
    Player* player2 = mPlayerManager->getPlayer(PLAYER2);
    
    if (slideBar->isTouch("p2", uiLayer)){
        player2->changeJumpTime(slideBar->getValue("p2", uiLayer));
    }
    
    if (player2->getState() != JUMP){
        
        player2->jump(mBlockManager->getBlockPos(player2->jumpCount()));
    }
    


}

void GameDataMediator::setFollow(cocos2d::Layer* layer){
	auto follow = CustomAction::CustomFollow::create(mPlayerManager->getPlayer(PLAYER1), mPlayerManager->getPlayer(PLAYER2), CustomAction::CustomFollowXOnly, cocos2d::Rect(0, 0, 40000, 800));
	follow->setTag(1003);
	layer->runAction(follow);
}