/*****************************************************************************
gameUI.cpp
Aythor	: 上野　匠
Data	: 2017_05_21
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bulletUI.h"
#include "gameUI.h"
#include "texture.h"

#include "stage.h"
#include "notes.h"
#include "castle.h"

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
float g_par = 0;

//////////////////////////////////////////////////////////////////////////////
//関数名	: initGameUI
//返り値	: 
//説明		: ゲームUI初期化
//////////////////////////////////////////////////////////////////////////////
void	initGameUI	( void )
{
	//弾UI初期化
	initBulletUI();
	setBulletUI(
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 25.5, SCREEN_HEIGHT / 100.0f * 15.5, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 24, SCREEN_HEIGHT / 100.0f * 6.5, 0.f),
		D3DCOLOR_RGBA(192, 255, 192, 255));
	setBulletUI(
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 25.5, SCREEN_HEIGHT / 100.0f * 8, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH / 100.0f * 24, SCREEN_HEIGHT / 100.0f * 7, 0.f),
		D3DCOLOR_RGBA(192, 192, 255, 255));

	// UI
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

	// 弾
	SetTexture(7 , SCREEN_WIDTH / 100.0f * 4 , SCREEN_HEIGHT / 100.0f * 4 * 3.1f, SCREEN_WIDTH / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);
	SetTexture(8 , SCREEN_WIDTH / 100.0f * 4 *2.1f, SCREEN_HEIGHT / 100.0f * 4 * 3.1f, SCREEN_WIDTH / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);
	SetTexture(9 , SCREEN_WIDTH / 100.0f * 4 * 1.55f , SCREEN_HEIGHT / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);
//	SetTexture(10 , SCREEN_WIDTH / 100.0f * 4 *2.1f, SCREEN_HEIGHT / 100.0f * 4, SCREEN_WIDTH / 100.0f * 4 , SCREEN_WIDTH / 100.0f * 4 , 0 , 0 , 1 , 1 , 2);

	// 進行度
	SetTexture(11 , SCREEN_WIDTH / 100.0f * 58 , SCREEN_HEIGHT / 100.0f * 4, SCREEN_WIDTH / 100.0f * 40 , SCREEN_HEIGHT / 100.0f * 15 , 0 , 0 , 1 , 1 , 2);
	SetTexture(12 , SCREEN_WIDTH / 100.0f * 60, SCREEN_HEIGHT / 100.0f * 6, SCREEN_WIDTH / 100.0f * 5 , SCREEN_WIDTH / 100.0f * 5 , 0 , 0 , 1 , 1 , 2);

	//お城初期化
	InitCastle(0);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitGameUI
//返り値	: 
//説明		: ゲームUI終了
//////////////////////////////////////////////////////////////////////////////
void	uninitGameUI	( void )
{
	//弾UI終了
	uninitBulletUI();

	//お城終了
	UninitCastle();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateGameUI
//返り値	: 
//説明		: ゲームUI更新
//////////////////////////////////////////////////////////////////////////////
void	updateGameUI	( void )
{
	//弾UI更新
	updateBulletUI();

	// 
	int i = 0;
	for(i = 1 ; i < 6 ; i++)
	{
		//MoveUVTexture(i , 0.0002f , 1.0f);					// テクスチャのUV移動
	}

	// 進行度で更新
	float fPosx = 0.0f;
	// 最大時間と取得
	int nMaxTime = GetTimeGame(0);
	// 現在の時間取得
	int nNowTime = GetTimeGameNow();

	if(nNowTime > nMaxTime)
	{
		nNowTime = nMaxTime;
	}

	// 進行度を百分率で出す
	g_par = (float)nNowTime / (float)nMaxTime;
	fPosx = 31.5f * g_par;
	// SCREEN_WIDTH / 100.0f * 60から割合で足してあげる
	fPosx = SCREEN_WIDTH / 100.0f * 90- SCREEN_WIDTH / 100.0f * fPosx;
	if(fPosx <= SCREEN_WIDTH / 100.0f * 60)
	{
		fPosx = SCREEN_WIDTH / 100.0f * 60;
	}

		// 12番目に渡す。
	SetPosTexture(12 , fPosx , SCREEN_HEIGHT / 100.0f * 6);					// テクスチャのポジショ指定

	//お城更新
	UpdateCastle();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawGameUI
//返り値	: 
//説明		: ゲームUI描画
//////////////////////////////////////////////////////////////////////////////
void	drawGameUI	( void )
{
	//弾UI描画
	drawBulletUI();

	DrawTexture(2);

	//お城描画
	DrawCastle();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getParcent
//返り値	: 
//説明		: ゲーム進行度取得
//////////////////////////////////////////////////////////////////////////////
float	getParcent(void)
{
	return g_par;
}