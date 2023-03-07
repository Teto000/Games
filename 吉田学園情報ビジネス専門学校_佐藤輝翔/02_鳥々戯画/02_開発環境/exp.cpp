//===================================
//
// 経験値の処理
// Author : Sato Teruto
//
//===================================

//------------------------
// インクルード
//------------------------
#include "exp.h"
#include "main.h"
#include "renderer.h"
#include "object2D.h"
#include "input_keybord.h"
#include "texture.h"

//===========================
// コンストラクタ
//===========================
CExp::CExp() : CObject2D()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//回転
	m_fWidth = 0.0f;	//幅
	m_fHeight = 0.0f;	//高さ
}

//===========================
// デストラクタ
//===========================
CExp::~CExp()
{

}

//===========================
// 初期化
//===========================
HRESULT CExp::Init(D3DXVECTOR3 pos)
{
	//位置の代入
	m_pos = pos;

	CObject2D::Init(m_pos);

	//頂点座標の設定(回転)
	CObject2D::SetVtxCIE_Rot(m_pos, m_rot.x, m_fWidth, m_fHeight);

	CObject2D::SetTexture(CTexture::TEXTURE_EXP);	//テクスチャの設定

	return S_OK;
}

//===========================
// 終了
//===========================
void CExp::Uninit()
{
	CObject2D::Uninit();
}

//===========================
// 更新
//===========================
void CExp::Update()
{
	CObject2D::Update();

	//頂点座標の設定(回転)
	CObject2D::SetVtxCIE_Rot(m_pos, m_rot.x, m_fWidth, m_fHeight);

	//----------------------------
	// レベルアップの処理
	//----------------------------
	if (m_rot.x <= D3DXToRadian(-360))
	{//ゲージが一周したら
		CObject *pObject;

		for (int i = 0; i < MY_MAX_PRIORITY; i++)
		{
			for (int j = 0; j < MAX_OBJECT; j++)
			{
				pObject = CObject::GETObject(i, j);

				if (pObject == nullptr)
				{
					continue;
				}

				//オブジェクトの種類の取得
				CObject::EObjType type = pObject->GetObjType();

				if (type == CObject::OBJTYPE_EXP)
				{
					//経験値ゲージの消去
					pObject->Uninit();
					//return;
				}
			}
		}

		//角度の正規化
		m_rot.x += D3DXToRadian(360);
	}
}

//===========================
// 描画
//===========================
void CExp::Draw()
{
	CObject2D::Draw();
}

//===========================
// 生成
//===========================
CExp *CExp::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fLength)
{
	CExp *pExp = nullptr;

	//----------------------------------
	// 経験値の生成と初期化
	//----------------------------------
	pExp = new CExp;	//生成

	if (pExp != nullptr)
	{//NULLチェック
		 //メンバ変数に代入
		pExp->m_rot = D3DXVECTOR3(D3DXToRadian(-rot.x),0.0f,0.0f);	//回転
		pExp->m_fWidth = fLength * 0.7f;
		pExp->m_fHeight = fLength / 2;	//高さ

		//初期化
		pExp->Init(pos);
		pExp->SetObjType(OBJTYPE_EXP);
	}

	return pExp;
}