/*****************************************************************************
game.cpp
Aythor	: 上野　匠
Data	: 2017_05_20
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "game.h"
#include "gameBG.h"
#include "bossHp.h"
#include "bullet.h"
#include "bulletEffect.h"
#include "gameUI.h"
#include "castle.h"
#include "bulletUI.h"
#include "player.h"
#include "notes.h"
#include "stage.h"
#include "gate.h"
#include "fade.h"
#include "input.h"
#include "inputX.h"
#include "texture.h"
#include "sound.h"
#include "activate.h"
#include "fcoh.h"
#include "explo.h"
#include "tutorial.h"

#include "boss.h"
#include "bulletBoss.h"
#include "nucleusBoss.h"
#include "human.h"

#include "result.h"

#include "heart.h"
#include "warning.h"

#include "effect.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define COUNT	(30)	//必殺技後ゲーム復帰までの時間

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
int	g_count = 0;			//カウントダウン
bool g_countFlag = false;	//カウントダウンフラグ
STATE g_gameState = NONE;	//ゲームの状態
int	g_combo = 0;			//コンボ数
int g_maxCombo = 0;			//最大コンボ

//////////////////////////////////////////////////////////////////////////////
//関数名	: initGame
//返り値	: 
//説明		: ゲーム初期化
//////////////////////////////////////////////////////////////////////////////
void	initGame	( void )
{
	//変数初期化
	g_combo = 0;
	g_countFlag = false;
	g_count = 0;
	g_gameState = NONE;
	g_maxCombo = 0;

	InitEffect();


	//UI初期化
	InitTexture();
	initGameUI();

	// 敵配置の初期化
	ReStage();

	//チュートリアル初期化
	if (getStgNum() == STAGE_00)
	{
		initTuto();
	}

	//フェードイン
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	InitWarning();
	InitHeart();

	//HP初期化
	initBossHp();

	//プレイヤー初期化
	InitPlayer();

	//弾初期化
	initBullet();

	//弾エフェクト初期化
	initBulletEffect();

	//爆発初期化
	initExplo();

	//ステージ初期化
	InitNotes();

	//門初期化
	InitGate();

	//魔法発動初期化
	initActive();

	//必殺技初期化
	initFcoh();

	// 人初期化
	InitHuman();

	InitBoss();
	InitBulletBoss();
	InitNucleusBoss();

	SetTexture(0 , 0.0f , 0.0f , SCREEN_WIDTH , SCREEN_HEIGHT / 100.0f * 23.6f , 0 , 0 , 1 , 1 , 1);
	
	
	SetTexture(1 , 10.0f , SCREEN_HEIGHT / 100.0f * 22.6f ,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	
	SetTexture(2 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	SetTexture(3 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 2,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	SetTexture(4 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 3,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);
	SetTexture(5 , 10.0f , SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4,
		SCREEN_WIDTH - 10.0f, 30.0f , 0 , 0 , 1 , 1 , 0);

	PlaySound(GAME_BGM_01);

	//背景画像設定
	initGameBG();
	setGameBGType(GAMEBG_VILLAGE);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitGame
//返り値	: 
//説明		: ゲーム終了
//////////////////////////////////////////////////////////////////////////////
void	uninitGame	( void )
{
	//必殺技終了
	uninitFcoh();

	//魔法発動終了
	uninitActive();

	//門終了
	UninitGate();

	//チュートリアル終了
	if (getStgNum() == STAGE_00)
	{
		uninitTuto();
	}

	//ステージ終了
	UninitNotes();

	//爆発終了
	uninitExplo();

	//弾エフェクト終了
	uninitBulletEffect();

	//弾終了
	uninitBullet();

	//プレイヤー終了
	UninitPlayer();

	//HP終了
	uninitBossHp();

	//UI終了
	uninitGameUI();

	// 人終了
	UninitHuman();

	//ボス終了
	UninitBoss();
	UninitBulletBoss();
	UninitNucleusBoss();

	UninitTexture();

	//背景終了
	uninitGameBG();

	UninitWarning();
	UninitHeart();

	UninitEffect();

	StopSound();

	resetStgNum();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateGame
//返り値	: 
//説明		: ゲーム更新
//////////////////////////////////////////////////////////////////////////////
void	updateGame	( void )
{
	//必殺技更新
	updateFcoh();

	//必殺技中は更新されない
	if(getFcohFlag() == false && g_count <= 0)
	{
		//背景更新
		updateGameBG();

		//HP更新
		updateBossHp();

		//プレイヤー更新
		UpdatePlayer();

		//弾更新
		updateBullet();

		//弾エフェクト更新
		updateBulletEffect();

		//爆発更新
		updateExplo();

		//魔法発動更新
		updateActive();

		//ステージ更新
		UpdateNotes();

		//チュートリアル更新
		if (getStgNum() == STAGE_00)
		{
			updateTuto();
		}

		//門更新
		UpdateGate();

		UpdateTexture();
	
		//UI更新
		updateGameUI();

		// 人更新
		UpdateHuman();

		UpdateBoss();
		UpdateBulletBoss();
		UpdateNucleusBoss();

		UpdateWarning();
		UpdateHeart();

		UpdateEffect();

		//ボス出現
		if(GetKeyboardTrigger(DIK_4))
		{
			SetWarning(0 , WARNING_BOSS);
			SetBoss(SCREEN_WIDTH , ((SCREEN_HEIGHT / 100.0f * 23.6f + LINE_HEIGHT * 4) + ( SCREEN_HEIGHT / 100.0f * 22.6f )) / 2.0f + 5.0f, BOSS_ONE);
		}
	}
	if(getFcohFlag() == true)
	{
		g_count = COUNT;
		g_countFlag = true;
	}

	if(g_count > 0)
	{
		g_count--;
	}
	else if(g_countFlag == true)
	{
		g_count = 0;
		damageFcoh();
		g_countFlag = false;
	}

	//シーン遷移
	if (g_gameState == VICTORY)				//勝った場合
	{
		SetAchiveValue(100);				//達成度設定
		SetComboValue(g_maxCombo);			//コンボ数設定
		SetPhysicalValue(GetCastleHp());	//残体力設定
		//startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), RESULT_MODE);
	}
	if (g_gameState == LOSE)			//負けた場合
	{
		SetAchiveValue(getParcent());	//達成度設定
		SetComboValue(g_maxCombo);		//コンボ数設定
		SetPhysicalValue(100);			//残体力設定
		//startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), RESULT_MODE);
	}
	if (GetKeyboardTrigger(DIK_N))
	{
		SetAchiveValue(getParcent());	//達成度設定
		SetComboValue(g_maxCombo);		//コンボ数設定
		SetPhysicalValue(100);			//残体力設定
		//startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), RESULT_MODE);
		setMode(RESULT_MODE);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawGame
//返り値	: 
//説明		: ゲーム描画
//////////////////////////////////////////////////////////////////////////////
void	drawGame	( void )
{
	//背景描画
	drawGameBG();

	DrawTexture(1);
	DrawTexture(0);

	//魔法発動描画
	drawActive();

	//ステージ描画
	DrawNotes();

	//プレイヤー描画
	DrawPlayer();

	//爆発描画
	drawExplo();

	//魔法エフェクト描画
	drawBulletEffect();

	//弾描画
	drawBullet();

	//hp描画
	//drawBossHp();

	//門更新
	DrawGate();

	//必殺技
	drawFcoh();

	//UI描画
	drawGameUI();

	DrawHeart();

	// 人描画
	DrawHuman();

	DrawBoss();
	DrawBulletBoss();
	DrawNucleusBoss();

	DrawWarning();

	DrawEffect();

	//チュートリアル描画
	if (getStgNum() == STAGE_00)
	{
		drawTuto();
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setGameState
//返り値	: 
//説明		: ゲーム状態設定
//////////////////////////////////////////////////////////////////////////////
void	setGameState(STATE state)
{
	g_gameState = state;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: addCombo
//返り値	: 
//説明		: コンボ加算
//////////////////////////////////////////////////////////////////////////////
void	addCombo(void)
{
	g_combo++;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: resetCombo
//返り値	: 
//説明		: コンボリセット
//////////////////////////////////////////////////////////////////////////////
void	resetCombo(void)
{
	if (g_maxCombo < g_combo)
	{
		g_maxCombo = g_combo;
	}
	g_combo = 0;
}