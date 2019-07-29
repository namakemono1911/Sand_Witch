/*****************************************************************************
fade.cpp
Aythor	: 上野　匠
Data	: 2016_09_28
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "fade.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define FADE_POS_X		(SCREEN_WIDTH * 0.5f)	//ポリゴンの表示位置X
#define FADE_POS_Y		(SCREEN_HEIGHT * 0.5f)	//ポリゴンの表示位置Y

#define FADE_WIDTH		(SCREEN_WIDTH)			//ポリゴンの幅
#define FADE_HEIGHT		(SCREEN_HEIGHT)			//ポリゴンの高さ

#define SPEED_MAX		(30)					//最高速度
#define ROT_MAX			(0.0005)				//最高角度

#define NUM_HITBOX		(3)						//ヒットボックスの数

#define TEXTURE_WIDTH	(1.0f)					//テクスチャ一つ分の幅
#define TEXTURE_HEIGHT	(1.0f)					//テクスチャ一つ分の高さ

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON	conf;		//ポリゴンの各種設定
	TEXTURE		tex;		//テクスチャ設定
	D3DXCOLOR	color;		//色
	float		time;		//フェードの時間
	bool		action;		//trueで動いてる
	MODE		nextMode;	//フェード後のモード
}FADE;

FADE fade;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFade ( LPDIRECT3DDEVICE9 pDevice );
void	opeFade			( void );
void	updateFadeIn	( void );
void	updateFadeOut	( void );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureFade = NULL;			//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9	g_pVtxBufferFade = NULL;		//頂点バッファ管理インターフェイス

FADE_MODE		g_fadeMode = FADE_MODE_NONE;			//フェードモード

//////////////////////////////////////////////////////////////////////////////
// 変数名	: initFade
// 返り値	:
// 説明		: デバイスの初期化
//////////////////////////////////////////////////////////////////////////////
void	initFade	( void )
{	
	//変数宣言

	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	initRotPolygon(&fade.conf,
		D3DXVECTOR3(FADE_POS_X, FADE_POS_Y, 0.f),
		D3DXVECTOR3(FADE_WIDTH, FADE_HEIGHT, 0.f));

	initTexture(&fade.tex,
		D3DXVECTOR2(0.f, 0.f),
		D3DXVECTOR2(TEXTURE_WIDTH, TEXTURE_HEIGHT));

	fade.action = false;

	//デバイス取得
	makeVertexFade(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: uninitFade
// 返り値	:
// 説明		: デバイスの終了
//////////////////////////////////////////////////////////////////////////////
void uninitFade ( void )
{
	//テクスチャインターフェイスの解放
	if(g_pTextureFade != NULL)
	{
		g_pTextureFade->Release();
		g_pTextureFade = NULL;
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferFade != NULL)
	{
		g_pVtxBufferFade->Release();
		g_pVtxBufferFade = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: updateFade
// 返り値	:
// 説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	updateFade	( void )
{
	//変数宣言
	VERTEX2D	*pVtx;		

	//モードごと処理
	switch(g_fadeMode)
	{
	case FADE_IN:
		{
			updateFadeIn();
			break;
		}

	case FADE_OUT:
		{
			updateFadeOut();
			break;
		}

	case FADE_MODE_NONE:
		{
			return;
		}
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(2D座標・右回り)
	setRotBuffer(pVtx, fade.conf);

	//頂点カラーの設定(0~155の整数値)
	pVtx[0].color = fade.color;
	pVtx[1].color = fade.color;
	pVtx[2].color = fade.color;
	pVtx[3].color = fade.color;
	
	//テクスチャ頂点座標の設定(0~1)
	setTexture(pVtx, fade.tex);

	//私のこころアーンロック♪
	g_pVtxBufferFade->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: updateFadeIn
// 返り値	:
// 説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	updateFadeIn	( void )
{
	//透過度減算
	fade.color.a -= fade.time;

	if(fade.color.a <= 0.f)
	{
		fade.color.a = 0.f;
		g_fadeMode = FADE_MODE_NONE;
		fade.action = false;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: updateFadeOut
// 返り値	:
// 説明		: 更新
//////////////////////////////////////////////////////////////////////////////
void	updateFadeOut	( void )
{
	//透過度加算
	fade.color.a += fade.time;
	
	if(fade.color.a >= 1.f)
	{
		fade.color.a = 1.f;
		g_fadeMode = FADE_MODE_NONE;
		fade.action = false;
		setMode(fade.nextMode);
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: setFade
// 返り値	:
// 説明		: フェードの設定
//////////////////////////////////////////////////////////////////////////////
void	setFade	( char *texAdd, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR2 texPos, D3DXVECTOR2 texSize )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//テクスチャの読み込み
	if(texAdd != NULL)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, texAdd, &g_pTextureFade)))
		{
			MessageBox(NULL, "Test", "エラー", MB_OK);
		}
	}

	//変数代入
	initRotPolygon(&fade.conf, pos, size);
	initTexture(&fade.tex, texPos, texSize);
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: startFadeIn
// 返り値	:
// 説明		: フェードの設定
//////////////////////////////////////////////////////////////////////////////
void	startFadeIn	( int time, D3DXCOLOR color )
{
	if(fade.action == false)
	{
		fade.time = 1.f / (float)time;
		fade.color = color;

		g_fadeMode = FADE_IN;

		fade.action = true;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: startFadeOut
// 返り値	:
// 説明		: フェードの設定
//////////////////////////////////////////////////////////////////////////////
void	startFadeOut	( int time, D3DXCOLOR color, MODE nextMode )
{
	if(fade.action == false)
	{
		fade.time = 1.f / (float)time;
		fade.color = color;

		g_fadeMode = FADE_OUT;

		fade.action = true;

		fade.nextMode = nextMode;
	}
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: setFadeMode
// 返り値	:
// 説明		: フェードモード途中切り替え
//////////////////////////////////////////////////////////////////////////////
void	setFadeMode	( FADE_MODE mode )
{
	g_fadeMode = mode;
}

//////////////////////////////////////////////////////////////////////////////
// 変数名	: drawFade
// 返り値	:
// 説明		: デバイスの初期化
//////////////////////////////////////////////////////////////////////////////
void	drawFade	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferFade, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,g_pTextureFade);

	//ポリゴンの描画
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		NUM_POLYGON				//ポリゴンの数
		);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexFade
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFade ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	VERTEX2D	*pVtx = NULL;;		//仮想アドレス用ポインタ

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEX,	//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,				//頂点バッファの使用方法
			FVF_VERTEX_2D,					//
			D3DPOOL_MANAGED,				//メモリ管理方法
			&g_pVtxBufferFade,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferFade->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(2D座標・右回り)
	setRotBuffer(pVtx, fade.conf);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0~155の整数値)
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 0);
	
	//テクスチャ頂点座標の設定(0~1)
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//私のこころアーンロック♪
	g_pVtxBufferFade->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getFadeAction
//返り値	: 
//説明		: フェード中かを取得
//////////////////////////////////////////////////////////////////////////////
bool	getFadeAction	( void )
{
	return fade.action;
}