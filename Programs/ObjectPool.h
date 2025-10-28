#pragma once
#include <iostream>
#include <vector>
#include <stack>

// 前方宣言
template <typename T>
class ObjectPool;

template <typename T>
class PoolHandle {
	// friend class 指定したクラスに対して、プライベートメンバーやプロテクテッドメンバーへのアクセス権を与える
	friend class ObjectPool<T>;
	explicit PoolHandle(T* obj, ObjectPool<T>* pool)
		: obj_(obj), pool_(pool) {
	}
public:
	PoolHandle() noexcept : obj_(nullptr), pool_(nullptr) {}
	// コピー禁止
	PoolHandle(const PoolHandle&) = delete;
	// ムーブ可能
	PoolHandle(PoolHandle&& other) noexcept
		: obj_(other.obj_), pool_(other.pool_) {
		other.obj_ = nullptr;
		other.pool_ = nullptr;
	}
	// デストラクタで自動返却
	~PoolHandle() {
		if (pool_ && obj_) {
			pool_->Release(obj_);
		}
	}

	// アクセス演算子
	T* operator->() { return obj_; }
	T& operator*() { return *obj_; }
private:
	T* obj_;
	ObjectPool<T>* pool_;
};

template <typename T>
class ObjectPool {
	friend class PoolHandle<T>;
public:
	explicit ObjectPool(size_t capacity) {
		objects_.reserve(capacity);
		for (size_t i = 0; i < capacity; ++i) {
			objects_.emplace_back(std::make_unique<T>());
			free_.push(objects_.back().get());
		}
	}
	// 取得
	PoolHandle<T> Acquire() {
		if (free_.empty()) throw std::runtime_error("empty");	// 空の場合
		T* obj = free_.top();
		free_.pop();
		return PoolHandle<T>(obj, this);
	}
private:
	void Release(T* obj) { free_.push(obj); }
	std::vector<std::unique_ptr<T>> objects_;
	std::stack<T*> free_;
};