#pragma once

#include "HotDrinks.h"

/**
 * The Abstract Factory interface declares a set of
 * methods that return different abstract products. 
 */
class IHotDrinkFactory {
public:
	virtual ~IHotDrinkFactory() = default;
	virtual std::unique_ptr<IHotDrink> CreateProduct() = 0;
};

class TeaFactory : public IHotDrinkFactory {
	std::unique_ptr<IHotDrink> CreateProduct() override {
		return std::make_unique<Tea>();
	}
};

class CoffeeFactory : public IHotDrinkFactory {
	std::unique_ptr<IHotDrink> CreateProduct() override {
		return std::make_unique<Coffee>();
	}
};

class ChocolateFactory : public IHotDrinkFactory {
	std::unique_ptr<IHotDrink> CreateProduct() override {
		return std::make_unique<Chocolate>();
	}
};
