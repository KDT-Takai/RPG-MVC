#pragma once
#include <iostream>
#include "Singleton.h"

// ü‚Ì•`‰æi‚½‚¾‚½‚¾Œ©‚â‚·‚­‚·‚é‚½‚ß
// ‰½‰ñ‚àü‚ğ‘‚­‚Ì‚¾‚é‚¢
class Text : public Singleton<Text> {
	friend class Singleton<Text>;
public:
	void Line() {
		std::cout << "-------------------------------------" << std::endl;
	}
};