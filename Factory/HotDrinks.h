#pragma once

#include <iostream>
#include <memory>
#include <unordered_map>

/**
 * Each distinct product of a product family should have a base interface. 
 * All variants of the product must implement this interface.
 */
class IHotDrink {
public:
	virtual ~IHotDrink() = default;
	virtual void Prepare() = 0;
};

class Tea : public IHotDrink {
public:
	void Prepare() override {
		std::cout << "[Preparing a cup of tea]";
	}
};

class Coffee : public IHotDrink {
public:
	void Prepare() override {
		std::cout << "[Preparing a cup of coffee]";
	}
};

class Chocolate : public IHotDrink {
public:
	void Prepare() override {
		std::cout << "[Preparing a cup of hot chocolate]";
	}
};
