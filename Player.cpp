﻿#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, uint32_t textuerHandle) {
	// NULLポインタチェック
	assert(model);
	model_ = model;
	texturehandle_ = textuerHandle;

	worldTransform_.Initialize();
}

void Player::Update() {
	// 　行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, texturehandle_);
}