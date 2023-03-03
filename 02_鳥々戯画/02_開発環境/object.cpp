//=====================================
//
// オブジェクトの処理
// Author : Sato Teruto
//
//=====================================

//--------------------
// インクルード
//--------------------
#include "object.h"
#include "object2D.h"

//------------------------
// 静的メンバ変数宣言
//------------------------
CObject *CObject::m_pObject[3][MAX_OBJECT] = {};

//================================
// コンストラクタ(イニシャライザ)
//================================
CObject::CObject(int nPriority)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[nPriority][i] == nullptr)
		{
			m_pObject[nPriority][i] = this;
			m_nID = i;
			m_ObjType = OBJTYPE_MAX;
			break;
		}
	}
}

//=============================
// デストラクタ
//=============================
CObject::~CObject()
{

}
//=============================
// 全て解放
//=============================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				//解放
				m_pObject[i][j]->Uninit();
			}
		}
	}
}

//=============================
// 全て更新
//=============================
void CObject::UpdateAll()
{
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Update();	//オブジェクトの更新
			}
		}
	}
}

//=============================
// 全て描画
//=============================
void CObject::DrawAll()
{
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		for (int j = 0; j < MAX_OBJECT; j++)
		{
			if (m_pObject[i][j] != nullptr)
			{
				m_pObject[i][j]->Draw();	//オブジェクトの描画
			}
		}
	}
}

//=============================
// 総数の取得
//=============================
int CObject::GetNumAll()
{
	return 0;
}

//=============================
// 解放する
//=============================
void CObject::Release()
{
	//NULLチェック
	for (int i = 0; i < MY_MAX_PRIORITY; i++)
	{
		if (m_pObject[i][m_nID] != nullptr)
		{
			int nID = m_nID;				//番号を保存
			delete m_pObject[i][nID];		//オブジェクトの解放
			m_pObject[i][nID] = nullptr;	//NULLにする]
			return;
		}
	}
}

//=============================
// オブジェクトの取得
//=============================
CObject *CObject::GETObject(int nPriority, int nCnt)
{
	return m_pObject[nPriority][nCnt];
}

//=============================
// オブジェクトの種類の設定
//=============================
void CObject::SetObjType(EObjType ObjType)
{
	m_ObjType = ObjType;
}

//=============================
// オブジェクトの種類の取得
//=============================
CObject::EObjType CObject::GetObjType()
{
	return m_ObjType;
}