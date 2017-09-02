#include "Bomb.h"
#include <string>

using namespace std;

Bomb::Bomb() {}

Bomb::~Bomb() {}

Bomb* Bomb::create(BombType type, int score)
{
	Bomb *pBomb = new Bomb();
	if (pBomb&&pBomb->init(type,score))
	{
		pBomb->autorelease();
		return pBomb;
	}
	else {
		delete pBomb;
		pBomb = NULL;
		return NULL;
	}
}

bool Bomb::init(BombType type, int score)
{
	bool bflag=false;
	do
	{
		auto cache = SpriteFrameCache::getInstance();
		cache->addSpriteFramesWithFile("Sprite/bomb/bomb.plist", "Sprite/bomb/bomb.png");


		int size;
		string name;

		_type = type;
		_score = score;
		switch (_type)
		{
		case kPlayerTankBomb:
		case kEnemyTankBomb:
		case kHomeBomb:
			size = 7;
			name = "tankbomb";
			break;
		case kBulletBomb:
			size = 3;
			name = "bulletbomb";
			break;
		default:
			break;
		}
		auto str = __String::createWithFormat("%s_01.png", name.c_str())->getCString();
		this->initWithSpriteFrameName(str);

		Vector<SpriteFrame*> animFrames(size);
		for (int i = 1; i < size + 1; i++)
		{
			auto str = __String::createWithFormat("%s_%02d.png", name.c_str(), i)->getCString();
			auto frame = cache->getSpriteFrameByName(str);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, 0.08f);
		auto actions = Sequence::create(
			Animate::create(animation),
			RemoveSelf::create(),
			nullptr);
		this->runAction(actions);
		bflag = true;
	} while (0);
	return bflag;
}

