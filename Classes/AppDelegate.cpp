#include "AppDelegate.h"
#include "Utility/SceneSupport/SceneCreator.h"
#include "Utility/Audio/ADX2Manager.h"
#include "Utility/Audio/ADX2LogoLayer.h"
#include "Game/Scene/Test/HigeLayer.h"
#include "Game/Scene/GameMain/GameMainScene.h"
#include "Game/Scene/Title/TitleScene.h"
#include "Game/Scene/Test/TestLayer.h"

using namespace cocos2d;

AppDelegate::AppDelegate()
	: mADX2Manager( ADX2Manager::create() )
{
	mADX2Manager->retain();
}

AppDelegate::~AppDelegate()
{
	mADX2Manager->release();
}

bool AppDelegate::applicationDidFinishLaunching()
{
	auto director	= Director::getInstance();
	auto glView		= director->getOpenGLView();

	if ( !glView )
	{
		glView = GLView::create( "おんぷ" );
		director->setOpenGLView( glView );
	}
	
	director->setDisplayStats( false );
	director->setAnimationInterval( 1.f / 60.f );
	
	glView->setDesignResolutionSize( 1280, 720, ResolutionPolicy::SHOW_ALL );
	
	mADX2Manager->init( "Note.acf" );
	
	auto firstScene = SceneCreator::createPhysicsScene( TitleScene::create(),Vect(0,-9.8f),5.0f);
	auto scene		= TransitionFade::create( 1.5f, firstScene, Color3B::BLACK );
	director->runWithScene( scene );
	
	return true;
}

void AppDelegate::applicationDidEnterBackground()
{
	Director::getInstance()->stopAnimation();
	
	mADX2Manager->pauseApp();
}

void AppDelegate::applicationWillEnterForeground()
{
	Director::getInstance()->startAnimation();
	
	mADX2Manager->resumeApp();
}