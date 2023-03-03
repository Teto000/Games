//===================================================
//
// 2D�|���S���w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object2D.h"

//--------------------------------
// �o���b�g�N���X
//--------------------------------
class CPolygon : public CObject2D
{
public:
	enum POLYGONTYPE
	{
		POLYGONTYPE_NONE = 0,
		POLYGONTYPE_AIM,		//�Ə�
		POLYGONTYPE_MAX
	};

	CPolygon();				//�R���X�g���N�^
	~CPolygon() override;	//�f�X�g���N�^

	//-------------------
	// �����o�֐�
	//-------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//-------------------
	// �ÓI�����o�֐�
	//-------------------
	static CPolygon* Create(POLYGONTYPE type);	//����
	
private:
	//-------------------
	// �����o�ϐ�
	//-------------------
	float		m_fRadius;	//���a
	POLYGONTYPE m_type;		//���
};

#endif // !_BG_H_