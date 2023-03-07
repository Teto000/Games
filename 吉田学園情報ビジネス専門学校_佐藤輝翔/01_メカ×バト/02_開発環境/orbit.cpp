//===================================================
//
// �O�Ղ̏���
// Author:Teruto Sato
//
//===================================================

//-----------------------
// �C���N���[�h
//-----------------------
//
#include <assert.h>
#include "orbit.h"
#include "application.h"
#include "renderer.h"
#include "game.h"
#include "player.h"
#include "model.h"

//==========================
// �R���X�g���N�^
//==========================
COrbit::COrbit() : CObject(1)
{
	m_offsetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�I�t�Z�b�g���W
	m_worldPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���[���h���W
	m_initCol = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	//�F�̏����l
	m_nNumVtx = 0;		//���_��

	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���b�N�X
	D3DXMatrixIdentity(&m_pMtxParent);	//�e�̃}�g���b�N�X
	m_pVtxBuff = nullptr;				//���_�o�b�t�@�ւ̃|�C���^
}

//==========================
// �f�X�g���N�^
//==========================
COrbit::~COrbit()
{

}

//==========================
// ������
//==========================
HRESULT COrbit::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_offsetPos = pos;	//�ʒu
	m_initCol = D3DXCOLOR(0.0f, 1.0f, 0.0f, 0.5f);	//�F�̏����l

	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//----------------------------------
	// ���_�o�b�t�@�̐���
	//----------------------------------
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * nMaxVtx,	//�m�ۂ���o�b�t�@�̃T�C�Y
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//----------------------------------
	// ���_���̐ݒ�
	//----------------------------------
	for (int i = 0; i < nMaxVtx; i++)
	{
		//------------------------
		// ���_���W�̐ݒ�
		//------------------------
		pVtx[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//------------------------
		// �e���_�̖@���̐ݒ�
		//------------------------
		pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//------------------------
		// ���_�J���[�̐ݒ�
		//------------------------
		pVtx[i].col = m_initCol;

		//------------------------
		// �e�N�X�`�����W�̐ݒ�
		//------------------------
		//pVtx[i].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	pVtx += m_nNumVtx;

	return S_OK;
}

//==========================
// �I��
//==========================
void COrbit::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//==========================
// �X�V
//==========================
void COrbit::Update()
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//--------------------------------------
	// ���_���W����납��R�s�[����
	//--------------------------------------
	for (int i = m_nNumVtx - 1; i > 0; i--)
	{//���_�����~���ɉ�
		pVtx[i].pos = pVtx[i - 2].pos;
		pVtx[i].col = pVtx[i - 2].col;

	}

	//-------------------------------
	// �F�̕ύX
	//-------------------------------
	for (int i = 0; i < m_nNumVtx; i++)
	{
		D3DXCOLOR col = pVtx[i].col;
		col.a -= 0.005f;
		pVtx[i].col = col;
	}

	//--------------------------------------
	// �󂢂�0��1�ɋO�Ղ̐V�������W����
	//--------------------------------------
	//�e���f���̌��_����I�t�Z�b�g���ړ��������W����
	D3DXVec3TransformCoord(&m_worldPos, &m_offsetPos, &m_pMtxParent);
	pVtx[1].pos = m_worldPos;	//���W�̐ݒ�
	pVtx[1].col = m_initCol;	//�F�̐ݒ�

	//�e���f���̌��_�̍��W����
	D3DXVec3TransformCoord(&m_worldPos, &D3DXVECTOR3(0.0f, -20.0f, 0.0f), &m_pMtxParent);
	pVtx[0].pos = m_worldPos;	//���W�̐ݒ�

	//�F�̐ݒ�
	{
		D3DXCOLOR newCol = m_initCol;
		newCol.a = 0.1f;
		pVtx[0].col = newCol;
	}

	if (m_nNumVtx < nMaxVtx - 2)
	{//���_�̐����ő�l�𒴂��Ȃ��Ȃ�
		m_nNumVtx += 2;	//���_�������Z
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//==========================
// �`��
//==========================
void COrbit::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//------------------------------------
	// �}�g���b�N�X
	//------------------------------------
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//------------------------------------
	// ���_
	//------------------------------------
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//���ʂ��猩����悤�ɂ���
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//Z�o�b�t�@�̃N���A
	//pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
						   0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
						   m_nNumVtx - 4);		//�`�悷��v���~�e�B�u��

	// Z�o�b�t�@�̗L�����ݒ�
	//pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	//���ʂ��猩���Ȃ�����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

//=======================================
// ����
// �����F����̍��W�A�}�g���b�N�X
//=======================================
COrbit* COrbit::Create(D3DXVECTOR3 offset, D3DXMATRIX mtx)
{
	COrbit* pOrbit = nullptr;

	//----------------------------------
	// �|���S���̐����Ə�����
	//----------------------------------
	pOrbit = new COrbit;	//����

	if (pOrbit != nullptr)
	{//NULL�`�F�b�N
		//�����̑��
		pOrbit->m_pMtxParent = mtx;	//�e�̃}�g���b�N�X

		//������
		pOrbit->Init(offset);
		pOrbit->SetObjType(OBJTYPE_MESHORBIT);
	}

	return pOrbit;
}

//==========================
// �F�̐ݒ�
// �����F�F
//==========================
void COrbit::SetColor(D3DXCOLOR colDest)
{
	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//-------------------------------
	// �F�̕ύX
	//-------------------------------
	pVtx[1].col = colDest;

	D3DXCOLOR newCol = colDest;
	newCol.a = 0.1f;

	pVtx[0].col = newCol;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}