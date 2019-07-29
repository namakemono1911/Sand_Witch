/*****************************************************************************
bulletEffect.cpp
Aythor	: ���@��
Data	: 2017_06_09
=============================================================================
Updata

*****************************************************************************/
#ifndef BULLET_EFFECT_H
#define BULLET_EFFECT_H
//////////////////////////////////////////////////////////////////////////////
//�񋓌^��`
//////////////////////////////////////////////////////////////////////////////
typedef enum
{
	BULLET_EFFECT_001 = 0,
	BULLET_EFFECT_MAX
}BULLET_EFFECT_TYPE;

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
void initBulletEffect(void);
void uninitBulletEffect(void);
void updateBulletEffect(void);
void drawBulletEffect(void);
int	setBulletEffect(D3DXVECTOR3 pos, D3DXVECTOR3 size, BULLET_EFFECT_TYPE type);
void setBulletEffectPos(int id, D3DXVECTOR3 pos);
void setBulletEffectSize(int id, D3DXVECTOR3 size);
void releaseBulletEffect(int id);

#endif // !BULLET_EFFECT_H

