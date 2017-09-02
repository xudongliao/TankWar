#include "soundEngine.h"
#include "gvarible.h"

int g_BGpercent = 60;
int g_SEpercent = 100;

auto audio = SimpleAudioEngine::getInstance();

void soundEngine::PreLoadBGM() {

	const char* BGAudio[] = { STARTBGM, SELECTBGM ,BATTELBGM, SETTINGBGM };
	for (auto name : BGAudio) {
		SimpleAudioEngine::getInstance()->preloadBackgroundMusic(name);
	}
}

void soundEngine::KindsOfBgm(char * pFilename, double percentage)
{
	audio->setBackgroundMusicVolume((double)g_BGpercent/100);
	audio->playBackgroundMusic(pFilename, true);
}

void soundEngine::PauseBGMusic()
{
	audio->pauseBackgroundMusic();
}

void soundEngine::ResumeBGMusic()
{
	audio->resumeBackgroundMusic();
}

void soundEngine::StopBGMusic(char * pFilename)
{
	audio->stopBackgroundMusic();
}

void soundEngine::SetBGVolume(int percentage)
{
	g_BGpercent = percentage;
	audio->setBackgroundMusicVolume((double)percentage / 100);
}

void soundEngine::PreLoadSE() {

	const char* SEAudio[] = { E_Bullet, E_Enemy_Bomb,  E_Hit_Obstacle, E_Metal, E_Obstacle_Bomb, 
		E_Player_Bomb, E_ClickOn, E_MoveBack,E_GG };
	for (auto name : SEAudio) {
		SimpleAudioEngine::getInstance()->preloadEffect(name);
	}
}

void soundEngine::KindsOfSE(char * pFilename, double percentage)
{
	audio->setEffectsVolume((double)percentage / 100);
	audio->playEffect(pFilename);
}


void soundEngine::PauseSE()
{
	audio->pauseAllEffects();
}

void soundEngine::ResumeSE()
{
	audio->resumeAllEffects();
}

void soundEngine::StopSEMusic()
{
	audio->stopAllEffects();
}

void soundEngine::SetSEVolume(int percentage)
{
	g_SEpercent = percentage;
	audio->setEffectsVolume((double)percentage / 100);
}