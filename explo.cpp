/*****************************************************************************
explo.cpp
Aythor	: 上野　匠
Data	: 2016_06_08
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "explo.h"
#include "notes.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define TEX_SIZE		(D3DXVECTOR2(1.f / 20, 1.f))	//テクスチャサイズ
#define MAX_EXPLO		(15)		//一度に描画できる最大数
#define ANIME_FRAME		(30)		//再生FPS

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON		conf;		//ポリゴンの各種設定
	TEXTURE	  	tex;		//テクスチャ設定
	int			frameCnt;	//フレームカウンタ
	bool	  	use;		//使用フラグ
}EXPLO;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexExplo(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureExplo = NULL ;	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferExplo = NULL;	//頂点バッファ管理インターフェイス

EXPLO		g_explo[MAX_EXPLO];		//背景構造体
UINT		g_numExplo = 0;			//現在有効な構造体の数

//////////////////////////////////////////////////////////////////////////////
//関数名	: initExplo
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initExplo(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	for(int i = 0; i < MAX_EXPLO; i++)
	{
		g_explo[i].tex.size = TEX_SIZE;
		g_explo[i].use = false;
	}

	g_numExplo = 0;

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/GAME/BULLET/explosion.png", &g_pTextureExplo)))
	{
		MessageBox(NULL, "bg", "エラー", MB_OK);
	}

	//デバイス取得
	makeVertexExplo(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitExplo
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitExplo(void)
{
	//テクスチャインターフェイスの解放
	if (g_pTextureExplo != NULL)
	{
		g_pTextureExplo->Release();
		g_pTextureExplo = NULL;
	}

	//頂点バッファ管理の解放
	if (g_pVtxBufferExplo != NULL)
	{
		g_pVtxBufferExplo->Release();
		g_pVtxBufferExplo = NULL;
	}

	g_numExplo = 0;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateExplo
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateExplo(void)
{
	//情報更新
	for (UINT i = 0, j = 0; j < g_numExplo; i++)
	{
		if (g_explo[i].use == true)
		{
			//テクスチャアニメ
			g_explo[i].frameCnt++;
			if (g_explo[i].frameCnt % (60 / ANIME_FRAME) == 0)
			{
				g_explo[i].tex.pos.x += g_explo[i].tex.size.x;
				if (g_explo[i].tex.pos.x >= 1.f)
				{
					//削除
					g_explo[i].use = false;
					g_numExplo--;
				}
			}

			j++;
		}
	}

	//情報登録
	VERTEX2D *pVtx;

	g_pVtxBufferExplo->Lock(0, 0, (void**)&pVtx, 0);
	
	for (UINT i = 0, j = 0; j < g_numExplo; i++)
	{
		if (g_explo[i].use == true)
		{
			//頂点
			setBuffer(pVtx, g_explo[i].conf);

			//テクスチャ
			setTexture(pVtx, g_explo[i].tex);

			j++;
		}

		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferExplo->Unlock();

}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawExplo
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawExplo(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferExplo, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャ設定
	pDevice->SetTexture(0, g_pTextureExplo);

	//ポリゴンの描画
	for(UINT i = 0, j = 0; j < g_numExplo; i++)
	{
		if (g_explo[i].use == true)
		{
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
				0,						//オフセット(頂点数)
				NUM_POLYGON				//ポリゴンの数
			);

			j++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexExplo
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexExplo(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

	//頂点バッファの設定
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * MAX_EXPLO,		//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//メモリ管理方法
		&g_pVtxBufferExplo,					//頂点バッファ管理インターフェイス
		NULL
	)
	))

	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferExplo->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < MAX_EXPLO; i++)
	{
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

		pVtx += NUM_VERTEX;
	}

	//私のこころアーンロック♪
	g_pVtxBufferExplo->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setExploType
//返り値	: 
//説明		: 背景画像設定
//////////////////////////////////////////////////////////////////////////////
void	setExplo(D3DXVECTOR3 pos, float size)
{
	for(int i = 0; i < MAX_EXPLO; i++)
	{
		if(g_explo[i].use == false)
		{
			g_explo[i].conf.pos = pos;
			g_explo[i].conf.size = D3DXVECTOR3(size, NOTES_HEIGHT, 0.f);
			g_explo[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_explo[i].frameCnt = 0;
			g_explo[i].use = true;

			g_numExplo++;

			//情報登録
			VERTEX2D *pVtx;

			g_pVtxBufferExplo->Lock(0, 0, (void**)&pVtx, 0);

			//ポインタ移動
			pVtx += NUM_VERTEX * i;

			//頂点
			setBuffer(pVtx, g_explo[i].conf);

			//テクスチャ
			setTexture(pVtx, g_explo[i].tex);

			g_pVtxBufferExplo->Unlock();

			break;
		}
	}
}