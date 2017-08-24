#pragma once
#include "SimpleAudioEngine.h"
#include "gvarible.h"

#define STARTBGM "music/STARTBGM.mp3"
#define SELECTBGM "music/backMusic.mp3"
#define BATTELBGM "music/battlebgm1.mp3"
#define SETTINGBGM "music/STARTBGM.mp3"

#define E_Add_Life ""
#define E_Bullet ""
#define E_Enemy_Bomb ""
#define E_Hit_Obstacle ""
#define E_Metal ""
#define E_Obstacle_Bomb ""
#define E_Player_Bomb ""
#define E_Slip ""
#define E_ClickOn "music/E_Clickon.mp3"
#define E_MoveBack "music/E_MoveBack.mp3"
#define E_GG ""

using namespace CocosDenshion;

class soundEngine
{

public:

	static void PreLoadBGM(); //‘§º”‘ÿ±≥æ∞“Ù¿÷
	static void KindsOfBgm(char * pFilename, double percentage); //±≥æ∞“Ù¿÷£∫≤•∑≈º∞»∑∂®“Ù¿÷÷÷¿‡
	static void SetBGVolume(int percentage); //±≥æ∞“Ù¿÷£∫…Ë÷√≤•∑≈“Ù¡ø
	static void PauseBGMusic(); //‘›Õ£±≥æ∞“Ù¿÷
	static void ResumeBGMusic(); //ª÷∏¥±≥æ∞“Ù¿÷
	static void StopBGMusic(char * pFilename);  //Õ£÷π±≥æ∞“Ù¿÷

	static void PreLoadSE(); //‘§º”‘ÿ“Ù–ß
	static void KindsOfSE(char * pFilename, double percentage); //“Ù–ß£∫≤•∑≈º∞»∑∂®“Ù–ß÷÷¿‡
	static void SetSEVolume(int percentage); //“Ù–ß£∫…Ë÷√≤•∑≈“Ù¡ø
	static void PauseSE(); //‘›Õ£»´≤ø“Ù–ß
	static void ResumeSE(); //ª÷∏¥»´≤ø“Ù–ß
	static void StopSEMusic();  //Õ£÷π»´≤ø“Ù–ß

	friend class HelloWorld;
	friend class settingScene;
};

