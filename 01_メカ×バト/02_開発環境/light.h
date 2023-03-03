//===================================================
//
// ライトヘッダー
// Author : Sato Teruto
//
//===================================================
#ifndef _LIGHT_H_	//このマクロが定義されてなかったら
#define _LIGHT_H_	//2重インクルード防止のマクロ定義

//-------------------------------
// インクルード
//--------------------------------
#include <d3dx9.h>
#include "main.h"

//================================
// ライトクラスの定義
//================================
class CLight
{
public:
	CLight();	//コンストラクタ
	~CLight();	//デストラクタ

	//------------------
	// メンバ関数
	//------------------
	void Init(LPDIRECT3DDEVICE9 pDevice);
	void Uninit();
	void Update();

	//------------------
	// ゲッター
	//------------------
	D3DXVECTOR3 GetVecDir();	//ライト方向の取得

private:
	//------------------
	// 定数
	//------------------
	static const int nMaxLight = 3;	//ライトの最大数

	//------------------
	// メンバ変数
	//------------------
	D3DLIGHT9 m_Light[nMaxLight];
	D3DXVECTOR3 m_vecDir;	//ライト方向のベクトル
};

#endif