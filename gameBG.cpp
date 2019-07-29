/*****************************************************************************
gameBG.cpp
Aythor	: 上野　匠
Data	: 2017_06_04
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "gameBG.h"
#include "stage.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON		conf;		//ポリゴンの各種設定
	TEXTURE			tex;		//テクスチャ設定
	GAME_BG_TYPE	type;		//背景画像の種類
}GAME_BG;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexGameBG ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureGameBG = NULL;		//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferGameBG = NULL;	//頂点バッファ管理インターフェイス

GAME_BG		g_gameBG;		//背景構造体
const char	*texNameGameBG[GAMEBG_MAX] =
{
	"data/TEXTURE/GAME/BG/stageBG01.jpg",
	"data/TEXTURE/GAME/BG/stageBG02.jpg",
	"data/TEXTURE/GAME/BG/stageBG03.jpg",
};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initGameBG
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initGameBG( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	initRotPolygon(&g_gameBG.conf,
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f));

	initTexture(&g_gameBG.tex,
		D3DXVECTOR2(0.f, 0.f),
		D3DXVECTOR2(1.f, 1.f));
	
	//テクスチャの読み込み
	int num;
	switch(getStgNum())
	{
	case 0:
	case 1:
	case 2:
	case 3:
		num = 0;
		break;

	case 4:
	case 5:
	case 6:
		num = 1;
		break;

	case 7:
	case 8:
	case 9:
		num = 2;
		break;
	}

	if(FAILED(D3DXCreateTextureFromFile(pDevice, texNameGameBG[num], &g_pTextureGameBG)))
	{
		MessageBox(NULL, "bg", "エラー", MB_OK);
	}

	//デバイス取得
	makeVertexGameBG(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitGameBG
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitGameBG( void )
{
	//テクスチャインターフェイスの解放
	if(g_pTextureGameBG != NULL)
	{
		g_pTextureGameBG->Release();
		g_pTextureGameBG = NULL;
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferGameBG != NULL)
	{
		g_pVtxBufferGameBG->Release();
		g_pVtxBufferGameBG = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateGameBG
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateGameBG ( void )
{
	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBg
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawGameBG ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	
	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferGameBG, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureGameBG);

	//ポリゴンの描画
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		NUM_POLYGON				//ポリゴンの数
		);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexBg
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexGameBG ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEX,		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferGameBG,					//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferGameBG->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(2D座標・右回り)
	setRotBuffer(pVtx, g_gameBG.conf);

	//テクスチャ設定
	setTexture(pVtx, g_gameBG.tex);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定(0~155の整数値)
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	//私のこころアーンロック♪
	g_pVtxBufferGameBG->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBgType
//返り値	: 
//説明		: 背景画像設定
//////////////////////////////////////////////////////////////////////////////
void	setGameBGType	( GAME_BG_TYPE type )
{
	g_gameBG.type = type;
}