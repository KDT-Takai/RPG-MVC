#pragma once
#include <iostream>
#include "Singleton.h"

class Text : public Singleton<Text> {
	friend class Singleton<Text>;
public:
	void Line() {
		std::cout << "-------------------------------------" << std::endl;
	}
};

