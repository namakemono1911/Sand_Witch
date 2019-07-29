/*****************************************************************************
fcoh.cpp
Aythor	: 上野　匠
Data	: 2017_06_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "fcoh.h"
#include "gate.h"
#include "notes.h"
#include "boss.h"
#include "nucleusBoss.h"
#include "bulletBoss.h"

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define WIDTH		((float)SCREEN_WIDTH)	//幅
#define HEIGHT		(200.f)					//高さ
#define MOVE		(50.f)					//迫りくる速度
#define COUNT_DOWN	(60)					//必殺技が消えるまでのフレーム数
#define DAMAGE		(10)					//与えられるダメージ
#define NEED_ENERGY	(0)						//必殺技に必要なエネルギー

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON	conf;		//ポリゴンの設定
	TEXTURE	tex;		//テクスチャ
	UINT	count;		//カウントダウン
	int		energy;		//エネルギー
	bool	move;		//動いてるフラグ
	bool	use;		//使用フラグ
}FCOH;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFcoh(LPDIRECT3DDEVICE9 pDevice);

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureFcoh = NULL;			//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferFcoh = NULL;	//頂点バッファ管理インターフェイス

FCOH	g_fcoh[2];		//必殺技の設定
#define FCOH_TEX_NAME "data/TEXTURE/GAME/BULLET/killing.png"

//////////////////////////////////////////////////////////////////////////////
//関数名	: initFcoh
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initFcoh(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得

	//構造体初期化
	for(int i = 0; i < 2; i++)
	{
		g_fcoh[i].use = false;
		g_fcoh[i].move = false;
		g_fcoh[i].count = 0;
		g_fcoh[i].conf.size = D3DXVECTOR3(WIDTH, HEIGHT, 0.f);
		g_fcoh[i].tex.pos = D3DXVECTOR2(0.f, 0.f);
		g_fcoh[i].tex.size = D3DXVECTOR2(0.1f, 1.0f);
		g_fcoh[i].energy = 0;
	}

	//テクスチャの読み込み
	if (FAILED(D3DXCreateTextureFromFile(pDevice, FCOH_TEX_NAME, &g_pTextureFcoh)))
	{
		MessageBox(NULL, "killing", "エラー", MB_OK);
	}

	//デバイス取得
	makeVertexFcoh(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitFcoh
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitFcoh(void)
{
	//テクスチャインターフェイスの解放
	if (g_pTextureFcoh != NULL)
	{
		g_pTextureFcoh->Release();
		g_pTextureFcoh = NULL;
	}

	//頂点バッファ管理の解放
	if (g_pVtxBufferFcoh != NULL)
	{
		g_pVtxBufferFcoh->Release();
		g_pVtxBufferFcoh = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateFcoh
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateFcoh(void)
{
	//変数宣言
	VERTEX2D	*pVtx;

	//使用されていれば座標更新
	if(g_fcoh[0].use == true)
	{
		if(g_fcoh[0].move == true)
		{
			g_fcoh[0].conf.pos.y += MOVE;
			g_fcoh[1].conf.pos.y -= MOVE;

			g_fcoh[0].tex.pos.x += g_fcoh[0].tex.size.x;
			g_fcoh[1].tex.pos.x += g_fcoh[1].tex.size.x;

			if(g_fcoh[0].conf.pos.y >= SCREEN_HEIGHT * 0.5f - HEIGHT * 0.5f)
			{
				g_fcoh[0].conf.pos.y = SCREEN_HEIGHT * 0.5f - HEIGHT * 0.5f;
				g_fcoh[1].conf.pos.y = SCREEN_HEIGHT * 0.5f + HEIGHT * 0.5f;
				g_fcoh[0].move = false;
				g_fcoh[1].move = false;
			}
		}
		else
		{
			g_fcoh[0].count++;
			g_fcoh[0].tex.pos.x += g_fcoh[0].tex.size.x;
			g_fcoh[1].tex.pos.x += g_fcoh[1].tex.size.x;
			if(g_fcoh[0].count >= COUNT_DOWN)
			{
				g_fcoh[0].use = false;
				g_fcoh[1].use = false;
			}
		}
	}

	//頂点情報登録
	g_pVtxBufferFcoh->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < 2; i++)
	{
		setBuffer(pVtx, g_fcoh[i].conf);
		setTexture(pVtx, g_fcoh[i].tex);
		pVtx += NUM_VERTEX;
	}

	g_pVtxBufferFcoh->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawFcoh
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawFcoh(void)
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferFcoh, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, g_pTextureFcoh);

	for(int i = 0; i < 2 && g_fcoh[0].use == true; i++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive
		(
			D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
			NUM_VERTEX * i,			//オフセット(頂点数)
			NUM_POLYGON				//ポリゴンの数
		);
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexFcoh
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexFcoh(LPDIRECT3DDEVICE9 pDevice)
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

								//頂点バッファの設定
	if (FAILED(pDevice->CreateVertexBuffer
	(
		sizeof(VERTEX2D) * NUM_VERTEX * 2,	//頂点バッファサイズ
		D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
		FVF_VERTEX_2D,						//
		D3DPOOL_MANAGED,					//メモリ管理方法
		&g_pVtxBufferFcoh,					//頂点バッファ管理インターフェイス
		NULL)))
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferFcoh->Lock(0, 0, (void**)&pVtx, 0);

	for(int i = 0; i < 2; i++)
	{
		//テクスチャ設定
		setTexture(pVtx, g_fcoh[i].tex);

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
	g_pVtxBufferFcoh->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setFcoh
//返り値	: 
//説明		: 太いちんぽがおまんこに入っちゃった！
//////////////////////////////////////////////////////////////////////////////
void	setFcoh(void)
{
	if(g_fcoh[0].use == false && g_fcoh[0].energy >= NEED_ENERGY)
	{
		g_fcoh[0].conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, -HEIGHT, 0.f);
		g_fcoh[1].conf.pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT + HEIGHT, 0.f);

		g_fcoh[0].tex.pos = D3DXVECTOR2(0.0f,0.0f);
		g_fcoh[1].tex.pos = D3DXVECTOR2(0.0f,0.0f);

		g_fcoh[0].tex.size = D3DXVECTOR2(0.1f,1.0f);
		g_fcoh[1].tex.size = D3DXVECTOR2(0.1f,1.0f);

		g_fcoh[0].count = 0;
		g_fcoh[0].use = true;
		g_fcoh[1].use = true;
		g_fcoh[0].move = true;
		g_fcoh[1].move = true;

		g_fcoh[0].energy = 0;

		//頂点登録
		VERTEX2D	*pVtx;

		g_pVtxBufferFcoh->Lock(0, 0, (void**)&pVtx, 0);

		setBuffer(pVtx, g_fcoh[0].conf);
		
		pVtx += NUM_VERTEX;

		setBuffer(pVtx, g_fcoh[1].conf);

		g_pVtxBufferFcoh->Unlock();
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: damageFcoh
//返り値	: 
//説明		: 殺すぞ
//////////////////////////////////////////////////////////////////////////////
void damageFcoh(void)
{
	//殺すぞ（敵）
	NOTES *notes = GetNotes();	//ノーツの先頭
	for (int i = 0; i < MAX_NOTES; i++)
	{
		if(notes->fPos.x + notes->fWidth >= 0.f && notes->fPos.x <= SCREEN_WIDTH)
		{
			AddDameage(i, DAMAGE);
		}

		notes++;
	}

	//殺すぞ（ボス）
	BOSSNUCLEUS *boss = GetNucleusBoss();
	if (boss->fPos.x + boss->fWidth >= 0.f && boss->fPos.x <= SCREEN_WIDTH)
	{
		AddDameageBoss(0, DAMAGE);
	}

	//殺すぞ（ボス弾）
	BOSSBULLET	*bosBlt = GetBulletBoss();
	for (int i = 0; i < MAX_BOSSBULLET; i++)
	{
		if (bosBlt->fPos.x + bosBlt->fWidth >= 0.f && bosBlt->fPos.x <= SCREEN_WIDTH)
		{
			AddDmgBulletBoss(0, DAMAGE);
		}
		bosBlt++;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getFcohFlag
//返り値	: 
//説明		: 太い太い太い
//////////////////////////////////////////////////////////////////////////////
bool getFcohFlag(void)
{
	return g_fcoh[0].use;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: getFcohMove
//返り値	: 
//説明		: おまんこ～（気さくな挨拶）
//////////////////////////////////////////////////////////////////////////////
bool getFcohMove(void)
{
	return g_fcoh[0].move;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: addFcohEnergy
//返り値	: 
//説明		: エネルギー補充
//////////////////////////////////////////////////////////////////////////////
void addFcohEnergy(int addNum)
{
	g_fcoh[0].energy += addNum;
}