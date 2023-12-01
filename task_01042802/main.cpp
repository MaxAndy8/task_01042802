#include <iostream>
#include <memory>
#include <vector>

class ShopItem // �����
{
private:
	int m_id;
	std::string m_name;
	double m_price;

public:
	ShopItem(int id, const std::string& name, double price) :
		m_id(id), m_name(name), m_price(price)
	{
	}

	// ������ �������
	int getId() const { return m_id; }
	std::string getName() const { return m_name; }
	double getPrice() const { return m_price; }

	void setId(int id) { m_id = id; }
	void setName(const std::string& name) { m_name = name; }
	void setPrice(double price) { m_price = price; }
};

class ShopOrder // ����������
{
private:
	struct Item
	{
		std::shared_ptr<ShopItem> m_shopItem;
		double m_price;
		int m_quantity;

		Item(std::shared_ptr<ShopItem>& shopItem, double price, int quantity)
			: m_shopItem(shopItem), m_price(price), m_quantity(quantity)
		{
		}
	};

	int number;
	std::vector<Item> m_items;

public:
	ShopOrder() {
		static int num = 0;
		num++;
		number = num;
	}

	// ��������� ������ �� ����������
	void addItem(std::shared_ptr<ShopItem> shopItem, double price, int quantity)
	{
		m_items.emplace_back(shopItem, price, quantity);
	}

	// ��������� �������� ������� �� ����������
	double getTotalCost() const
	{
		double totalCost = 0.0;
		for (const auto& item : m_items)
		{
			totalCost += item.m_price * item.m_quantity;
		}
		return totalCost;
	}

	// ��������� ���������� �� �����
	void displayOrder() const
	{
		std::cout << "���������� " << number << std::endl;
		std::cout << "�����:" << std::endl;
		for (const auto& item : m_items)
		{
			std::cout << "ID: " << item.m_shopItem->getId()
				<< ", �����: " << item.m_shopItem->getName()
				<< ", ֳ��: $" << item.m_price
				<< ", ʳ������: " << item.m_quantity << std::endl;
		}
		std::cout << "�������� �������: $" << getTotalCost() << "\n";
	}
};

int main()
{
	system("chcp 1251>nul");

	// ��������� ��'���� ShopItem
	std::shared_ptr<ShopItem> item1 = std::make_shared<ShopItem>(1, "����� ������ RZTK Cobra �����-������", 199.99);
	std::shared_ptr<ShopItem> item2 = std::make_shared<ShopItem>(2, "���� Logitech G102 Lightsync USB Black", 20.49);
	std::shared_ptr<ShopItem> item3 = std::make_shared<ShopItem>(3, "³�������� Asus PCI-Ex GeForce GTX 1650 TUF", 155.75);

	// ��������� ��'���� ShopOrder � ��������� ������ �� ����������
	ShopOrder order1;
	order1.addItem(item1, 10.99, 2);
	order1.addItem(item2, 20.49, 1);
	order1.addItem(item3, 15.75, 3);

	ShopOrder order2;
	order2.addItem(item1, 10.99, 2);
	order2.addItem(item3, 15.75, 3);

	ShopOrder order3;
	order3.addItem(item1, 10.99, 2);
	order3.addItem(item2, 20.49, 177);
	order3.addItem(item3, 15.75, 355);

	// ��������� ���������� �� �����
	order1.displayOrder();
	std::cout << std::endl << std::endl;
	order2.displayOrder();
	std::cout << std::endl << std::endl;
	order3.displayOrder();

	return 0;
}
