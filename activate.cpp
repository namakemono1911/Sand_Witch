/*****************************************************************************
actibate.cpp
Aythor	: 上野　匠
Data	: 2017_06_04
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "input.h"
#include "polygon.h"
#include "activate.h"
#include "notes.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define ACTIVE_MAX		(100)		//最大数	
#define ANIME_FRAME		(30)		//テクスチャアニメのFPS
#define ACTIVE_SIZE		(D3DXVECTOR3(LINE_HEIGHT, LINE_HEIGHT, 0.f))	//ポリゴンのサイズ

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON		conf;		//ポリゴンの各種設定
	TEXTURE		tex;		//UV設定
	int			frame;		//フレーム数
	ACTIVE_TYPE	type;		//テクスチャのタイプ
	bool		use;		//使用フラグ
}ACTIVE;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexActive(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureActive[ACTIVE_TYPE_MAX] = { NULL };	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferActive = NULL;	//頂点バッファ管理インターフェイス

ACTIVE		g_active[ACTIVE_MAX];		//背景構造体
UINT		g_numActive = 0;			//いくつ構造体が有効になっているか
const char	*texNameActive[ACTIVE_TYPE_MAX] =
{
	"data/TEXTURE/mh.png",
};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initActive
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initActive(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	for(int i = 0; i < ACTIVE_MAX; i++)
	{
		g_active[i].conf.size = ACTIVE_SIZE;
		g_active[i].tex.size = D3DXVECTOR2(1.f / 11.f, 1.f);
		g_active[i].use = false;
	}

	g_numActive = 0;

	//テクスチャの読み込み
	for (int i = 0; i < ACTIVE_TYPE_MAX; i++)
	{
		if (FAILED(D3DXCreateTextureFromFile(pDevice, texNameActive[i], &g_pTextureActive[i])))
		{
			MessageBox(NULL, "bg", "エラー", MB_OK);
		}
	}

	//デバイス取得
	makeVertexActive(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitActive
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitActive(void)
{
	//テクスチャインターフェイスの解放
	for (int i = 0; i < ACTIVE_TYPE_MAX; i++)
	{
		if (g_pTextureActive[i] != NULL)
		{
			g_pTextureActive[i]->Release();
			g_pTextureActive[i] = NULL;
		}
	}

	//頂点バッファ管理の解放
	if (g_pVtxBufferActive != NULL)
	{
		g_pVtxBufferActive->Release();
		g_pVtxBufferActive = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateActive
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateActive(void)
{
	//使用されている情報の更新
	for(UINT i = 0, j = 0; j < g_numActive; i++)
	{
		//使われている構造体探索
		if(g_active[i].use == true)
		{
			//テクスチャアニメーション
			g_active[i].frame++;
			if (g_active[i].frame % (60 / ANIME_FRAME) == 0)
			{
				g_active[i].tex.pos.x += g_active[i].tex.size.x;
				if(g_active[i].tex.pos.x >= 1.f)
				{
					g_active[i].use = false;
					g_numActive--;
				}

			}
			j++;
		}
	}

	//頂点情報更新
	VERTEX2D *pVtx;
	g_pVtxBufferActive->Lock(0, 0, (void**)&pVtx, 0);

	for(UINT i = 0, j = 0; j < g_numActive; i++)
	{
		if(g_active[i].use == true)
		{
			//頂点情報登録
			setBuffer(pVtx, g_active[i].conf);

			//テクスチャ
			setTexture(pVtx, g_active[i].tex);

			j++;
		}

		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferActive->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawActive
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawActive(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferActive, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for(UINT i = 0, j = 0; j < g_numActive; i++)
	{
		if(g_active[i].use == true)
		{
			pDevice->SetTexture(0, g_pTextureActive[g_active[i].type]);

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
//関数名	: makeVertexActive
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexActive(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

								//頂点バッファの設定
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * ACTIVE_MAX,		//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//メモリ管理方法
		&g_pVtxBufferActive,				//頂点バッファ管理インターフェイス
		NULL
	)
	))

	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferActive->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < ACTIVE_MAX; i++)
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
	}

	//私のこころアーンロック♪
	g_pVtxBufferActive->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setActivate
//返り値	: 
//説明		: 生成
//////////////////////////////////////////////////////////////////////////////
void	setActivate	(D3DXVECTOR3 pos, ACTIVE_TYPE type)
{
	//変数宣言
	VERTEX2D	*pVtx;

	//頂点バッファロック
	g_pVtxBufferActive->Lock(0, 0, (void**)&pVtx, 0);

	//使われていない配列探索
	for(int i = 0; i < ACTIVE_MAX; i++)
	{
		if(g_active[i].use == false)
		{
			//情報設定
			g_active[i].conf.pos = pos;
			g_active[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
			g_active[i].use = true;

			//頂点情報登録
			setBuffer(pVtx, g_active[i].conf);

			//テクスチャ
			setTexture(pVtx, g_active[i].tex);
			
			g_numActive++;
			break;
		}

		pVtx += NUM_VERTEX;
	}

	//アンロック
	g_pVtxBufferActive->Unlock();
}