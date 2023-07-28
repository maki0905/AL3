#pragma once

#include "Input.h"
#include "MathFunction.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"

#include <vector>

class Player : public BaseCharacter {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models">モデルデータ配列</param>
	void Initialize(const std::vector<Model*>& models) override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update() override;
	

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="ViewProjection">ビュープロジェクション(参照渡し)</param>
	void Draw(ViewProjection& viewProjection);


	/// <summary>
	/// Get
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTransform_; }

	/// <summary>
	/// Set
	/// </summary>
	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();
	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

private:
	// ワールド変換データ
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	
	// テクスチャハンドル
	//uint32_t texturehandle_ = 0u;
	// キャラクター入力
	Input* input_ = nullptr;
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

};