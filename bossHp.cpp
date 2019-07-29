/*****************************************************************************
bossHp.cpp
Aythor	: 上野　匠
Data	: 2016_06_17
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "bossHp.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define BOSS_HP_POS_X	(0)		//ポリゴンの表示位置X
#define BOSS_HP_POS_Y	(0)		//ポリゴンの表示位置Y

#define BOSS_HP_WIDTH	(100.0f)		//ポリゴンの幅
#define BOSS_HP_HEIGHT	(30.0f)			//ポリゴンの高さ

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3		pos;	//座標
	D3DXCOLOR		color;	//バーの色
	bool			use;	//使用フラグ
}BOSS_HP_BAR;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBossHp ( LPDIRECT3DDEVICE9 pDevice );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9	g_pTextureBossHp = NULL;	//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferBossHp = NULL;	//頂点バッファ管理インターフェイス

D3DXVECTOR2 g_posBossHp;	//ポリゴンの中心座標
float g_rotBossHp;			//ポリゴンの回転量
float g_lengthBossHp;		//ポリゴンの対角線の長さ
float g_angleBossHp;		//ポリゴンの対角線の角度

int		maxBossHp = 0;		//最大体力
int		bossHp = 0;			//現在の体力
int		bossHptime;			//ゲージが減るカウントダウン
float	bossHpBarSize;		//サイズ
BOSS_HP_BAR	bossHpBar[6];	//hpバーの設定
D3DXVECTOR3 centerBossHp;	//HPバーの中心座標

//////////////////////////////////////////////////////////////////////////////
//関数名	: initBossHp
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initBossHp( void )
{
	//変数宣言
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得
	int		i;	//loop


	//テクスチャの読み込み
	/*
	if(FAILED(D3DXCreateTextureFromFile(pDevice, BOSS_HP_TEXTURENAME, &g_pTextureBossHp)))
	{
		MessageBox(NULL, "エラー", "エラー", MB_OK);
	}*/

	//ポリゴンの座標
	g_posBossHp = D3DXVECTOR2(BOSS_HP_WIDTH * 0.5f, BOSS_HP_HEIGHT * 0.5f);

	//ポリゴンの角度
	g_rotBossHp = 0.0f;

	//対角線の長さ
	g_lengthBossHp = sqrt(BOSS_HP_WIDTH * BOSS_HP_WIDTH + BOSS_HP_HEIGHT * BOSS_HP_HEIGHT) * 0.5f;

	//ポリゴンの対角線の角度
	g_angleBossHp = atan2(BOSS_HP_HEIGHT, BOSS_HP_WIDTH);

	//構造体初期化
	for(i = 0; i < 6; i++)
	{
		bossHpBar[i].pos.y	=	sin(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.y - 3;
	}

	//左端
	bossHpBar[0].pos.x	=	-cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x + 3;

	//右端
	bossHpBar[5].pos.x	=	cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x - 3;

	bossHpBar[1].pos	=	bossHpBar[5].pos;
	bossHpBar[2].pos	=	bossHpBar[5].pos;
	bossHpBar[3].pos	=	bossHpBar[5].pos;
	bossHpBar[4].pos	=	bossHpBar[5].pos;

	bossHpBar[0].color	=	D3DXCOLOR(0.5f, 1.f, 0.5f, 1.f);
	bossHpBar[1].color	=	bossHpBar[0].color;

	bossHpBar[2].color	=	D3DXCOLOR(0.9f, 0.8f, 0.3f, 1.f);
	bossHpBar[3].color	=	bossHpBar[2].color;

	bossHpBar[4].color	=	D3DXCOLOR(1.f, 0.f, 0.f, 1.f);
	bossHpBar[5].color	=	bossHpBar[4].color;

	//デバイス取得
	makeVertexBossHp(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitBossHp
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitBossHp ( void )
{
	//テクスチャインターフェイスの解放
	if(g_pTextureBossHp != NULL)
	{
		g_pTextureBossHp->Release();
		g_pTextureBossHp = NULL;
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferBossHp != NULL)
	{
		g_pVtxBufferBossHp->Release();
		g_pVtxBufferBossHp = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateBossHp
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateBossHp ( void )
{
	//変数宣言
	VERTEX2D *pVtx = NULL;
	float topLeftX;		//ポリゴンの左上座標X
	float topLeftY;		//ポリゴンの左上座標Y
	float topRightX;	//ポリゴンの右上X
	float topRightY;	//ポリゴンの右上Y
	float bottomLeftX;	//ポリゴンの左下座標X
	float bottomLeftY;	//ポリゴンの左下座標Y
	float bottomRightX;	//ポリゴンの右下X
	float bottomRightY;	//ポリゴンの右下Y
	float percent;
	int	 i;

	//ポリゴンの左上の座標
	topLeftX = -cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	topLeftY = -sin(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//ポリゴンの右上
	topRightX = cos(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	topRightY = sin(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//ポリゴンの左下
	bottomLeftX = -cos(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	bottomLeftY = -sin(g_rotBossHp - g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//ポリゴンの右下の座標
	bottomRightX = cos(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.x;
	bottomRightY = sin(g_rotBossHp + g_angleBossHp) * g_lengthBossHp + g_posBossHp.y;

	//パーセントの計算
	percent = ((float)maxBossHp - (float)bossHp) / (float)maxBossHp;
	bossHpBar[1].pos.x	=	(bossHpBar[5].pos.x) * (1 - percent);
	bossHpBar[2].pos	=	bossHpBar[1].pos;

	//時間計算
	if(bossHptime <= 24)
	{
		bossHptime++;
	}

	if(bossHptime >= 24)
	{
		if(bossHpBar[3].pos.x > (bossHpBar[5].pos.x) * (1 - percent))
		{
			bossHpBar[3].pos.x -= 2.f;
			bossHpBar[4].pos.x = bossHpBar[3].pos.x;
		}
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBossHp->Lock(0, 0, (void**)&pVtx, 0);
	
	//ポリゴンの頂点座標設定
	pVtx[0].pos = D3DXVECTOR3(topLeftX + centerBossHp.x, topLeftY + centerBossHp.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(topRightX + centerBossHp.x, topRightY + centerBossHp.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(bottomLeftX + centerBossHp.x, bottomLeftY + centerBossHp.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(bottomRightX + centerBossHp.x, bottomRightY + centerBossHp.y, 0.0f);

	//テクスチャ頂点座標の設定(0~1)
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
	
	pVtx	+=	4;

	for(i = 0; i < 3; i ++)
	{
		pVtx[0].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i].pos.x + centerBossHp.x,
			bossHpBar[2 * i].pos.y + centerBossHp.y,
			0.f);

		pVtx[1].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i].pos.x + centerBossHp.x,
			bossHpBar[2 * i].pos.y - 44 + centerBossHp.y,
			0.f);
		
		pVtx[2].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i + 1].pos.x + centerBossHp.x,
			bossHpBar[2 * i + 1].pos.y + centerBossHp.y,
			0.f);

		pVtx[3].pos	=	D3DXVECTOR3(
			bossHpBar[2 * i + 1].pos.x + centerBossHp.x,
			bossHpBar[2 * i + 1].pos.y - 44 + centerBossHp.y,
			0.f);
		
		pVtx[0].color = bossHpBar[2 * i].color;
		pVtx[1].color = bossHpBar[2 * i].color;
		pVtx[2].color = bossHpBar[2 * i + 1].color;
		pVtx[3].color = bossHpBar[2 * i + 1].color;

		pVtx	+=	4;
	}

	//バッファアンロック
	g_pVtxBufferBossHp->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawBossHp
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawBossHp ( void )
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
	pDevice->SetStreamSource(0, g_pVtxBufferBossHp, 0, sizeof(VERTEX2D));

	//テクスチャ読み込み
	pDevice->SetTexture(0, NULL);

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
//関数名	: setBossHp
//返り値	: 
//説明		: ボスの体力設定
//////////////////////////////////////////////////////////////////////////////
void setBossHp(int hp)
{
	bossHp = hp;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setBossHpPos
//返り値	: 
//説明		: ボスのHPバーの座標設定
//////////////////////////////////////////////////////////////////////////////
void setBossHpPos(D3DXVECTOR3 pos)
{
	centerBossHp = pos;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setMaxBossHp
//返り値	: 
//説明		: ボスのHPバーの最大値設定
//////////////////////////////////////////////////////////////////////////////
void setMaxBossHp(int hp)
{
	maxBossHp = hp;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexBossHp
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexBossHp ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ
	int		i;	//loop	

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * (NUM_VERTEX + 6 * 2),		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferBossHp,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferBossHp->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定(2D座標・右回り)
	pVtx[0].pos = D3DXVECTOR3(BOSS_HP_POS_X, BOSS_HP_POS_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(BOSS_HP_WIDTH, BOSS_HP_POS_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(BOSS_HP_POS_X, BOSS_HP_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(BOSS_HP_WIDTH, BOSS_HP_HEIGHT, 0.0f);

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

	pVtx	+=	4;

	for(i = 0; i < 3; i ++)
	{
		pVtx[0].pos	=	D3DXVECTOR3(
			bossHpBar[i].pos.x,
			bossHpBar[i].pos.y,
			0.f);

		pVtx[1].pos	=	D3DXVECTOR3(
			bossHpBar[i].pos.x,
			bossHpBar[i].pos.y - 44,
			0.f);

		pVtx[2].pos	-	D3DXVECTOR3(
			bossHpBar[i + 1].pos.x,
			bossHpBar[i + 1].pos.y,
			0.f);

		pVtx[3].pos	-	D3DXVECTOR3(
			bossHpBar[i + 1].pos.x,
			bossHpBar[i + 1].pos.y - 44,
			0.f);
		
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;
		
		pVtx[0].color = bossHpBar[i].color;
		pVtx[1].color = bossHpBar[i].color;
		pVtx[2].color = bossHpBar[i + 1].color;
		pVtx[3].color = bossHpBar[i + 1].color;

		pVtx	+=	4;
	}

	//私のこころアーンロック♪
	g_pVtxBufferBossHp->Unlock();

	return S_OK;
}