#include "HelloWorldScene.h"
#include "GameScene.h"
#include "GameSelect.h"
USING_NS_CC;
using namespace ui;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	/**  you can create scene with following comment code instead of using csb file.
	// 1. super init first
	if ( !Layer::init() )
	{
	return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.
	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
	"CloseNormal.png",
	"CloseSelected.png",
	CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
	origin.y + closeItem->getContentSize().height/2));
	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	/////////////////////////////
	// 3. add your codes below...
	// add a label shows "Hello World"
	// create and initialize a label

	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
	origin.y + visibleSize.height - label->getContentSize().height));
	// add the label as a child to this layer
	this->addChild(label, 1);
	// add "HelloWorld" splash screen"
	auto sprite = Sprite::create("HelloWorld.png");
	// position the sprite on the center of the screen
	sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	// add the sprite as a child to this layer
	this->addChild(sprite, 0);
	**/

	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("MainScene.csb");

	addChild(rootNode);

	soundEngine::PreLoadBGM(); //预加载背景音乐
	soundEngine::PreLoadSE();  //预加载音效

	soundEngine::KindsOfBgm(STARTBGM, (double)g_BGpercent / 100);
	auto button1 = (ui::Button*)rootNode->getChildByName("Button_1");//开始游戏
	button1->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			//更换成开始游戏游戏场景
			//构架StartGame类，在这个类中运行游戏，作为游戏进行时的场景
			Director::getInstance()->replaceScene(TransitionSlideInB::create(0.3f,GameSelect::createScene()));
		}
	});
	auto button3 = (ui::Button*)rootNode->getChildByName("Button_2");//游戏设置
	button3->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {

			soundEngine::StopBGMusic(STARTBGM);
			soundEngine::KindsOfSE(E_ClickOn, (double)g_SEpercent / 100);
			//更换成游戏设置场景
			this->addChild(settingScene::createScene());
		}
	});
	auto button4 = (ui::Button*)rootNode->getChildByName("Button_3");//结束游戏
	button4->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			Director::getInstance()->end();
		}
	});


	return true;
}