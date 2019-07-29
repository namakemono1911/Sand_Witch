/*****************************************************************************
hp.cpp
Aythor	: 上野　匠
Data	: 2016_06_17
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "hp.h"
#include "polygon.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define HP_TEXTURENAME "data/TEXTURE/kobeni0.png"	//読み込むテクスチャファイル
#define MAX_NUM		(20)	//表示できる最大数

#define MARGIN		(D3DXVECTOR2(44, 10))	//余白
#define COUNT_TIME	(10)	//バーが減り始める時間

#define HP_POS_X	(0)		//ポリゴンの表示位置X
#define HP_POS_Y	(0)		//ポリゴンの表示位置Y

#define HP_WIDTH	(500.0f)		//ポリゴンの幅
#define HP_HEIGHT	(50.0f)		//ポリゴンの高さ

#define	LIFE		(500)		//仮のHP

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	POLYGON			conf;		//ポリゴン設定
	D3DXCOLOR		color;		//バーの色
	float			barPos[2];	//バーの座標
	int				time;		//カウントダウン
	int				maxHp;		//最大HP
	int				hp;			//現在のHP
	bool			use;		//使用フラグ
}HP_BAR;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexHp ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureHp = NULL;	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferHp = NULL;	//頂点バッファ管理インターフェイス

D3DXVECTOR2 g_posHp;	//ポリゴンの中心座標
float g_rotHp;			//ポリゴンの回転量
float g_lengthHp;		//ポリゴンの対角線の長さ
float g_angleHp;		//ポリゴンの対角線の角度

int		hp	=	LIFE;
int		time;
float	hpBarSize;
HP_BAR	hpBar[6];

int		g_numHpbar;		//現在使用されているHPバーの数

//////////////////////////////////////////////////////////////////////////////
//関数名	: initHp
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initHp ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得
	int		i;	//loop

	//構造体初期化
	for (int i = 0; i < MAX_NUM; i++)
	{
		hpBar[i].use = false;
	}

	//テクスチャの読み込み
	/*
	if(FAILED(D3DXCreateTextureFromFile(pDevice, HP_TEXTURENAME, &g_pTextureHp)))
	{
		MessageBox(NULL, "エラー", "エラー", MB_OK);
	}*/

	//デバイス取得
	makeVertexHp(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitHp
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitHp ( void )
{
	//テクスチャインターフェイスの解放
	if(g_pTextureHp != NULL)
	{
		g_pTextureHp->Release();
		g_pTextureHp = NULL;
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferHp != NULL)
	{
		g_pVtxBufferHp->Release();
		g_pVtxBufferHp = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateHp
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateHp ( void )
{
	//変数宣言
	float	len;		//バーの長さ

	//HPバー更新
	if(GetKeyboardPress(DIK_A))
	{
		hpBar[0].hp--;
		hpBar[0].time =	0;
		if(hpBar[0].hp < 0)
		{
			hpBar[0].hp =	0;
		}
	}
	
	if(GetKeyboardPress(DIK_D))
	{
		hpBar[0].hp--;
		hpBar[0].time =	0;

		if(hpBar[0].hp > LIFE)
		{
			hpBar[0].hp =	LIFE;
		}
	}

	//使われているHPバー更新
	for (int i = 0, j = 0; j < MAX_NUM; i++)
	{
		if (hpBar[i].use == true)
		{
			//パーセントの計算
			float	percent;
			len = hpBar[i].conf.size.x - MARGIN.x * 2;

			percent = ((float)hpBar[i].maxHp - (float)hpBar[i].hp) / (float)hpBar[i].maxHp;
			hpBar[i].barPos[0] = (hpBar[i].conf.pos.x - hpBar[i].conf.size.x * 0.5f) - len * (1 - percent);

			//時間計算
			if(time <= COUNT_TIME)
			{
				time++;
			}

			if(time >= COUNT_TIME)
			{
				if(hpBar[i].barPos[1] > hpBar[i].barPos[0])
				{
					hpBar[i].barPos[1] -= 2.f;
				}
			}

			j++;
		}
	}

	//頂点バッファをロックして仮想アドレスを取得
	VERTEX2D *pVtx = NULL;
	g_pVtxBufferHp->Lock(0, 0, (void**)&pVtx, 0);
	
	for (int i = 0, j = 0; j < g_numHpbar; i++)
	{
		if (hpBar[i].use == true)
		{
			//ポリゴンの頂点座標設定
			setBuffer(pVtx, hpBar[i].conf);

			//テクスチャ頂点座標の設定(0~1)
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
			pVtx	+=	4;

			//残りの体力
			pVtx[0].pos = D3DXVECTOR3(
				hpBar[i].conf.pos.x - len * 0.5f,
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y, 
				0.f);

			pVtx[1].pos = D3DXVECTOR3(
				hpBar[i].conf.pos.x - len * 0.5f,
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[2].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			pVtx[3].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[0].color = pVtx[1].color =
			pVtx[2].color = pVtx[3].color = hpBar[i].color;

			//縮退ポリゴン
			pVtx[4].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[5].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			//減ってく部分
			pVtx[6].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			pVtx[7].pos = D3DXVECTOR3(
				hpBar[i].barPos[0],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[8].pos = D3DXVECTOR3(
				hpBar[i].barPos[1],
				hpBar[i].conf.pos.y + hpBar[i].conf.size.y * 0.5f - MARGIN.y,
				0.f);

			pVtx[9].pos = D3DXVECTOR3(
				hpBar[i].barPos[1],
				hpBar[i].conf.pos.y - hpBar[i].conf.size.y * 0.5f + MARGIN.y,
				0.f);

			pVtx[6].color = pVtx[7].color =
			pVtx[8].color = pVtx[9].color = D3DCOLOR_RGBA(192, 255, 255, 255);

			//縮退ポリゴン


			j++;
		}
	}
	//バッファアンロック
	g_pVtxBufferHp->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawHp
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawHp ( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_DITHERENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferHp, 0, sizeof(VERTEX2D));

	//テクスチャ読み込み
	//pDevice->SetTexture(0,g_pTextureHp);

	//ポリゴンの描画
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		0,						//オフセット(頂点数)
		NUM_POLYGON				//ポリゴンの数
		);
	
	pDevice->DrawPrimitive
		(
		D3DPT_TRIANGLESTRIP,	//ポリゴンの種類
		4,						//オフセット(頂点数)
		NUM_POLYGON * 8				//ポリゴンの数
		);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setHpbar
//返り値	: 
//説明		: HPバー設定
//////////////////////////////////////////////////////////////////////////////
int setHpbar(int maxHp, D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR color)
{
	for (int i = 0; i < MAX_NUM; i++)
	{
		if (hpBar[i].use == false)
		{
			hpBar[i].maxHp = maxHp;			//最大体力
			hpBar[i].hp = maxHp;			//現在の体力
			hpBar[i].conf.pos = pos;		//中心座標
			hpBar[i].conf.size = size;		//サイズ
			hpBar[i].color = color;			//バーの色
			hpBar[i].time = 0;

			g_numHpbar++;
			return i;
		}
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexHp
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
void releaseHpbar(int num)
{
	if (hpBar[num].use == true)
	{
		hpBar[num].use = false;
		g_numHpbar--;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexHp
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexHp ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ
	int		i;	//loop	

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * (NUM_VERTEX + 6 * 2) * MAX_NUM,		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferHp,					//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferHp->Lock(0, 0, (void**)&pVtx, 0);

	for (int i = 0; i < (NUM_VERTEX + 6 * 2) * MAX_NUM; i++)
	{
		//rhwの設定(必ず1.0f)
		pVtx[0].rhw = 1.0f;

		//頂点カラーの設定(0~155の整数値)
		pVtx[0].color = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx++;
	}

	//私のこころアーンロック♪
	g_pVtxBufferHp->Unlock();

	return S_OK;
}