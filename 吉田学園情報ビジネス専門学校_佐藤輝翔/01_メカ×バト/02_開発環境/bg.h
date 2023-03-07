//===================================================
//
// �w�i�̃w�b�_�[
// Author : Sato Teruto
//
//===================================================
#ifndef _BG_H_
#define _BG_H_	

//--------------------------------
// �C���N���[�h
//--------------------------------
#include "object2D.h"

//--------------------------------
// �w�i�N���X
//--------------------------------
class CBg : public CObject
{
public:
	enum BGTYPE
	{
		BGTYPE_TITLE,		//�^�C�g��
		BGTYPE_RESULT,		//���U���g
		BGTYPE_MANUAL,		//�������
		BGTYPE_TUTORIAL1,	//�`���[�g���A��1
		BGTYPE_TUTORIAL2,	//�`���[�g���A��2
		BGTYPE_PRESS,		//�L�[�����̎w��
		BGTYPE_COMBO,		//�R���{
		BGTYPE_TIMER,		//�^�C�}�[
		BGTYPE_PLAYER_HP,	//�v���C���[HP
		BGTYPE_ENEMY_HP,	//�G�l�~�[HP
		BGTYPE_BLACK,		//������
		BGTYPE_MAX
	};

	CBg();				//�R���X�g���N�^
	~CBg() override;	//�f�X�g���N�^

	//-------------------
	// �����o�֐�
	//-------------------
	HRESULT Init(D3DXVECTOR3 pos) override;
	void Uninit() override;
	void Update() override;
	void Draw()	  override;

	//-------------------
	// �Q�b�^�[
	//-------------------
	D3DXVECTOR3 GetPosition() override  { return m_pos; }		//�ʒu�̎擾
	float GetWidth() override			{ return 0.0f; }		//���̎擾
	float GetHeight() override			{ return 0.0f; }		//�����̎擾

	//-------------------
	// �ÓI�����o�֐�
	//-------------------
	static CBg *Create(D3DXVECTOR3 pos, BGTYPE type);	//����

private:
	//-------------------
	// �����o�ϐ�
	//-------------------
	CObject2D *m_pObject2D;		//�I�u�W�F�N�g2D
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXCOLOR m_col;			//�F
	int m_nFlashTime;			//�_�Ŏ���
	float m_fWidth;				//��
	float m_fHeight;			//����
	BGTYPE m_type;				//���
};

#endif // !_BG_H_