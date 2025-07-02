// Lab-03a.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include"SDS.h"
#include <cstring>
#include <string>
int main(int argc,char* argv[])
{
	generateArray();
	std::cout << "First 10 nums: " << std::endl;
	for (int i = 0; i < 10; ++i)
	{
		std::cout << data[i] << " ";
	}
	std::cout << std::endl;
	if (argc < 2) {
		std::cout << "Ne ykazana vyzyvaemaya function!" << std::endl;
		return 1;
	}
std::string functionName = argv[1];
int target = (argc > 2) ? std::stoi(argv[2]) : 0;
if (argc == 2) {
	std::cout << "Input num for search: ";
	std::cin >> target;
}
int result = -1;
if (functionName == "iterative") {
	result = iterativeBinarySearch(data, 1024, target);
}
else if (functionName == "recursive")
{
	result = recursiveBinarySearch(data, 0,1024, target);
}
else {
	std::cerr << "Uknown func: " << functionName << std::endl;
	return 1;
}
if (result == -1) {
	std::cout << functionName << ": Your num not found!" << std::endl;
}
else {
	std::cout << functionName << ": Num " << target << "find in pos " << result << "!" << std::endl;
}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
