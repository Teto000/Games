//===================================================
//
// HP�̏���
// Author : Sato Teruto
//
//===================================================

//-----------------------
// �C���N���[�h
//-----------------------
#include "hp.h"
#include "fream.h"
#include "game.h"
#include "enemy.h"

//==========================
// �R���X�g���N�^
//==========================
CHP::CHP() : CGauge(1)
{

}

//==========================
// �f�X�g���N�^
//==========================
CHP::~CHP()
{

}

//==========================
// ������
//==========================
HRESULT CHP::Init(D3DXVECTOR3 pos)
{
	CGauge::Init(pos);

	return S_OK;
}

//==========================
// �I��
//==========================
void CHP::Uninit()
{
	CGauge::Uninit();
}

//==========================
// �X�V
//==========================
void CHP::Update()
{
	CGauge::Update();

	if (SubHP())
	{//�Q�[�W�������Ă�����
		return;
	}

	//-------------------------
	// ��ނ��Ƃ̏���
	//-------------------------
	switch (m_type)
	{
	//----------------------------
	// �v���C���[��HP
	//----------------------------
	case GAUGETYPE_HP_PLAYER:
		if (m_fRemLife <= 20)
		{//HP��20%�ȉ��ɂȂ�����
			//�ԐF�ɂ���
			CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}
		else if (m_fRemLife <= 50)
		{//HP��50%�ȉ��ɂȂ�����
			//���F�ɂ���
			CObject2D::SetColor(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			//�ΐF�ɂ���
			CObject2D::SetColor(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		}
		break;

	//----------------------------
	// �G��HP
	//----------------------------
	case GAUGETYPE_HP_ENEMY:
		//�I�����W�F�ɂ���
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
		break;

	//----------------------------
	// �u���C�N�Q�[�W
	//----------------------------
	case GAUGETYPE_BREAK:
		//�I�����W�F�ɂ���
		CObject2D::SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		break;

	default:
		break;
	}
}

//==========================
// �`��
//==========================
void CHP::Draw()
{
	if (m_type == GAUGETYPE_BREAK)
	{
		if (CGame::GetEnemy()->GetState() != CEnemy::ENEMYSTATE_BREAK)
		{
			CGauge::Draw();
		}
	}
	else
	{
		CGauge::Draw();
	}
}

//==========================
// ����
//==========================
CHP* CHP::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, GAUGETYPE type)
{
	CHP *pHP = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pHP = new CHP;	//����

	if (pHP != nullptr)
	{//NULL�`�F�b�N
		//�ϐ��ɑ��
		pHP->m_pos = pos;			//�ʒu
		pHP->m_fWidth = fWidth;		//��
		pHP->m_fHeight = fHeight;	//����
		pHP->m_type = type;			//���

		//������
		pHP->Init(D3DXVECTOR3(pos));
		pHP->SetObjType(OBJTYPE_GAUGE);
	}

	return pHP;
}