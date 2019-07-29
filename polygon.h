/*****************************************************************************
polygon.h
Aythor	: ���@��
Data	: 2016_07_05
=============================================================================
Updata

*****************************************************************************/
#ifndef POLYGON_H
#define POLYGON_H

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�萔��`
//////////////////////////////////////////////////////////////////////////////
typedef struct
{
	D3DXVECTOR3	pos;		//�\�����W
	D3DXVECTOR3	size;		//�|���S���̕�����
}POLYGON;

typedef struct
{
	POLYGON		conf;		//���S���W�ƃT�C�Y
	float	rot;			//�|���S���̉�]��
	FLOAT	length;			//�|���S���̑Ίp���̒���
	float	angle;			//�|���S���̑Ίp���̊p�x
}ROTPOLYGON;

typedef struct
{
	D3DXVECTOR2	pos;		//�e�N�X�`���̕`��ʒu
	D3DXVECTOR2	size;		//�e�N�X�`���̃T�C�Y
}TEXTURE;

//////////////////////////////////////////////////////////////////////////////
//�w�b�_�[�t�@�C���C���N���[�h
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////
void initDevice ( void );
void addDevice ( void );
void initPolygon ( POLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size );
void initRotPolygon ( ROTPOLYGON *polygon, D3DXVECTOR3 pos, D3DXVECTOR3 size );
void initTexture ( TEXTURE	*tex, D3DXVECTOR2 pos, D3DXVECTOR2 size );
void setTexture ( VERTEX2D *pVtx, TEXTURE texture );
void setBuffer ( VERTEX2D *pVtx, POLYGON polygon );
void setListBuffer ( VERTEX2D *pVtx, POLYGON polygon );
void setRotBuffer ( VERTEX2D *pVtx, ROTPOLYGON polygon );
void setDegenerate ( VERTEX2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 nextPos );

//////////////////////////////////////////////////////////////////////////////
//�\���̒�`
//////////////////////////////////////////////////////////////////////////////

#endif