/*****************************************************************************
activate.h
Aythor	: 上野　匠
Data	: 2017_06_04
=============================================================================
Updata

*****************************************************************************/
#ifndef ACTIVATE_H
#define ACTIVATE_H
//////////////////////////////////////////////////////////////////////////////
//構造体定義
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	ACTIVE_001 = 0,
	ACTIVE_TYPE_MAX,
}ACTIVE_TYPE;

//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void initActive(void);
void uninitActive(void);
void updateActive(void);
void drawActive(void);
void	setActivate(D3DXVECTOR3 pos, ACTIVE_TYPE type);

#endif