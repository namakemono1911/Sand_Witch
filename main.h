/*****************************************************************************
main.h
Aythor	: 上野　匠
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef MAIN_H
#define MAIN_H

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define SCREEN_WIDTH	(1280)		//ウィンドウの幅
#define SCREEN_HEIGHT	(720)		//ウィンドウの高さ

#define FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)	//2Dポリゴン設定
#define NUM_VERTEX		(4)			//頂点数
#define NUM_VERTEXLIST	(6)			//TRIANGLELIST用
#define NUM_POLYGON		(2)			//ポリゴン数

#define SAFE_RELEASE(x) { if(x){(x)->Release(); (x) = NULL;} }

#define PI				(3.141592f)	//円周率

//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <d3dx9.h>
#define	DisableLoad	(0x0800)
#include <dinput.h>
#include <XAudio2.h>

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR color;
	D3DXVECTOR2 tex;
}VERTEX2D;		//ポリゴン描写用構造体

typedef enum
{
	TITLE_MODE = 0,			//タイトルモード
	STAGE_SELECT,
	GAME_MODE,				//ゲームモード
	RESULT_MODE,			//リザルトモード
	MODE_MAX,				//モード最大数
	MODE_NULL				//null
}MODE;

//////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DDEVICE9 getDevice ( void );
void	setMode	(MODE mode);
MODE	getMode	(void);

//////////////////////////////////////////////////////////////////////////////
//ライブラリのリンク
//////////////////////////////////////////////////////////////////////////////
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "winmm.lib")		//システム時刻取得に必要
#pragma comment (lib, "dinput8.lib")	//入力装置ライブラリ

#endif