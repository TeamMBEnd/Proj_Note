#include "CustomFollow.h"

USING_NS_CC;

namespace CustomAction{


	CustomFollow::~CustomFollow(){
		CC_SAFE_RELEASE(_followedNode);
	}

	CustomFollow* CustomFollow::create(Node* followNode){
		CustomFollow *follow = new CustomFollow();

		if (follow && follow->initWithTarget(followNode, Rect::ZERO)){
			follow->autorelease();
			return follow;
		}
		CC_SAFE_DELETE(follow);
		return nullptr;
	}

	CustomFollow* CustomFollow::create(Node* followNode, CustomFollowType type){
		CustomFollow *follow = new CustomFollow();
		follow->mType = type;
		if (follow && follow->initWithTarget(followNode, Rect::ZERO)){
			follow->autorelease();
			return follow;
		}
		CC_SAFE_DELETE(follow);
		return nullptr;
	}

	CustomFollow* CustomFollow::create(Node* followNode, Rect  marginRect){
		CustomFollow *follow = new CustomFollow();
		follow->mMarginRect = marginRect;
		if (follow && follow->initWithTarget(followNode, Rect::ZERO)){
			follow->autorelease();
			return follow;
		}
		CC_SAFE_DELETE(follow);
		return nullptr;
	}
	
	void CustomFollow::step(float dt){
		
		CC_UNUSED_PARAM(dt);

		if (_boundarySet)
		{
			if (_boundaryFullyCovered)
				return;

			Point tempPos = _halfScreenSize - _followedNode->getPosition();

			float x = clampf(tempPos.x, _leftBoundary, _rightBoundary);
			float y = clampf(tempPos.y, _bottomBoundary, _topBoundary);

			if (mType == CustomFollowXOnly){
				y = _target->getPositionY();
			}
			else if (mType == CustomFollowYOnly){
				x = _target->getPositionX();
			}

			_target->setPosition(Point(x, y));

		}
		else
		{
			//Point calcPos = _target->convertToWorldSpace(_followedNode->getPosition());

			/*if (mMarginRect.containsPoint(calcPos)){
				return;
			}*/

			//float x = _halfScreenSize.x - _followedNode->getPositionX();
			//float y = _halfScreenSize.y - _followedNode->getPositionY();

			auto pos = _halfScreenSize - _followedNode->getPosition();

			if (mType == CustomFollowXOnly){
				pos.y = _target->getPositionY();
			}
			else if (mType == CustomFollowYOnly){
				pos.x = _target->getPositionX();
			}

			_target->setPosition(pos);
			//_target->setPosition(_halfScreenSize - _followedNode->getPosition());
		}
	}

	CustomFollow* CustomFollow::clone() const
	{
		// no copy constructor
		auto a = new CustomFollow();
		a->initWithTarget(_followedNode, _worldRect);
		a->autorelease();
		return a;
	}

	CustomFollow* CustomFollow::reverse() const
	{
		return clone();
	}

	bool CustomFollow::initWithTarget(Node *followedNode, const Rect& rect/* = Rect::ZERO*/)
	{
		CCASSERT(followedNode != nullptr, "");

		followedNode->retain();
		_followedNode = followedNode;
		_worldRect = rect;
		if (rect.equals(Rect::ZERO))
		{
			_boundarySet = false;
		}
		else
		{
			_boundarySet = true;
		}

		_boundaryFullyCovered = false;

		Size winSize = Director::getInstance()->getWinSize();
		_fullScreenSize = Vec2(winSize.width, winSize.height);
		_halfScreenSize = _fullScreenSize * 0.5f;

		if (_boundarySet)
		{
			_leftBoundary = -((rect.origin.x + rect.size.width) - _fullScreenSize.x);
			_rightBoundary = -rect.origin.x;
			_topBoundary = -rect.origin.y;
			_bottomBoundary = -((rect.origin.y + rect.size.height) - _fullScreenSize.y);

			if (_rightBoundary < _leftBoundary)
			{
				// screen width is larger than world's boundary width
				//set both in the middle of the world
				_rightBoundary = _leftBoundary = (_leftBoundary + _rightBoundary) / 2;
			}
			if (_topBoundary < _bottomBoundary)
			{
				// screen width is larger than world's boundary width
				//set both in the middle of the world
				_topBoundary = _bottomBoundary = (_topBoundary + _bottomBoundary) / 2;
			}

			if ((_topBoundary == _bottomBoundary) && (_leftBoundary == _rightBoundary))
			{
				_boundaryFullyCovered = true;
			}
		}

		return true;
	}

	bool CustomFollow::isDone() const
	{
		return (!_followedNode->isRunning());
	}

	void CustomFollow::stop()
	{
		_target = nullptr;
		Action::stop();
	}
}