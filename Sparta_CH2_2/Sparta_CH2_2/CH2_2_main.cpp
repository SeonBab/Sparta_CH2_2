#include <iostream>
#include <cstdlib>
#include <ctime>

// CH2 OOP Summary 2�� �ʼ� �� �������� ����

class Animal
{
public:
	virtual void makeSound() const = 0;
};

class Dog : public Animal
{
	virtual void makeSound() const override
	{
		std::cout << "�� : Woof" << std::endl;
	}
};

class Cat : public Animal
{
	virtual void makeSound() const override
	{
		std::cout << "����� : Meow" << std::endl;
	}
};

class Cow : public Animal
{
	virtual void makeSound() const override
	{
		std::cout << "�� : Moo" << std::endl;
	}
};

class Zoo
{
private:
	Animal** animals; // ���� ��ü�� �����ϴ� ������ �迭
	int animalCount = 0;
	int arraysize = 0;

public:

	int getAnimalCount() { return animalCount; }
	// ������ �������� �߰��ϴ� �Լ�
	// - Animal ��ü�� �����͸� �޾� ������ �迭�� �����մϴ�.
	// - ���� �����̶� ���� �� �߰��� �� �ֽ��ϴ�.
	// - �Է� �Ű�����: Animal* (�߰��� ���� ��ü)
	// - ��ȯ��: ����
	void addAnimal(Animal* animal)
	{
		if (animalCount == arraysize)
		{
			(arraysize == 0) ? arraysize = 1 : arraysize *= 2;
			Animal** newAnimals = new Animal * [arraysize];

			for (int i = 0; i < animalCount; ++i)
			{
				newAnimals[i] = animals[i];
			}

			delete[] animals;
			animals = newAnimals;
		}

		animals[animalCount++] = animal;
	}

	// �������� �ִ� ��� ������ �ൿ�� �����ϴ� �Լ�
	// - ��� ���� ��ü�� ���� ���������� �Ҹ��� ���� �����̴� ������ �����մϴ�.
	// - �Է� �Ű�����: ����
	// - ��ȯ��: ����
	void performActions()
	{
		for (int i = 0; i < animalCount; ++i)
		{
			animals[i]->makeSound();
		}
	}

	// Zoo �Ҹ���
	// - Zoo ��ü�� �Ҹ�� ��, ���� ���Ϳ� ����� ��� ���� ��ü�� �޸𸮸� �����մϴ�.
	// - �޸� ������ �����ϱ� ���� ���� �Ҵ�� Animal ��ü�� `delete` �մϴ�.
	// - �Է� �Ű�����: ����
	// - ��ȯ��: ����
	~Zoo()
	{
		for (int i = 0; i < animalCount; ++i)
		{
			delete animals[i];
		}

		delete[] animals;
	}
};

// ���� ������ �����ϴ� �Լ�
// - 0, 1, 2 �� �ϳ��� ������ �����Ͽ� ���� Dog, Cat, Cow ��ü �� �ϳ��� �������� �����մϴ�.
// - ������ ��ü�� Animal Ÿ���� �����ͷ� ��ȯ�˴ϴ�.
// - �Է� �Ű�����: ����
// - ��ȯ��: Animal* (������ ���� ��ü�� ������)
Animal* createRandomAnimal()
{
	Animal* makeAnimal = nullptr;

	int curRand = rand() % 3;

	switch (curRand)
	{
	case 0:
		makeAnimal = new Dog;
		std::cout << "�� 1������ �߰��ƽ��ϴ�." << std::endl;
		break;
	case 1:
		makeAnimal = new Cat;
		std::cout << "����� 1������ �߰��ƽ��ϴ�." << std::endl;
		break;
	case 2:
		makeAnimal = new Cow;
		std::cout << "�� 1������ �߰��ƽ��ϴ�." << std::endl;
		break;
	default:
		break;
	}

	return makeAnimal;
}

int main()
{
	// �ʼ�
	Dog dog1;
	Cat cat1;
	Cow cow1;

	Animal* animals[3]{ &dog1, &cat1, &cow1 };

	for (int i = 0; i < 3; ++i)
	{
		animals[i]->makeSound();
	}

	// ����
	srand(time(0));

	Zoo Zoo1;

	bool bInputLoop = true;
	while (true == bInputLoop)
	{
		int inputValue = 0;
		std::cout << "������ �߰��Ͻ÷��� 1�� �Է����ּ���" << std::endl;
		std::cout << "���� " << Zoo1.getAnimalCount() << " ������ �߰��ƽ��ϴ�." << std::endl;
		std::cout << "���̻� �߰����� ������ �ϽŴٸ� �ٸ� ���� �Է����ּ���" << std::endl;

		std::cin >> inputValue;

		if (1 != inputValue)
		{
			bInputLoop = false;
			continue;
		}

		Zoo1.addAnimal(createRandomAnimal());
	}

	Zoo1.performActions();
}