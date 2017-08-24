#include "soundEngine.h"

int g_BGpercent = 75;
auto audio = SimpleAudioEngine::getInstance();

void soundEngine::PreLoadBGM() {

	const char* BGAudio[] = {STARTBGM, SELECTBGM ,BATTELBGM, SETTINGBGM};
	for (auto name : BGAudio) {
		SimpleAudioEngine::getInstance()->preloadEffect(name);
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
	audio->stopBackgroundMusic(pFilename);
}

void soundEngine::SetBGVolume(int percentage)
{
	g_BGpercent = percentage;
	audio->setBackgroundMusicVolume((double)percentage / 100);
}

void soundEngine::PreLoadSE() {

	const char* SEAudio[] = { E_Add_Life, E_Bullet, E_Enemy_Bomb,  E_Hit_Obstacle, E_Metal, E_Obstacle_Bomb, 
		E_Player_Bomb, E_Slip, E_ClickOn, E_MoveBack,E_GG };
	for (auto name : SEAudio) {
		SimpleAudioEngine::getInstance()->preloadEffect(name);
	}
}

void soundEngine::KindsOfSE(char * pFilename)
{
	audio->playEffect(pFilename, 1.0f, 0, 1.0f);
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
	audio->setEffectsVolume((double)percentage / 100);
}