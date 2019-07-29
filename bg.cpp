/*****************************************************************************
bg.cpp
Aythor	: 上野　匠
Data	: 2017_04_13
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bg.h"
#include "polygon.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define BG_TEXTURENAME "data/TEXTURE/gameBG001.jpg"	//読み込むテクスチャファイル

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON	conf;		//ポリゴンの各種設定
	TEXTURE		tex;		//テクスチャ設定
	BG_TYPE		type;		//背景画像の種類
}BG;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBg ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBg[BG_TYPE_MAX] = {NULL};	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBg = NULL;	//頂点バッファ管理インターフェイス

BG		g_bg;		//背景構造体
const char	*texNameBg[BG_TYPE_MAX] =
{
	"data/TEXTURE/titleBG001.jpg",
	"data/TEXTURE/gameBG001.jpg",
};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initBg
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initBg ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	initRotPolygon(&g_bg.conf,
		D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f),
		D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f));

	initTexture(&g_bg.tex,
		D3DXVECTOR2(0.f, 0.f),
		D3DXVECTOR2(1.f, 1.f));
	
	//テクスチャの読み込み
	for(int i = 0; i < BG_TYPE_MAX; i++)
	{
		if(FAILED(D3DXCreateTextureFromFile(pDevice, texNameBg[i], &g_pTextureBg[i])))
		{
			//MessageBox(NULL, "bg", "エラー", MB_OK);
		}
	}

	//デバイス取得
	makeVertexBg(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitBg
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitBg ( void )
{
	//テクスチャインターフェイスの解放
	for(int i = 0; i < BG_TYPE_MAX; i++)
	{
		if(g_pTextureBg[i] != NULL)
		{
			g_pTextureBg[i]->Release();
			g_pTextureBg[i] = NULL;
		}
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferBg != NULL)
	{
		g_pVtxBufferBg->Release();
		g_pVtxBufferBg = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateBg
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateBg ( void )
{
	
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBg
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawBg ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	
	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferBg, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureBg[g_bg.type]);

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
HRESULT makeVertexBg ( LPDIRECT3DDEVICE9 pDevice )
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
			&g_pVtxBufferBg,					//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBg->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(2D座標・右回り)
	setRotBuffer(pVtx, g_bg.conf);

	//テクスチャ設定
	setTexture(pVtx, g_bg.tex);

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
	g_pVtxBufferBg->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBgType
//返り値	: 
//説明		: 背景画像設定
//////////////////////////////////////////////////////////////////////////////
void	setBgType	( BG_TYPE type )
{
	g_bg.type = type;
}