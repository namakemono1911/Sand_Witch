/*****************************************************************************
tutorial.cpp
Aythor	: 上野　匠
Data	: 2017_06_21
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "tutorial.h"
#include "fade.h"
#include "input.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define	MAX_TUTO	(29)		//チュートリアルの画像の数
#define POP_SPD		(0.1f)		//ポップアップスピード

#define TUTO_MSG_SIZE	(D3DXVECTOR3(1000.f, 200.f, 0.f))	//チュートリアルメッセージのサイズ

#define POP_HEIGHT	(SCREEN_HEIGHT - TUTO_MSG_SIZE.y * 0.5f - 50.f)	//ポップアップする高さ
#define POP_DOWN_HE	(SCREEN_HEIGHT + TUTO_MSG_SIZE.y *0.5f)			//ポップダウンする高さ

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	TUTO_00 = 0,		//チュートリアルを始めます
	TUTO_01,			//目的
	TUTO_02,			//プレイヤー
	TUTO_03,			//門
	TUTO_04,			//進行度バー
	TUTO_05,			//お城
	TUTO_06,			//通常弾
	TUTO_07,			//通常弾
	TUTO_08,			//魔法の発動
	TUTO_09,			//魔法の発動
	TUTO_10,			//クールタイム
	TUTO_11,			//特殊弾
	TUTO_12,			//市民
	TUTO_13,			//市民
	TUTO_14,			//市民
	TUTO_15,			//ボス
	TUTO_16,			//ボス

	//チュートリアル説明画像
	TUTO_DSP_00,		//最初の画面
	TUTO_DSP_01,		//プレイヤー
	TUTO_DSP_02,		//門
	TUTO_DSP_03,		//進行度バー
	TUTO_DSP_04,		//お城
	TUTO_DSP_05,		//帽子
	TUTO_DSP_06,		//通常弾1
	TUTO_DSP_07,		//通常弾2
	TUTO_DSP_08,		//魔法発動
	TUTO_DSP_09,		//敵
	TUTO_DSP_10,		//クールタイム
	TUTO_DSP_11,		//特殊弾
	TUTO_DSP_12,		//次の説明画面
	TUTO_DSP_13,		//市民
	TUTO_DSP_14,		//次の説明画面
	TUTO_DSP_15,		//ボス
	TUTO_DSP_16,		//ボスの核
	TUTO_TYPE_MAX,		//テクスチャ最大数
}TUTO_TYPE;

typedef struct
{
	POLYGON		conf;	//ポリゴン設定
	TEXTURE		tex;	//テクスチャ設定
	int			achive;	//進行度
	TUTO_TYPE	type;	//テクスチャタイプ
}TUTO;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexTuto(LPDIRECT3DDEVICE9 pDevice);
void	popupTuto(void);
void	popdownTuto(void);
void	changeTutoDsp(int achive);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureTuto[TUTO_TYPE_MAX] = {NULL};	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferTuto = NULL;			//頂点バッファ管理インターフェイス
char	*g_texNameTuto[] = 
{
	//メッセージ
	"data/TEXTURE/TUTORIAL/tuto00.png",		//チュートリアルメッセージ00
	"data/TEXTURE/TUTORIAL/tuto01.png",		//チュートリアルメッセージ01
	"data/TEXTURE/TUTORIAL/tuto02.png",		//チュートリアルメッセージ02
	"data/TEXTURE/TUTORIAL/tuto03.png",		//チュートリアルメッセージ03
	"data/TEXTURE/TUTORIAL/tuto04.png",		//チュートリアルメッセージ04
	"data/TEXTURE/TUTORIAL/tuto05.png",		//チュートリアルメッセージ05
	"data/TEXTURE/TUTORIAL/tuto06.png",		//チュートリアルメッセージ06
	"data/TEXTURE/TUTORIAL/tuto07.png",		//チュートリアルメッセージ07
	"data/TEXTURE/TUTORIAL/tuto08.png",		//チュートリアルメッセージ08
	"data/TEXTURE/TUTORIAL/tuto09.png",		//チュートリアルメッセージ09
	"data/TEXTURE/TUTORIAL/tuto10.png",		//チュートリアルメッセージ10
	"data/TEXTURE/TUTORIAL/tuto11.png",		//チュートリアルメッセージ11
	"data/TEXTURE/TUTORIAL/tuto12.png",		//チュートリアルメッセージ12
	"data/TEXTURE/TUTORIAL/tuto13.png",		//チュートリアルメッセージ13
	"data/TEXTURE/TUTORIAL/tuto14.png",		//チュートリアルメッセージ14
	"data/TEXTURE/TUTORIAL/tuto15.png",		//チュートリアルメッセージ15
	"data/TEXTURE/TUTORIAL/tuto16.png",		//チュートリアルメッセージ16

	//図説
	"data/TEXTURE/TUTORIAL/tuto_dsp00.jpg",	//チュートリアル図説00
	"data/TEXTURE/TUTORIAL/tuto_dsp01.jpg",	//チュートリアル図説01
	"data/TEXTURE/TUTORIAL/tuto_dsp02.jpg",	//チュートリアル図説02
	"data/TEXTURE/TUTORIAL/tuto_dsp03.jpg",	//チュートリアル図説03
	"data/TEXTURE/TUTORIAL/tuto_dsp04.jpg",	//チュートリアル図説04
	"data/TEXTURE/TUTORIAL/tuto_dsp05.jpg",	//チュートリアル図説05
	"data/TEXTURE/TUTORIAL/tuto_dsp06.jpg",	//チュートリアル図説06
	"data/TEXTURE/TUTORIAL/tuto_dsp07.jpg",	//チュートリアル図説07
	"data/TEXTURE/TUTORIAL/tuto_dsp08.jpg",	//チュートリアル図説08
	"data/TEXTURE/TUTORIAL/tuto_dsp09.jpg",	//チュートリアル図説09
	"data/TEXTURE/TUTORIAL/tuto_dsp10.jpg",	//チュートリアル図説10
	"data/TEXTURE/TUTORIAL/tuto_dsp11.jpg",	//チュートリアル図説11
	"data/TEXTURE/TUTORIAL/tuto_dsp12.jpg",	//チュートリアル図説12
	"data/TEXTURE/TUTORIAL/tuto_dsp13.jpg",	//チュートリアル図説13
	"data/TEXTURE/TUTORIAL/tuto_dsp14.jpg",	//チュートリアル図説14
	"data/TEXTURE/TUTORIAL/tuto_dsp15.jpg",	//チュートリアル図説15
	"data/TEXTURE/TUTORIAL/tuto_dsp16.jpg",	//チュートリアル図説15
};

TUTO	g_tuto;		//チュートリアルの設定
TUTO	g_tutoDsp;	//チュートリアル図説の設定

bool	g_popUp = false;	//ポップアップしてるかどうか
bool	g_popDown = true;	//ポップダウンしてるかどうか

//////////////////////////////////////////////////////////////////////////////
//関数名	: initTuto
//返り値	: 
//説明		: チュートリアル初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	initTuto	(void)
{
	//フェードイン
	startFadeIn(60, D3DXCOLOR(1.f, 1.f, 1.f, 1.f));

	//変数初期化
	g_tuto.achive = 0;
	g_tutoDsp.achive = 0;
	g_tuto.conf.size = TUTO_MSG_SIZE;
	g_tuto.conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + g_tuto.conf.size.x * 0.5f, 0.f);
	g_tuto.tex.pos = D3DXVECTOR2(0.f, 0.f);
	g_tuto.tex.size = D3DXVECTOR2(1.f, 1.f);

	g_tutoDsp.conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.f);
	g_tutoDsp.conf.size = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.f);
	g_tutoDsp.tex.pos = D3DXVECTOR2(0.f, 0.f);
	g_tutoDsp.tex.size = D3DXVECTOR2(1.f, 1.f);

	g_popUp = false;
	g_popDown = true;

	//テクスチャの読み込み
	LPDIRECT3DDEVICE9	pDevice = getDevice();		//デバイス情報
	for (int i = 0; i < TUTO_TYPE_MAX; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, g_texNameTuto[i], &g_pTextureTuto[i])))
		{
			MessageBox(NULL, "tutorial", "エラー", MB_OK);
		}
	}

	//頂点バッファ作成
	makeVertexTuto(pDevice);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateTuto
//返り値	: 
//説明		: チュートリアル更新
//////////////////////////////////////////////////////////////////////////////
void uninitTuto(void)
{
	//頂点バッファリリース
	if (g_pVtxBufferTuto != NULL)
	{
		g_pVtxBufferTuto->Release();
		g_pVtxBufferTuto = NULL;
	}

	//テクスチャバッファリリース
	for (int i = 0; i < TUTO_TYPE_MAX; i++)
	{
		if (g_pTextureTuto[i] != NULL)
		{
			g_pTextureTuto[i]->Release();
			g_pTextureTuto[i] = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateTuto
//返り値	: 
//説明		: チュートリアル更新
//////////////////////////////////////////////////////////////////////////////
void updateTuto(void)
{
	if (g_popDown == false)
	{
		popdownTuto();

		if (g_tuto.achive >= TUTO_16)
		{
			startFadeOut(60, D3DXCOLOR(1.f, 1.f, 1.f, 0.f), STAGE_SELECT);
		}
	}
	else if (g_popUp == false)
	{
		if (g_tuto.achive <= TUTO_16)
		{
			popupTuto();
		}
	}

	//テクスチャ変更
	changeTutoDsp(g_tutoDsp.achive);

	//頂点情報更新
	VERTEX2D	*pVtx;
	g_pVtxBufferTuto->Lock(0, 0, (void**)&pVtx, 0);

	//図説部分の更新
	setBuffer(pVtx, g_tutoDsp.conf);
	setTexture(pVtx, g_tutoDsp.tex);

	pVtx += NUM_VERTEX;

	//メッセージ更新
	setBuffer(pVtx, g_tuto.conf);
	setTexture(pVtx, g_tuto.tex);

	g_pVtxBufferTuto->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawTuto
//返り値	: 
//説明		: チュートリアル描画
//////////////////////////////////////////////////////////////////////////////
void drawTuto(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();
	int		i;		//loop

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferTuto, 0, sizeof(VERTEX2D));

	//ポリゴンの描画
	for (i = 0; i < TUTO_TYPE_MAX; i++)
	{
		////図説部分描画
		//pDevice->SetTexture(0, g_pTextureTuto[g_tutoDsp.type]);

		//pDevice->DrawPrimitive
		//(
		//	D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		//	0,						//オフセット(頂点数)
		//	NUM_POLYGON				//ポリゴンの数
		//);

		//メッセージ部分描画
		if (g_tuto.achive <= TUTO_16)
		{
			pDevice->SetTexture(0, g_pTextureTuto[g_tuto.achive]);

			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
				NUM_VERTEX,				//オフセット(頂点数)
				NUM_POLYGON				//ポリゴンの数
			);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexTuto
//返り値	: 
//説明		: 頂点バッファ作成
//////////////////////////////////////////////////////////////////////////////
void addAchive(void)
{
	g_tuto.achive++;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: startPopdown
//返り値	: 
//説明		: ポップダウン開始
//////////////////////////////////////////////////////////////////////////////
void startPopdown(void)
{
	g_popDown = false;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexTuto
//返り値	: 
//説明		: 頂点バッファ作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexTuto(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ
	int		i;		//loop

	//頂点バッファの設定
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX2D) * NUM_VERTEX * 2,	//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//メモリ管理方法
		&g_pVtxBufferTuto,					//頂点バッファ管理インターフェイス
		NULL)))
	{
		return E_FAIL;
	}

	g_pVtxBufferTuto->Lock(0, 0, (void**)&pVtx, 0);

	//頂点情報
	setBuffer(pVtx, g_tutoDsp.conf);

	//テクスチャ座標
	setTexture(pVtx, g_tutoDsp.tex);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = pVtx[1].rhw =
		pVtx[2].rhw = pVtx[3].rhw = 1.f;

	//頂点カラーの設定(0~155の整数値)
	pVtx[0].color = pVtx[1].color =
		pVtx[2].color = pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx += NUM_VERTEX;

	//頂点情報
	setBuffer(pVtx, g_tuto.conf);

	//テクスチャ座標
	setTexture(pVtx, g_tuto.tex);

	//rhwの設定(必ず1.0f)
	pVtx[0].rhw = pVtx[1].rhw = 
	pVtx[2].rhw = pVtx[3].rhw = 1.f;

	//頂点カラーの設定(0~155の整数値)
	pVtx[0].color = pVtx[1].color = 
	pVtx[2].color = pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 255);


	g_pVtxBufferTuto->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: popupTuto
//返り値	: trueで更新完了
//説明		: チュートリアルメッセージ表示
//////////////////////////////////////////////////////////////////////////////
void	popupTuto(void)
{
	g_tuto.conf.pos.y -= (g_tuto.conf.pos.y - POP_HEIGHT) * POP_SPD;
	g_popUp = false;

	if (g_tuto.conf.pos.y <= POP_HEIGHT)
	{
		g_tuto.conf.pos.y = POP_HEIGHT;
		g_popUp = true;
		g_tutoDsp.achive++;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: popdownTuto
//返り値	: trueで更新完了
//説明		: チュートリアルメッセージ表示
//////////////////////////////////////////////////////////////////////////////
void	popdownTuto(void)
{
	g_tuto.conf.pos.y += 50.f;
	g_popDown = false;

	if (g_tuto.conf.pos.y >= POP_DOWN_HE)
	{
		g_tuto.conf.pos.y = POP_DOWN_HE;
		g_popDown = true;
		g_popUp = false;
		g_tuto.achive++;
		g_tutoDsp.achive++;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: changeTuto
//返り値	: 
//説明		: テクスチャ
//////////////////////////////////////////////////////////////////////////////
void	changeTutoDsp(int achive)
{
	switch(achive)
	{
	case 0:
	{
		g_tutoDsp.type = TUTO_DSP_00;
		break;
	}

	case 1:
	{
		g_tutoDsp.type = TUTO_DSP_00;
		break;
	}

	case 2:
	{
		g_tutoDsp.type = TUTO_DSP_01;
		break;
	}

	case 3:
	{
		g_tutoDsp.type = TUTO_DSP_02;
		break;
	}

	case 4:
	{
		g_tutoDsp.type = TUTO_DSP_03;
		break;
	}

	case 5:
	{
		g_tutoDsp.type = TUTO_DSP_04;
		break;
	}

	case 6:
	{
		g_tutoDsp.type = TUTO_DSP_06;
		break;
	}

	case 7:
	{
		g_tutoDsp.type = TUTO_DSP_07;
		break;
	}

	case 8:
	{
		g_tutoDsp.type = TUTO_DSP_08;
		break;
	}

	case 9:
	{
		g_tutoDsp.type = TUTO_DSP_09;
		break;
	}

	case 10:
	{
		g_tutoDsp.type = TUTO_DSP_10;
		break;
	}

	case 11:
	{
		g_tutoDsp.type = TUTO_DSP_11;
		break;
	}

	case 12:
	{
		g_tutoDsp.type = TUTO_DSP_13;
		break;
	}

	case 13:
	{
		g_tutoDsp.type = TUTO_DSP_13;
		break;
	}

	case 14:
	{
		g_tutoDsp.type = TUTO_DSP_13;
		break;
	}

	case 15:
	{
		g_tutoDsp.type = TUTO_DSP_15;
		break;
	}

	case 16:
	{
		g_tutoDsp.type = TUTO_DSP_16;
		break;
	}
	}
}