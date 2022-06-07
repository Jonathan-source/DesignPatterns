/*
	In this demo, I have applied the abstract factory design pattern to encapsulate the logic for creating
	various hot beverages ( chocolate, coffee, tea ), which are all prepared differently, and delegated their
	creation to respective factory. A super-factory of factories let us produce families of related objects 
	without specifying their concrete classes, and keeping initialization in one place.
	
	Updated: 2022-06-05
	Author: Jonathan Helsing [github.com/Jonathan-source]
*/

#include "HotDrinkFactories.h"

/**
 * Concrete Factories produce a family of products that belong to a single
 * variant. The factory guarantees that resulting products are compatible. Note
 * that signatures of the Concrete Factory's methods return an abstract product,
 * while inside the method a concrete product is instantiated.
 */
class DrinkFactory {
public:
	DrinkFactory() {
		m_factories["chocolate"] = std::make_unique<ChocolateFactory>();
		m_factories["coffee"] = std::make_unique<CoffeeFactory>();
		m_factories["tea"] = std::make_unique<TeaFactory>();
		
	}
	virtual ~DrinkFactory() = default;

	std::unique_ptr<IHotDrink> MakeDrink(const std::string& name) {
		auto drink = m_factories[name]->CreateProduct();
		drink->Prepare();
		std::cout << " Here you are..." << std::endl;
		return drink;
	}

private:
	typedef std::unordered_map<std::string, std::unique_ptr<IHotDrinkFactory>> FactoryMap;
	FactoryMap m_factories;
};


int main()
{
	DrinkFactory drinkFactory;
	auto drink = drinkFactory.MakeDrink("coffee");
	drink = drinkFactory.MakeDrink("tea");
	drink = drinkFactory.MakeDrink("chocolate");

	return 0;
}
