/*****************************************************************************
particle.cpp
Aythor	: 上野　匠
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//ヘッダーファイルインクルード
//////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "polygon.h"
#include "particle.h"
#include "input.h"
#include <math.h>

//////////////////////////////////////////////////////////////////////////////
//定数定義
//////////////////////////////////////////////////////////////////////////////
#define TEXTURE_NAME	"data/TEXTURE/effect000.jpg"	//テクスチャファイルネーム

#define PARTICLE_POS_X	(SCREEN_WIDTH * 0.5f)		//ポリゴンの表示位置X
#define PARTICLE_POS_Y	(SCREEN_HEIGHT * 0.5f)		//ポリゴンの表示位置Y

#define PARTICLE_WIDTH	(SCREEN_WIDTH)				//ポリゴンの幅
#define PARTICLE_HEIGHT	(SCREEN_HEIGHT)				//ポリゴンの高さ
#define PARTICLE_RATE	(0.0001f)					//フェード係数

#define	MAX_PARTICLE	(1024)						//パーティクルの最大量

//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ROTPOLYGON	conf;		//回転ポリゴンの各種設定
	D3DXCOLOR	color;		//ポリゴンの色
	float		angle;		//発射角度
	float		life;		//寿命
	float		move;		//移動量
	bool		use;		//trueで使用されている
}PARTICLE;

//typedef enum
//{
//	MODE_ANGLE = 0,		//角度操作
//	MODE_LIFE,			//寿命操作
//	MODE_MOVE,			//加速度操作
//	MODE_MAX,			//モードの総数
//	MODE_NONE			//実質NULL
//}OPERATION;				//パーティクルの操作モード

PARTICLE	particle[MAX_PARTICLE];
//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexParticle ( LPDIRECT3DDEVICE9 pDevice );
void	setConf	( int num );

//////////////////////////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////////////////////////
LPDIRECT3DTEXTURE9		g_pTextureParticle = NULL;		//テクスチャインターフェイス
LPDIRECT3DVERTEXBUFFER9 g_pVtxBufferParticle = NULL;	//頂点バッファ管理インターフェイス

D3DXVECTOR3	g_pos;		//発生位置
D3DXCOLOR	g_color;	//ポリゴン色
float		g_size;		//サイズ
float		g_angle;	//発射角度
float		g_move;		//移動量
float		g_life;		//寿命

//////////////////////////////////////////////////////////////////////////////
//関数名	: initParticle
//返り値	: 
//説明		: ポリゴン初期化
//////////////////////////////////////////////////////////////////////////////
void initParticle ( void )
{
	//変数宣言
	int		i;		//loop
	LPDIRECT3DDEVICE9 pDevice = getDevice();	//デバイスポインタ取得
	
	//グローバル変数初期化
	g_pos = D3DXVECTOR3(PARTICLE_POS_X, PARTICLE_POS_Y, 0.f);
	//g_color = 0xf9861e;
	g_color = D3DXCOLOR(0.9f, 0.5f, 0.03f, 0.5f);
	g_size = 30.f;
	g_angle = 6.28f;
	g_move = 2;
	g_life = 0.001f;

	//構造体初期化
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		//使用判定
		particle[i].use = false;
	}

	//テクスチャの読み込み
	if(FAILED(D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME, &g_pTextureParticle)))
	{
		MessageBox(NULL, "particle", "エラー", MB_OK);
	}

	//デバイス取得
	makeVertexParticle(pDevice);
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: uninitParticle
//返り値	: 
//説明		: ポリゴン終了
//////////////////////////////////////////////////////////////////////////////
void uninitParticle ( void )
{
	//テクスチャインターフェイスの解放
	if(g_pTextureParticle != NULL)
	{
		g_pTextureParticle->Release();
		g_pTextureParticle = NULL;
	}

	//頂点バッファ管理の解放
	if(g_pVtxBufferParticle != NULL)
	{
		g_pVtxBufferParticle->Release();
		g_pVtxBufferParticle = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: updateParticle
//返り値	: 
//説明		: ポリゴン更新
//////////////////////////////////////////////////////////////////////////////
void updateParticle ( void )
{
	//変数宣言
	int		i;		//loop
	VERTEX2D	*pVtx;

	//新しい粒子を発生させる
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		if(particle[i].use == false)
		{
			particle[i].use = true;
			setConf(i);
			break;
		}
	}

	//既に出ている粒子更新
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		if(particle[i].use == true)
		{
			//座標更新
			particle[i].conf.conf.pos = D3DXVECTOR3(
				particle[i].move * cos(particle[i].angle) + particle[i].conf.conf.pos.x,
				particle[i].move * sin(particle[i].angle) + particle[i].conf.conf.pos.y,
				0.f);

			//色更新
			particle[i].color.a -= particle[i].life;

			if(particle[i].color.a < 0.f)
			{
				particle[i].color.a = 0.f;
				particle[i].use = false;
			}
		}
	}

	//=============================
	// キー操作
	//=============================


	//--------------------------------------------------------------------------
	// 描画位置確定
	//--------------------------------------------------------------------------
	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferParticle->Lock(0, 0, (void**)&pVtx, 0);

	//座標設定
	for(i = 0; i < MAX_PARTICLE; i++)
	{
		//使われている粒子だけ登録
		if(particle[i].use == true)
		{
			//バッファに座標登録
			setRotBuffer(pVtx, particle[i].conf);

			//縮退ポリゴン設定
			if(i < MAX_PARTICLE - 1)
			{
				pVtx[4].pos = D3DXVECTOR3(
					cos(particle[i].conf.rot + particle[i].angle) * particle[i].conf.length + particle[i].conf.conf.pos.x,
					sin(particle[i].conf.rot + particle[i].angle) * particle[i].conf.length + particle[i].conf.conf.pos.y,
					0.0f);

				pVtx[5].pos = D3DXVECTOR3(
					-cos(particle[i + 1].conf.rot + particle[i + 1].angle) * particle[i + 1].conf.length + particle[i + 1].conf.conf.pos.x,
					-sin(particle[i + 1].conf.rot + particle[i + 1].angle) * particle[i + 1].conf.length + particle[i + 1].conf.conf.pos.y,
					0.0f);
			}

			pVtx[0].color = particle[i].color;
			pVtx[1].color = particle[i].color;
			pVtx[2].color = particle[i].color;
			pVtx[3].color = particle[i].color;

			//ポインタ移動
			pVtx += NUM_VERTEXLIST;
		}

	}

	//バッファアンロック
	g_pVtxBufferParticle->Unlock();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: drawParticle
//返り値	: 
//説明		: ポリゴン描写
//////////////////////////////////////////////////////////////////////////////
void drawParticle ( void )
{
	//変数宣言
	int		i;			//loop
	int		numVertex;	//頂点数
	LPDIRECT3DDEVICE9 pDevice = getDevice();

	//描画設定を加算合成に変更
	addDevice();

	//ストリーム作成
	pDevice->SetStreamSource(0, g_pVtxBufferParticle, 0, sizeof(VERTEX2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0,g_pTextureParticle);

	//ポリゴンの描画
	for(i = 0, numVertex = 0; i < MAX_PARTICLE; i++)
	{
		//使われている粒子だけ描画
		if(particle[i].use == true)
		{
			pDevice->DrawPrimitive
				(
				D3DPT_TRIANGLESTRIP,			//ポリゴンの種類
				numVertex * NUM_VERTEXLIST,		//オフセット(頂点数)
				NUM_POLYGON						//ポリゴンの数
				);

			//頂点数加算
			numVertex++;
		}
	}

	//描画設定を乗算合成に変更
	initDevice();
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: makeVertexParticle
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
HRESULT makeVertexParticle ( LPDIRECT3DDEVICE9 pDevice )
{
	//変数宣言
	int		i;		//loop
	VERTEX2D *pVtx = NULL;;		//仮想アドレス用ポインタ

	//頂点バッファの設定
	if(FAILED(pDevice->CreateVertexBuffer
			(
			sizeof(VERTEX2D) * NUM_VERTEXLIST * MAX_PARTICLE,		//頂点バッファサイズ
			D3DUSAGE_WRITEONLY,					//頂点バッファの使用方法
			FVF_VERTEX_2D,						//
			D3DPOOL_MANAGED,					//メモリ管理方法
			&g_pVtxBufferParticle,				//頂点バッファ管理インターフェイス
			NULL
			)
		))
		
	{
		return E_FAIL;
	}

	//頂点バッファをロックして仮想アドレスを取得
	g_pVtxBufferParticle->Lock(0, 0, (void**)&pVtx, 0);

	for(i = 0; i < MAX_PARTICLE; i++)
	{
		//頂点座標の設定(2D座標・右回り)
		pVtx[0].pos = D3DXVECTOR3(PARTICLE_POS_X, PARTICLE_POS_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(PARTICLE_WIDTH, PARTICLE_POS_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(PARTICLE_POS_X, PARTICLE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(PARTICLE_WIDTH, PARTICLE_HEIGHT, 0.0f);

		//rhwの設定(必ず1.0f)
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定(0~155の整数値)
		pVtx[0].color = g_color;
		pVtx[1].color = g_color;
		pVtx[2].color = g_color;
		pVtx[3].color = g_color;
	
		//テクスチャ頂点座標の設定(0~1)
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		//ポインタ移動
		pVtx += NUM_VERTEX;
	}

	//私のこころアーンロック♪
	g_pVtxBufferParticle->Unlock();

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////
//関数名	: setConf
//返り値	: 
//説明		: 頂点作成
//////////////////////////////////////////////////////////////////////////////
void	setConf	( int num )
{
	//変数宣言
	float	size;	//サイズのワーク
	float	color;	//カラーのワーク

	//乱数をサイズに設定
	size = (float)(rand() % 20);
	size -= g_size;

	//各種初期化
	initRotPolygon(&particle[num].conf, 
		g_pos,
		D3DXVECTOR3(size, size, 0.f));

	//色設定
	particle[num].color = g_color;
	color = (float)(rand() % 50);
	color /= 100;
	particle[num].color.a += color; 

	//角度設定
	particle[num].angle = (float)(rand() % (int)(g_angle * 100) - 314);
	particle[num].angle /= 100;

	//寿命設定
	particle[num].life = (float)(rand() % 10 + 1);
	particle[num].life /= 10000.f;
	particle[num].life += g_life;

	//移動量
	particle[num].move = (float)(rand() % 5);
	particle[num].move -= g_move;
}