//===================================================
//
// �R���{�\������
// Author : Sato Teruto
//
//===================================================

//----------------------
// �C���N���[�h
//----------------------
#include "combo.h"
#include "number.h"

//=======================
// �R���X�g���N�^
//=======================
CCombo::CCombo() : CObject(1)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ŏ��̈ʒu
	m_numberPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);//�����̈ʒu
	m_nNumCombo = 0;							//�R���{��
	fInterval = 0.0f;							//���l�̊Ԋu

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_aPosTexU[i] = 0;		//���̌��̐��l
		m_pNumber[i] = nullptr;	//���l
	}
}

//=======================
// �f�X�g���N�^
//=======================
CCombo::~CCombo()
{

}

//=======================
// ������
//=======================
HRESULT CCombo::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;		//�ʒu
	fInterval = 50.0f;	//���l�̊Ԋu
	m_newWidth = 60.0f;
	m_newHeight = 80.0f;

	//------------------------------
	// ���l�̐ݒ�
	//------------------------------
	for (int i = 0; i < nMaxDigits; i++)
	{
		D3DXVECTOR3 numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
		m_pNumber[i] = CNumber::Create(numberPos, m_nNumCombo);
		m_pNumber[i]->Set(i);
	}

	SetNumber();

	return S_OK;
}

//=======================
// �I��
//=======================
void CCombo::Uninit()
{
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Uninit();
	}
}

//=======================
// �X�V
//=======================
void CCombo::Update()
{
	float nPoint = 1.5;

	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Update();

		//-------------------
		// �ʒu�̐ݒ�
		//-------------------
		if (m_pos.x <= m_initPos.x)
		{//���̈ʒu��菬�����Ȃ�
			m_pos.x += nPoint;	//�ʒu�̉��Z
		}
		//-------------------
		// �����Ԋu�̏k��
		//-------------------
		if (fInterval >= 50.0f)
		{//���̕����傫���Ȃ�
			fInterval -= nPoint;
		}
		//-------------------
		// ���̏k��
		//-------------------
		if (m_newWidth >= 60.0f)
		{//���̕����傫���Ȃ�
			m_newWidth -= nPoint;
		}
		//-------------------
		// �����̏k��
		//-------------------
		if (m_newHeight >= 80.0f)
		{//���̕����傫���Ȃ�
			m_newHeight -= nPoint;
		}

		//�傫���̍Đݒ�
		m_pNumber[i]->SetScaling(m_newWidth, m_newHeight);

		//���W�̍Đݒ�
		m_numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
		m_pNumber[i]->SetPosition(m_numberPos);
	}
}

//=======================
// �`��
//=======================
void CCombo::Draw()
{
	
	for (int i = 0; i < nMaxDigits; i++)
	{
		m_pNumber[i]->Draw();
	}
}

//=======================
// ����
// �����F�ʒu�A�R���{��
//=======================
CCombo *CCombo::Create(D3DXVECTOR3 pos, int nNum)
{
	CCombo *pCombo = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pCombo = new CCombo;	//����

	if (pCombo != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pCombo->m_nNumCombo = nNum;
		pCombo->m_initPos = pos;

		//������
		pCombo->Init(D3DXVECTOR3(pos));
	}

	return pCombo;
}

//=======================
// ���l�̐ݒ�
//=======================
void CCombo::SetNumber()
{
	for (int i = 0; i < nMaxDigits; i++)
	{//��������
		if (m_pNumber[i] != nullptr)
		{//null����Ȃ��Ȃ�
			//�������v�Z
			int nDigit = (int)(log10(m_nNumCombo) + 1);

			//�i���o�[�̕`���L���E�����ɂ���
			m_pNumber[i]->SetEnable(nMaxDigits - i <= nDigit);

			if (m_nNumCombo == 0)
			{//�R���{����0�Ȃ�
				//�i���o�[�̕`���L���E�����ɂ���
				m_pNumber[nMaxDigits - 1]->SetEnable(true);
			}

			//pow�Ō������o���B
			int nCntNumber = nMaxDigits - i - 1;
			int nNum0 = (int)pow(10, nCntNumber + 1);
			int nNum1 = (int)pow(10, nCntNumber);

			//�����Ƃ̒l�����߂�
			m_aPosTexU[i] = (m_nNumCombo % nNum0) / nNum1;
			m_pNumber[i]->Set(m_aPosTexU[i]);
		}
	}
}

//=======================
// ���l�̉��Z
//=======================
int CCombo::AddNumber(int nNum)
{
	if (m_nNumCombo + nNum < 100)
	{//100�ɂȂ�Ȃ��Ȃ�
		m_nNumCombo += nNum;
	}

	//���l�̐ݒ�
	SetNumber();

	fInterval = 90.0f;
	m_pos.x = 1090.0f;
	m_newWidth = 100.0f;
	m_newHeight = 120.0f;

	for (int i = 0; i < nMaxDigits; i++)
	{//��������
		if (m_pNumber[i] != nullptr)
		{//null����Ȃ��Ȃ�
			m_pNumber[i]->SetScaling(m_newWidth, m_newHeight);
			
			m_numberPos = D3DXVECTOR3(m_pos.x + (fInterval * i), m_pos.y, m_pos.z);
			m_pNumber[i]->SetPosition(m_numberPos);
		}
	}

	return m_nNumCombo;
}

//=======================
// �R���{�����Z�b�g
//=======================
void CCombo::ResetCombo()
{
	m_nNumCombo = 0;

	//���l�̐ݒ�
	SetNumber();
}