#include "GameScene.h"

Scene * GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

void GameScene::update()
{
}

void GameScene::updateScore(int delta)
{
	_score = _score + delta;
}
