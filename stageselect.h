//==========================================================================================
//	Xe[WZNg[stageselect.cpp]
//	Author : KAZUNORI MARUHASHI
//
//	Update :
//		YYYY/MM/DD	Updater :
//
//		2017/06/04	Updater : KAZUNORI MARUHASHI
//			
//			
//	
//==========================================================================================
#ifndef _STAGESELECT_H_	//ñdCN[hh~
#define _STAGESELECT_H_

//==========================================================================================
//	CN[ht@C
//==========================================================================================
//ùèwb_

//VKwb_
#include "main.h"

//==========================================================================================
//	\¢Ìè`
//==========================================================================================
typedef enum
{
	STAGESELECT_TEX_TITLE = 0,		//Xe[WZNg¶
	STAGESELECT_TEX_TURORIAL,		//`[gA
	STAGESELECT_TEX_STAGE1,			//ºACR
	STAGESELECT_TEX_STAGE2,			//áRACR
	STAGESELECT_TEX_STAGE3,			//ÎRACR
	STAGESELECT_TEX_CURSOL,			//Xe[WJ[\
	STAGESELECT_TEX_STAGE1DIF1,		//ºïÕxÕ
	STAGESELECT_TEX_STAGE1DIF2,		//ºïÕx
	STAGESELECT_TEX_STAGE1DIF3,		//ºïÕxï
	STAGESELECT_TEX_STAGE2DIF1,		//áRïÕxÕ
	STAGESELECT_TEX_STAGE2DIF2,		//áRïÕx
	STAGESELECT_TEX_STAGE2DIF3,		//áRïÕxï
	STAGESELECT_TEX_STAGE3DIF1,		//ÎRïÕxÕ
	STAGESELECT_TEX_STAGE3DIF2,		//ÎRïÕx
	STAGESELECT_TEX_STAGE3DIF3,		//ÎRïÕxï
	STAGESELECT_TEX_DIFCURSOL,		//ïÕxJ[\

	STAGESELECT_TEX_BG_STAGE1,			//ºACR
	STAGESELECT_TEX_BG_STAGE2,			//áRACR
	STAGESELECT_TEX_BG_STAGE3,			//ÎRACR

	STAGESELECT_TEX_MAX,			//UgeNX`
} STAGESELECT_TEX_LABEL;	//eNX`px

typedef enum
{
	STAGESELECT_OBJ_BG = 0,		//wiæ
	STAGESELECT_OBJ_BGFADE,		//wiætF[h
	STAGESELECT_OBJ_TITLE,		//Xe[WZNg¶
	STAGESELECT_OBJ_TURORIAL,	//`[gA
	STAGESELECT_OBJ_STAGE1,		//ºACR
	STAGESELECT_OBJ_STAGE2,		//áRACR
	STAGESELECT_OBJ_STAGE3,		//ÎRACR
	STAGESELECT_OBJ_CURSOL,		//Xe[WJ[\
	STAGESELECT_OBJ_DIFCURSOL,	//ïÕxJ[\
	STAGESELECT_OBJ_STAGE1DIF1,	//ºïÕxÕ
	STAGESELECT_OBJ_STAGE1DIF2,	//ºïÕx
	STAGESELECT_OBJ_STAGE1DIF3,	//ºïÕxï
	STAGESELECT_OBJ_STAGE2DIF1,	//áRïÕxÕ
	STAGESELECT_OBJ_STAGE2DIF2,	//áRïÕx
	STAGESELECT_OBJ_STAGE2DIF3,	//áRïÕxï
	STAGESELECT_OBJ_STAGE3DIF1,	//ÎRïÕxÕ
	STAGESELECT_OBJ_STAGE3DIF2,	//ÎRïÕx
	STAGESELECT_OBJ_STAGE3DIF3,	//ÎRïÕxï
	STAGESELECT_OBJ_MAX,		//UgeNX`
} STAGESELECT_OBJ_LABEL;	//IuWFNgpx

struct STAGESELECT
{
	D3DXVECTOR3		Pos;		//æÊu
	D3DXVECTOR3		Size;		//æTCY
	D3DXVECTOR2		UV;			//UVl
	D3DXVECTOR2		UVSize;		//UVTCY
	STAGESELECT_TEX_LABEL	label;	//`æeNX`
	float			fAlpha;		//¿l
	bool			bDraw;		//`æÂÛ
};

//==========================================================================================
//	NXè`
//==========================================================================================

//==========================================================================================
//	}Nè`
//==========================================================================================
void InitStageSelect(void);
void UninitStageSelect(void);
void UpdateStageSelect(void);
void DrawStageSelect(void);

//==========================================================================================
//	vg^Cvé¾
//==========================================================================================


#endif