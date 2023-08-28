#include "Ground.h"
#include <assert.h>

void Ground::Initialize(Model* model) {
	assert(model);

	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {100.0f, 100.0f, 100.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
}

void Ground::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//// ワールドトランスフォームの更新
	worldTransform_.UpdateMatrix();
}

void Ground::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }