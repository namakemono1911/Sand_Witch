/*****************************************************************************
bulletEffect.cpp
Aythor	: 上野　匠
Data	: 2017_06_09
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "bulletEffect.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define MAX			(50)		//エフェクト最大数
#define TEX_MOVE	(0.01f)		//テクスチャスクロールの速度
#define TEX_HEIGHT	(1.f / 3.f)	//テクスチャの幅	
#define TEX_PER_SIZE	(1.f / 808.f)	//テクスチャサイズの割合

#define ANIME_FRAME	(15)		//アニメーションするフレーム数

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON			conf;		//ポリゴンの設定
	TEXTURE			tex;		//テクスチャ設定
	BULLET_EFFECT_TYPE	type;	//エフェクトの種類
	int				anime;		//アニメーション
	bool			use;		//使用フラグ
}BULLET_EFFECT;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBulletEffect(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBulletEffect[BULLET_EFFECT_MAX] = { NULL };	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBulletEffect = NULL;	//頂点バッファ管理インターフェイス

BULLET_EFFECT	g_bulletEffect[MAX];		//背景構造体
UINT			g_numBulletEffect = 0;		//使われているエフェクト数	
const char	*texNameBulletEffect[BULLET_EFFECT_MAX] =
{
	"data/TEXTURE/GAME/BULLET/mmm.png",
};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initBulletEffect
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initBulletEffect(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	for(int i = 0; i < MAX; i++)
	{
		g_bulletEffect[i].tex.size.y = TEX_HEIGHT;
		g_bulletEffect[i].use = false;
	}
	g_numBulletEffect = 0;

	//テクスチャの読み込み
	for (int i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, texNameBulletEffect[i], &g_pTextureBulletEffect[i])))
		{
			MessageBox(NULL, "bg", "エラー", MB_OK);
		}
	}

	//デバイス取得
	makeVertexBulletEffect(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitBulletEffect
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitBulletEffect(void)
{
	//テクスチャインターフェイスの解放
	for (int i = 0; i < BULLET_EFFECT_MAX; i++)
	{
		if (g_pTextureBulletEffect[i] != NULL)
		{
			g_pTextureBulletEffect[i]->Release();
			g_pTextureBulletEffect[i] = NULL;
		}
	}

	//頂点バッファ管理の解放
	if (g_pVtxBufferBulletEffect != NULL)
	{
		g_pVtxBufferBulletEffect->Release();
		g_pVtxBufferBulletEffect = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateBulletEffect
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateBulletEffect(void)
{
	//変数宣言
	VERTEX2D	*pVtx;

	g_pVtxBufferBulletEffect->Lock(0, 0, (void**)&pVtx, 0);

	for(UINT i = 0, j = 0; j < g_numBulletEffect; i++)
	{
		if (g_bulletEffect[i].use == true)
		{
			//座標
			setBuffer(pVtx, g_bulletEffect[i].conf);

			//テクスチャ
			g_bulletEffect[i].anime = (g_bulletEffect[i].anime + 1) % 60;
			g_bulletEffect[i].tex.pos.x += TEX_MOVE;
			g_bulletEffect[i].tex.size.x += TEX_MOVE;
			if (g_bulletEffect[i].anime % (60 / ANIME_FRAME) == 0)
			{
				g_bulletEffect[i].tex.pos.y += g_bulletEffect[i].tex.size.y;
				//g_bulletEffect[i].tex.size.y = fmod(g_bulletEffect[i].tex.size.y + TEX_HEIGHT, 1.f);
			}
			setTexture(pVtx, g_bulletEffect[i].tex);

			j++;
		}

		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferBulletEffect->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBulletEffect
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawBulletEffect(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferBulletEffect, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(UINT i = 0, j = 0; j < g_numBulletEffect; i++)
	{
		if (g_bulletEffect[i].use == true)
		{
			pDevice->SetTexture(0, g_pTextureBulletEffect[g_bulletEffect[i].type]);

			//ポリゴンの描画
			pDevice->DrawPrimitive
			(
				D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
				NUM_VERTEX * i,			//オフセット(頂点数)
				NUM_POLYGON				//ポリゴンの数
			);

			j++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexBulletEffect
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBulletEffect(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

								//頂点バッファの設定
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * MAX,	//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//メモリ管理方法
		&g_pVtxBufferBulletEffect,				//頂点バッファ管理インターフェイス
		NULL
	)
	))

	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBulletEffect->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < MAX; i++)
	{
		//rhwの設定(必ず1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0~155の整数値)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 192);
		pVtx[1].color = D3DCOLOR_RGBA(255, 255, 255, 192);
		pVtx[2].color = D3DCOLOR_RGBA(255, 255, 255, 192);
		pVtx[3].color = D3DCOLOR_RGBA(255, 255, 255, 192);

		pVtx += NUM_VERTEX;
	}

	//私のこころアーンロック♪
	g_pVtxBufferBulletEffect->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBulletEffect
//返り値	: 
//説明		: エフェクト生成
//////////////////////////////////////////////////////////////////////////////
int	setBulletEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, BULLET_EFFECT_TYPE type)
{
	for (int i = 0; i < MAX; i ++)
	{
		if (g_bulletEffect[i].use == false)
		{
			g_bulletEffect[i].conf.pos = pos;
			g_bulletEffect[i].conf.size = size;
			g_bulletEffect[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_bulletEffect[i].tex.size.x = TEX_PER_SIZE * size.x;
			g_bulletEffect[i].type = type;
			g_bulletEffect[i].anime = 0;
			g_bulletEffect[i].use = true;

			g_numBulletEffect++;
			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: ReleaseBulletEffect
//返り値	: 
//説明		: フラグリリース
//////////////////////////////////////////////////////////////////////////////
void releaseBulletEffect(int id)
{
	if(id >= 0)
	{
		g_bulletEffect[id].use = false;
		g_numBulletEffect--;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBulletEffectPos
//返り値	: 
//説明		: エフェクトの座標設定
//////////////////////////////////////////////////////////////////////////////
void setBulletEffectPos(int id, D3DXVECTOR3 pos)
{
	if (id >= 0)
	{
		g_bulletEffect[id].conf.pos = pos;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBulletEffectSize
//返り値	: 
//説明		: エフェクトの座標設定
//////////////////////////////////////////////////////////////////////////////
void setBulletEffectSize(int id, D3DXVECTOR3 size)
{
	if (id >= 0)
	{
		g_bulletEffect[id].conf.size = size;
		g_bulletEffect[id].tex.size.x = TEX_PER_SIZE * size.x;
	}
}