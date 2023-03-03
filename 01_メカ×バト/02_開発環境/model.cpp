//===================================================
//
// ���f���̏���
// Author:Teruto Sato
//
//===================================================

//------------------------
// �C���N���[�h
//------------------------
#include "model.h"
#include "application.h"
#include "renderer.h"
#include "light.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "texture.h"
#include "line.h"
#include "debug_proc.h"

//========================
// �R���X�g���N�^
//========================
CModel::CModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_initPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�̏����l
	m_initRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̏����l
	m_pModel = nullptr;
	
	for (int i = 0; i < nMaxLine; i++)
	{
		if (m_pLine[i])
		{
			m_pLine[i] = nullptr;
		}
	}
}

//========================
// �f�X�g���N�^
//========================
CModel::~CModel()
{

}

//========================
// ������
//========================
HRESULT CModel::Init(D3DXVECTOR3 pos)
{
	//�����l�̐ݒ�
	m_pos = pos;	//�ʒu

	//���f���̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//-----------------------
	// �f�o�C�X�̎擾
	//-----------------------
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//-----------------------
	// X�t�@�C���̓ǂݍ���
	//-----------------------
	D3DXLoadMeshFromX(m_modelName,
					   D3DXMESH_SYSTEMMEM,
					   pDevice,
					   nullptr,
					   &m_pBuffMat,
					   nullptr,
					   &m_nNumMat,
					   &m_pMesh);

	return S_OK;
}

//========================
// �I��
//========================
void CModel::Uninit()
{
	//-----------------------
	// ���b�V���̔j��
	//-----------------------
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	//-----------------------
	// �}�e���A���̔j��
	//-----------------------
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}
}

//========================
// �X�V
//========================
void CModel::Update()
{
}

//========================
// �`��
//========================
void CModel::Draw(D3DMATRIX* mtxPlayer)
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���f���̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//---------------------------------
	// ���f���̌����𔽉f
	//---------------------------------
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//---------------------------------
	// ���f���̈ʒu�𔽉f
	//---------------------------------
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//---------------------------------
	// �e���f���̐ݒ�
	//---------------------------------
	if (m_pModel != nullptr)
	{//�e���f����null����Ȃ��Ȃ�
		//�e���f���̏���ݒ�
		m_mtxParent = m_pModel->GetmtxWorld();

		//�e�̃}�g���b�N�X�Ƃ̊|���Z
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &m_mtxParent);
	}
	else
	{
		//�e�̃}�g���b�N�X�Ƃ̊|���Z
		D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, (const D3DXMATRIX*)mtxPlayer);
	}

	//�e�̕`��
	DrawShadow();

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//---------------------------------
	// �L�����N�^�[�̕`��
	//---------------------------------
	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�v���C���[�p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ێ����Ă���}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//========================
// ����
//========================
CModel* CModel::Create(LPCTSTR text, CModel* model, D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{//���f���̃p�X , �e���f�����猩���ʒu , �e���f�����猩������
	CModel *pModel = nullptr;

	//----------------------------------
	// �����Ə�����
	//----------------------------------
	pModel = new CModel;	//����

	if (pModel != nullptr)
	{//NULL�`�F�b�N
		//�����o�ϐ��ɑ��
		pModel->m_modelName = text;
		pModel->m_pModel = model;
		pModel->m_rot = rot;
		pModel->m_initPos = pos;	//�ʒu�̏����l
		pModel->m_initRot = rot;	//�����̏����l

		//������
		pModel->Init(pos);
	}

	return pModel;
}

//========================
// �e�̕`��
//========================
void CModel::DrawShadow()
{
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	D3DMATERIAL9 matDef;	//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;		//�}�e���A���f�[�^�ւ̃|�C���^

	D3DXMATRIX	mtxShadow;	//�e�̃}�g���b�N�X
	D3DXPLANE	planeField;	//���ʂ�\���ϐ�
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	//�V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	//���C�g�����̎擾
	{
		D3DXVECTOR3 vecDir(CApplication::GetLight()->GetVecDir());
		vecLight = D3DXVECTOR4(-vecDir, 0.0f);	//���C�g�̋t������ݒ�
	}

	pos = D3DXVECTOR3(0.0f, 5.0f, 0.0f);
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//�@���ƕ��ʂ�1�_���畽�ʂ��쐬
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	//���C�g�ƕ��ʂ���e�s����쐬
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	//���[���h�}�g���b�N�X���v�Z
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//----------------------------
	// �}�e���A���̐F��ۑ�
	//----------------------------
	D3DXCOLOR col[32];
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐F��ۑ�
		col[nCntMat] = pMat[nCntMat].MatD3D.Diffuse;
	}

	//----------------------------
	// �L�����N�^�[�̕`��
	//----------------------------
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐F�̐ݒ�
		pMat[nCntMat].MatD3D.Diffuse = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//�F
		pMat[nCntMat].MatD3D.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	//����

		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�v���C���[�p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//----------------------------
	// �L�����N�^�[�̐F��߂�
	//----------------------------
	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐F�̐ݒ�
		pMat[nCntMat].MatD3D.Diffuse = col[nCntMat];
	}

	//�ێ����Ă���}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}