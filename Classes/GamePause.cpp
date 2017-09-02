#include "GamePause.h"
#include "GameScene.h"//重新开始游戏的头文件  
#include "GameOpenScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GamePause.h"
using namespace ui;

GamePause::GamePause()
{
}


GamePause::~GamePause()
{
}

//传入一个renderTexture   
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景   
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。  
Scene* GamePause::createScene(RenderTexture* sqr,int rank)
{

	auto scene = Scene::create();
	auto layer = GamePause::createWithLevel(rank);
	scene->addChild(layer, 1);//把游戏层放上面，我们还要在这上面放按钮  


							  //增加部分：使用Game界面中截图的sqr纹理图片创建Sprite  
							  //并将Sprite添加到GamePause场景层中  
							  //得到窗口的大小  
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto back_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2)); //放置位置,这个相对于中心位置。  
	back_spr->setFlipY(true);            //翻转，因为UI坐标和OpenGL坐标不同  
	//back_spr->setColor(cocos2d::ccGRAY); //图片颜色变灰色  
	scene->addChild(back_spr);
	
	

	return scene;
}

GamePause * GamePause::createWithLevel(int rank)
{
	auto gamePause = new GamePause();
	if (gamePause && gamePause->init(rank)) {
		gamePause->autorelease();
		return gamePause;
	}
	else {
		CC_SAFE_DELETE(gamePause);
		return nullptr;
	}
	
}

bool GamePause::init(int rank)
{

	if (!Layer::init())
	{
		return false;
	}
	m_rank = rank;
	auto rootNode = CSLoader::createNode("GamePause.csb");
	this->addChild(rootNode);
	auto button_continue = (Button*)rootNode->getChildByName("Button_1");
	auto button_restart = (Button*)rootNode->getChildByName("Button_2");
	auto button_backToMainScene = (Button*)rootNode->getChildByName("Button_3");
	button_continue->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			menuContinue();
		}
	});
	button_restart->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			menuRestart();
		}
	});
	button_backToMainScene->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			menuLogin();
		}
	});
	return true;
}
void GamePause::menuContinue()
{
	Director::getInstance()->popScene();

}
//重新开始游戏  
void  GamePause::menuRestart()
{
	Director::getInstance()->replaceScene(GameScene::createSceneWithLevel(m_rank));
}
//回主界面  
void  GamePause::menuLogin()
{
	Director::getInstance()->replaceScene(GameOpen::createScene());
}
