/*****************************************************************************
bulletUI.cpp
Aythor	: 上野　匠
Data	: 2017_05_21
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "bullet.h"
#include "bulletUI.h"

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
#define MAX_BULLET_UI		(2)	//弾UIの最大数
#define NUM_VTX_BULLET_UI	(12)	//一つのUIに使う頂点数

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON				conf;		//ポリゴンの設定
	float				maxWidth;	//最大サイズ
	POLYGON				coolTime;	//クールタイム表示
	D3DXCOLOR			setColor;	//設定する頂点色
	D3DXCOLOR			color;		//頂点色
	BULLET_UI_TYPE		type;		//UIの種類
	UINT				cntTime;	//クールタイム
	bool				ct;			//クールタイムフラグ
	bool				use;		//使用フラグ
}BULLET_UI;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT	makeVertexBulletUI	( LPDIRECT3DDEVICE9 pDevice );
void	setBulletUIVtx	( const unsigned int num );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DVERTEXBUFFER9	g_pVtxBufferBulletUI = NULL;
LPDIRECT3DTEXTURE9		g_pTextureBulletUI[BULLET_UI_MAX] = {NULL};

BULLET_UI	bulletUI[MAX_BULLET_UI];		//弾UIの情報格納
const char	*g_texNameBulletUI[] =			//テクスチャの種類
{
	"data/TEXTURE/magicCursor.png",
	"data/TEXTURE/white.png",
};

//////////////////////////////////////////////////////////////////////////////
//関数名	: initBulletUI
//返り値	: 
//説明		: 弾UI初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	initBulletUI	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		bulletUI[i].cntTime = 0;
		bulletUI[i].use = false;
		bulletUI[i].ct = false;
	}
	
	for(int i = 0; i < 1; i++)
	{
		//テクスチャの読み込み
		if(FAILED(D3DXCreateTextureFromFile(pDevice, g_texNameBulletUI[i], &g_pTextureBulletUI[i])))
		{
			MessageBox(NULL, "bullet", "エラー", MB_OK);
			return E_FAIL;
		}
	}

	//デバイス取得
	makeVertexBulletUI(pDevice);

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitBulletUI
//返り値	: 
//説明		: 弾UI初期化
//////////////////////////////////////////////////////////////////////////////
void	uninitBulletUI	( void )
{
	//頂点情報解放
	if(g_pVtxBufferBulletUI != NULL)
	{
		g_pVtxBufferBulletUI->Release();
		g_pVtxBufferBulletUI = NULL;
	}

	//テクスチャ情報解放
	for(int i = 0; i <BULLET_UI_MAX; i++)
	{
		if(g_pTextureBulletUI[i] != NULL)
		{
			g_pTextureBulletUI[i]->Release();
			g_pTextureBulletUI[i] = NULL;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateBulletUI
//返り値	: 
//説明		: 弾UI初期化
//////////////////////////////////////////////////////////////////////////////
void	updateBulletUI	( void )
{
	//変数宣言
	VERTEX2D	*pVtx;

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		if(bulletUI[i].use == true)
		{
			//クールタイム状態の処理
			if(bulletUI[i].ct == true)
			{
				bulletUI[i].coolTime.size.x += bulletUI[i].maxWidth * (1.f / (float)bulletUI[i].cntTime);
				bulletUI[i].coolTime.pos.x = (bulletUI[i].conf.pos.x - bulletUI[i].maxWidth * 0.5f) + bulletUI[i].coolTime.size.x * 0.5f;
				bulletUI[i].cntTime--;

				if(bulletUI[i].coolTime.size.x >= bulletUI[i].maxWidth || bulletUI[i].cntTime <= 0)
				{
					bulletUI[i].coolTime.size.x = bulletUI[i].maxWidth;
					bulletUI[i].coolTime.pos.x = bulletUI[i].conf.pos.x;
					bulletUI[i].cntTime = 0;
					bulletUI[i].ct = false;
				}
			}

			//クールタイム可視化部分
			pVtx[6 + i * NUM_VTX_BULLET_UI].color = 
			pVtx[7 + i * NUM_VTX_BULLET_UI].color = 
			pVtx[8 + i * NUM_VTX_BULLET_UI].color = 
			pVtx[9 + i * NUM_VTX_BULLET_UI].color =
			pVtx[10 + i * NUM_VTX_BULLET_UI].color =
			pVtx[11 + i * NUM_VTX_BULLET_UI].color =
			bulletUI[i].color;

			//ポリゴン
			setListBuffer(&pVtx[6 + i * NUM_VTX_BULLET_UI], bulletUI[i].coolTime);
		}
	}

	g_pVtxBufferBulletUI->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBulletUI
//返り値	: 
//説明		: 弾UI初期化
//////////////////////////////////////////////////////////////////////////////
void	drawBulletUI	( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferBulletUI, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		if(bulletUI[i].use == true)
		{
			//これはマークの分！これはクールタイムの分だ！
			for(int j = 0; j < 2; j++)
			{
				if(j % 2 == 0)
				{
					//テクスチャ読み込み
					pDevice->SetTexture(0, g_pTextureBulletUI[bulletUI[i].type]);
				}
				else
				{
					//驚きの白さ
					pDevice->SetTexture(0, NULL);
				}

				pDevice->DrawPrimitive
					(
					D3DPT_TRIANGLELIST,	//ポリゴンの種類
					NUM_VTX_BULLET_UI * i + 6 * j,	//オフセット(頂点数)
					2						//ポリゴンの数
					);
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexBulletUI
//返り値	: 
//説明		: 弾UI初期化
//////////////////////////////////////////////////////////////////////////////
HRESULT	makeVertexBulletUI	( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ
	int		i;		//loop

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VTX_BULLET_UI * MAX_BULLET_UI,		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferBulletUI,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < NUM_VTX_BULLET_UI * MAX_BULLET_UI; i++)
	{
		//rhwの設定(必ず1.0f)
		pVtx->rhw = 1.f;

		pVtx++;
	}

	g_pVtxBufferBulletUI->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBulletUI
//返り値	: 
//説明		: 弾UI設定
//////////////////////////////////////////////////////////////////////////////
int	setBulletUI	( const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR color )
{
	//未使用の構造体探索
	for(int i = 0; i < MAX_BULLET_UI; i++)
	{
		if(bulletUI[i].use == false)
		{
			//回転ポリゴンに必要な情報設定
			bulletUI[i].conf.pos = pos;
			bulletUI[i].conf.size = size;
			
			bulletUI[i].coolTime.pos = pos;
			bulletUI[i].coolTime.size = D3DXVECTOR3(0.f, size.y - 10.f, 0.f);

			bulletUI[i].maxWidth = size.x - 65.2f;

			bulletUI[i].color = D3DXCOLOR(0.f, 0.f, 0.f, 0.f);
			bulletUI[i].setColor = color;
			bulletUI[i].use = true;

			//頂点情報設定
			setBulletUIVtx(i);

			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBulletUIVtx
//返り値	: 
//説明		: 弾UI頂点情報設定
//////////////////////////////////////////////////////////////////////////////
void	setBulletUIVtx	( const unsigned int num )
{
	//変数宣言
	VERTEX2D	*pVtx;

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += NUM_VTX_BULLET_UI * num;

	//アイコン
	pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].color = pVtx[2].color = pVtx[3].color = 
	pVtx[4].color = pVtx[5].color = D3DCOLOR_RGBA(255, 255, 255, 255);

	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 1.f);
	pVtx[3].tex = D3DXVECTOR2(1.f, 0.f);
	pVtx[4].tex = D3DXVECTOR2(1.f, 1.f);
	pVtx[5].tex = D3DXVECTOR2(0.f, 1.f);

	setListBuffer(pVtx, bulletUI[num].conf);

	pVtx += 6;
	/*
	//縮退ポリゴン
	pVtx[0].pos = D3DXVECTOR3(
		bulletUI[num].conf.pos.x + (bulletUI[num].conf.size.x * 0.5f),
		bulletUI[num].conf.pos.y + (bulletUI[num].conf.size.y * 0.5f),
		0.f);
	
	pVtx[1].pos = D3DXVECTOR3(
		bulletUI[num].coolTime.pos.x - (bulletUI[num].conf.size.x * 0.5f),
		bulletUI[num].coolTime.pos.y - (bulletUI[num].conf.size.y * 0.5f),
		0.f);

	pVtx += 2;*/

	//クールタイム可視化部分
	pVtx[0].color = pVtx[1].color = pVtx[2].color = pVtx[3].color = 
	pVtx[4].color = pVtx[5].color = bulletUI[num].setColor;

	pVtx[0].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[1].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[2].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[3].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[4].tex = D3DXVECTOR2(0.f, 0.f);
	pVtx[5].tex = D3DXVECTOR2(0.f, 0.f);
	
	setListBuffer(pVtx, bulletUI[num].coolTime);

	g_pVtxBufferBulletUI->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBulletUICoolTime
//返り値	: 
//説明		: 弾UIクールタイム
//////////////////////////////////////////////////////////////////////////////
void	setBulletUICoolTime	( const UINT num, const UINT coolTime )
{
	//変数宣言
	VERTEX2D	*pVtx;

	bulletUI[num].coolTime.size.x = 0.f;
	bulletUI[num].color = bulletUI[num].setColor;
	bulletUI[num].coolTime.pos.x = bulletUI[num].conf.pos.x - bulletUI[num].maxWidth * 0.5f;
	bulletUI[num].cntTime = coolTime;

	g_pVtxBufferBulletUI->Lock(0, 0, (void**)&pVtx, 0);

	//ポインタ移動
	pVtx += NUM_VTX_BULLET_UI * num + 6;

	setBuffer(pVtx, bulletUI[num].coolTime);

	pVtx[0].color = pVtx[1].color = pVtx[2].color = pVtx[3].color = bulletUI[num].color;

	g_pVtxBufferBulletUI->Unlock();

	bulletUI[num].ct = true;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getBulletCoolTime
//返り値	: 
//説明		: クールタイム取得
//////////////////////////////////////////////////////////////////////////////
int	getBulletCoolTime	(const UINT num)
{
	return bulletUI[num].cntTime;
}