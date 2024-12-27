#include <iostream>
#include <cstdlib>
#include <ctime>

// CH2 OOP Summary 2번 필수 및 도전과제 제출

class Animal
{
public:
	virtual void makeSound() const = 0;
};

class Dog : public Animal
{
	virtual void makeSound() const override
	{
		std::cout << "개 : Woof" << std::endl;
	}
};

class Cat : public Animal
{
	virtual void makeSound() const override
	{
		std::cout << "고양이 : Meow" << std::endl;
	}
};

class Cow : public Animal
{
	virtual void makeSound() const override
	{
		std::cout << "소 : Moo" << std::endl;
	}
};

class Zoo
{
private:
	Animal** animals; // 동물 객체를 저장하는 포인터 배열
	int animalCount = 0;
	int arraysize = 0;

public:

	int getAnimalCount() { return animalCount; }
	// 동물을 동물원에 추가하는 함수
	// - Animal 객체의 포인터를 받아 포인터 배열에 저장합니다.
	// - 같은 동물이라도 여러 번 추가될 수 있습니다.
	// - 입력 매개변수: Animal* (추가할 동물 객체)
	// - 반환값: 없음
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

	// 동물원에 있는 모든 동물의 행동을 수행하는 함수
	// - 모든 동물 객체에 대해 순차적으로 소리를 내고 움직이는 동작을 실행합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	void performActions()
	{
		for (int i = 0; i < animalCount; ++i)
		{
			animals[i]->makeSound();
		}
	}

	// Zoo 소멸자
	// - Zoo 객체가 소멸될 때, 동물 벡터에 저장된 모든 동물 객체의 메모리를 해제합니다.
	// - 메모리 누수를 방지하기 위해 동적 할당된 Animal 객체를 `delete` 합니다.
	// - 입력 매개변수: 없음
	// - 반환값: 없음
	~Zoo()
	{
		for (int i = 0; i < animalCount; ++i)
		{
			delete animals[i];
		}

		delete[] animals;
	}
};

// 랜덤 동물을 생성하는 함수
// - 0, 1, 2 중 하나의 난수를 생성하여 각각 Dog, Cat, Cow 객체 중 하나를 동적으로 생성합니다.
// - 생성된 객체는 Animal 타입의 포인터로 반환됩니다.
// - 입력 매개변수: 없음
// - 반환값: Animal* (생성된 동물 객체의 포인터)
Animal* createRandomAnimal()
{
	Animal* makeAnimal = nullptr;

	int curRand = rand() % 3;

	switch (curRand)
	{
	case 0:
		makeAnimal = new Dog;
		std::cout << "개 1마리가 추가됐습니다." << std::endl;
		break;
	case 1:
		makeAnimal = new Cat;
		std::cout << "고양이 1마리가 추가됐습니다." << std::endl;
		break;
	case 2:
		makeAnimal = new Cow;
		std::cout << "소 1마리가 추가됐습니다." << std::endl;
		break;
	default:
		break;
	}

	return makeAnimal;
}

int main()
{
	// 필수
	Dog dog1;
	Cat cat1;
	Cow cow1;

	Animal* animals[3]{ &dog1, &cat1, &cow1 };

	for (int i = 0; i < 3; ++i)
	{
		animals[i]->makeSound();
	}

	// 도전
	srand(time(0));

	Zoo Zoo1;

	bool bInputLoop = true;
	while (true == bInputLoop)
	{
		int inputValue = 0;
		std::cout << "동물을 추가하시려면 1을 입력해주세요" << std::endl;
		std::cout << "현재 " << Zoo1.getAnimalCount() << " 마리가 추가됐습니다." << std::endl;
		std::cout << "더이상 추가하지 않으려 하신다면 다른 값을 입력해주세요" << std::endl;

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