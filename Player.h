#pragma once

#include "Input.h"
#include "MathFunction.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	//void Initialize(std::vector<Model*> model);
	void Initialize(Model* modeBody, Model* modelHead, Model* modelL_arm, Model* modelR_arm);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="ViewProjection">ビュープロジェクション(参照渡し)</param>
	void Draw(ViewProjection& viewProjection);


	/// <summary>
	/// Get
	/// </summary>
	WorldTransform& GetWorldTransform() { return worldTransformBase_; }

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
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;
	// モデル
	//Model* model_ = nullptr;
	//std::vector<Model*> model_;
	Model* modelBody_ = nullptr;
	Model* modelHead_ = nullptr;
	Model* modelL_arm_ = nullptr;
	Model* modelR_arm_ = nullptr;
	// テクスチャハンドル
	//uint32_t texturehandle_ = 0u;
	// キャラクター入力
	Input* input_ = nullptr;
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;
	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

};