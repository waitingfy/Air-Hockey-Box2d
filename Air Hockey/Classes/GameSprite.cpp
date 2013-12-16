#include "GameSprite.h"

GameSprite::GameSprite(void)
{
	_screenSize = CCDirector::sharedDirector()->getWinSize();
}

GameSprite::~GameSprite(void)
{
}

GameSprite* GameSprite::spriteWithTexture(CCTexture2D* aTexture)
{
	GameSprite* pSprite = new GameSprite();
	pSprite->initWithTexture( aTexture );
	pSprite->autorelease();

	return pSprite;
}

float GameSprite::radius(){
	return getTexture()->getContentSize().width * 0.5f;
}

void GameSprite::setPosition(const CCPoint& pos){
	CCSprite::setPosition(pos);
	if(!_nextPosition.equals(pos)){
		_nextPosition = pos;
	}
}