/*****************************************************************************
fcoh.cpp
Aythor	: 上野　匠
Data	: 2017_06_05
=============================================================================
Updata

*****************************************************************************/
#ifndef FCOH_H
#define	FCOH_H
//////////////////////////////////////////////////////////////////////////////
//プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////
void initFcoh(void);
void uninitFcoh(void);
void updateFcoh(void);
void drawFcoh(void);
void setFcoh(void);
bool getFcohFlag(void);
bool getFcohMove(void);
void damageFcoh(void);
void addFcohEnergy(int addNum);

#endif // !FCOH_H