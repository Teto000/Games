//===================================================
//
// �_���[�W������
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "damage.h"
#include "num_board.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "camera.h"

//=======================
// �R���X�g���N�^
//=======================
CDamage::CDamage() : CBillBoard(0)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu
	m_nAtkValue = 0;						//�R���{��
	m_nDeleteTime = 0;						//������܂ł̎���

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;			//���̌��̐��l
		m_pNumBoard[i] = nullptr;	//����
	}
}

//=======================
// �f�X�g���N�^
//=======================
CDamage::~CDamage()
{

}

//=======================
// ������
//=======================
HRESULT CDamage::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;		//�ʒu
	m_fWidth = 30.0f;	//��
	m_fHeight = 40.0f;	//����

	if (type == DAMAGE_TYPE_CRITICAL)
	{//�N���e�B�J���Ȃ�
		m_col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);	//�F
	}
	else
	{
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F
	}

	//------------------------------
	// ���l�̐ݒ�
	//------------------------------
	float cameraRotY = CGame::GetCamera()->GetRot().y;	//�J�����̌������擾
	cameraRotY += D3DX_PI / 2;	//90����]
	D3DXVECTOR3 vec = D3DXVECTOR3(sinf(cameraRotY), cosf(cameraRotY), 0.0f);	//�x�N�g���̌v�Z

	for (int i = 0; i < nMaxDigits; i++)
	{
		//�J�������Ɍ����ĕ��Ԉʒu���v�Z
		D3DXVECTOR3 numberPos = D3DXVECTOR3((m_pos.x - (m_fWidth / 2)) + ((m_fWidth * vec.x) * i),
											m_pos.y,
											m_pos.z + ((m_fWidth * vec.y) * i));

		m_pNumBoard[i] = CNumBoard::Create(numberPos, m_nAtkValue);
		m_pNumBoard[i]->Set(i);							//�l�̐ݒ�
		m_pNumBoard[i]->SetSize(m_fWidth, m_fHeight);	//�傫���̐ݒ�
		m_pNumBoard[i]->SetColor(m_col);				//�F�̐ݒ�
	}

	SetNumber();

	return S_OK;
}

//=======================
// �I��
//=======================
void CDamage::Uninit()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		if (m_pNumBoard[i] != nullptr)
		{//null����Ȃ��Ȃ�
			m_pNumBoard[i]->Uninit();
			m_pNumBoard[i] = nullptr;
		}
	}
}

//=======================
// �X�V
//=======================
void CDamage::Update()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		if (m_pNumBoard[i] == nullptr)
		{//null�Ȃ�
			continue;
		}

		//----------------------
		// �㏸������
		//----------------------
		if (m_nDeleteTime >= 20)
		{
			D3DXVECTOR3 pos = m_pNumBoard[i]->GetPosition();
			pos.y += 1.0f;
			m_pNumBoard[i]->SetPos(pos);
		}

		m_pNumBoard[i]->Update();

		//�F�̐ݒ�
		m_pNumBoard[i]->SetColor(m_col);
	}

	//������܂ł̎��Ԃ𐔂���
	m_nDeleteTime++;

	if (m_nDeleteTime >= 20)
	{//��莞�Ԃ��o�߂�����
		//�����x�̌���
		m_col.a -= 0.05f;
	}

	if (m_col.a <= 0.0f)
	{//���S�ɓ����ɂȂ�����
		Uninit();
		return;
	}
}

//=======================
// �`��
//=======================
void CDamage::Draw()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		if (m_pNumBoard[i] != nullptr)
		{//null����Ȃ��Ȃ�
			m_pNumBoard[i]->Draw();
		}
	}
}

//=======================
// ����
// �����F�ʒu�A�R���{��
//=======================
CDamage *CDamage::Create(D3DXVECTOR3 pos, int nNum, DAMAGE_TYPE type)
{
	CDamage *pDamage = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pDamage = new CDamage;	//����

	if (pDamage != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pDamage->m_nAtkValue = nNum;
		pDamage->type = type;

		//������
		pDamage->Init(pos);
	}

	return pDamage;
}

//=======================
// ���l�̐ݒ�
//=======================
void CDamage::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//��������
		//�������v�Z
		int nDigit = (int)(log10(m_nAtkValue) + 1);

		//�i���o�[�̕`���L���E�����ɂ���
		m_pNumBoard[i]->SetEnable(nMaxDigits - i <= nDigit);

		//pow�Ō������o���B
		int nCntNumber = nMaxDigits - i - 1;
		int nNum0 = (int)pow(10, nCntNumber + 1);
		int nNum1 = (int)pow(10, nCntNumber);

		//�����Ƃ̒l�����߂�
		m_aPosTexU[i] = (m_nAtkValue % nNum0) / nNum1;
		m_pNumBoard[i]->Set(m_aPosTexU[i]);
	}
}