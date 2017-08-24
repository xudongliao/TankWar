#include "MenuScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;
cocos2d::Scene * MenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}
bool MenuScene::init() {
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("MenuScene.csb");
	addChild(rootNode);
	return true;
}