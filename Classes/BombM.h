#pragma once
#include "cocos2d.h"
#include "Bomb.h"

USING_NS_CC;

/* 爆炸管理类 */
class BombM : public Layer
{
public:
	BombM();
	~BombM();
	CREATE_FUNC(BombM);

	//type 爆炸类型
	//pos 爆炸位置
	//score 爆炸后显示的分数
    //创建爆炸
	void createBomb(BombType type, Vec2 pos, int score = 0);
	//暂停游戏（暂停播放所有爆炸动画）
	void pauseGame();
	//继续游戏（继续播放所有爆炸动画)
	void resumeGame();
};