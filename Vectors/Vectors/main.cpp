
#include<iostream>
#include<fstream>
#include "Vector.h"
#include <string>
#include "OutputState.h"
#include <math.h>



std::istream& operator>>(std::istream& file, OutputState& temp);
std::ostream& operator<<(std::ostream& file, OutputState& temp);
void error(std::string str);
Vector simpleOperation(char symbol, Vector first, Vector second);
float hardOperation(char symbol, Vector* first, Vector* second);

void inputError(std::istream& is);
void alloc(OutputState*& arr,int& sz);

static int arraySize = 0;// переменная позволяющая сделать цикл не выходящий


int main() {
	int sz = 2;
	setlocale(LC_ALL, "Russian");
	std::string inputFileName, outputFileName;
	std::cout << "Введите абсолютный или относительный путь к входящему файлу:\n";
	std::cin >> inputFileName;
	std::ifstream input(inputFileName);
	OutputState* array = new OutputState[sz];
	if (!input.is_open()) {
		system("cls");
		error("Ошибка открытия входящего файла.\n");
		system("pause");
		return 0;
	}
	std::cout << "Введите абсолютный или относительный путь к исходящему файлу:\n";
	std::cin >> outputFileName;
	std::ofstream output(outputFileName);
	std::string mark1;
	input >> mark1;
	if (mark1 != "operations") //Стандартный прирыв чтения из файла, при не соблюдении формата записи.
	{
		input.clear(std::ios_base::failbit);
		std::cout << "Ошибка, неверный формат входящего файла.\n";
		return 0;
	}
	
	
	int count = 0;
	for (OutputState tmp; input >> tmp;) {
		if (arraySize>sz) {
			alloc(array,sz);
		}
		array[count] = tmp;
		count++;
		//array = new OutputState[6];
	}
	for (int i = 0; i < arraySize; i++)//Использование переменной обусловленно тем, что размер массива заранее резервируется.
	{ 
		if (array[i].symbol == '+' || array[i].symbol == '-') {
			Vector tmp = simpleOperation(array[i].symbol, array[i].first, array[i].second);
			array[i].result = tmp;
		}
		else if(array[i].symbol == '|'){
			array[i].resul = hardOperation(array[i].symbol, &array[i].first, &array[i].first);
		}
		else {
			array[i].resul = hardOperation(array[i].symbol, &array[i].first, &array[i].second);
		}
	}
	for (int i = 0; i < arraySize; i++) {
		output << array[i];
	}
	std::cout << "Расчеты проведены успешно!";
	system("pause");
	return 0;

}
std::istream& operator>>(std::istream& file, OutputState& temp) {
	constexpr int sz= 3;
	char mark2, mark3, mark4;
	float array[sz],array2[sz],tmp; // array[3] - x, y, z
	file >> mark2;
	if (mark2 == '|') {
		int counter = 0;
		while (file >> tmp && file >> mark3) {//цикл считывания чисел до знака | формат вектора - |x,y,z|;
			if (mark3 == '|') {
				array[counter] = tmp;
				break;
			}
			array[counter] = tmp; // делаем наполнение 
			counter++;
		}
		file >> mark4;
		if (mark4 != ';') {
			inputError(file);
			return file;
		}
		temp.first.setX(array[0]);
		temp.first.setY(array[1]);
		temp.first.setZ(array[2]);
		temp.symbol = '|';
		arraySize++;
		return file;
	}
	else if (mark2 != '{') {
		file.clear(std::ios_base::failbit);
		return file;
	}
	int counter = 0;
	while (file >> tmp && file >> mark3) {//цикл считывания чисел до знака | формат вектора - {x,y,z}
		if (mark3 == '}') {
			array[counter] = tmp;
			break;
		}
		array[counter] = tmp; // делаем наполнение 
		counter++;
	}
	file >> mark4;
	file >> mark2;
	
	if (mark4 == '*' && mark2 == '{' ||mark4 == '+' && mark2 == '{' ||mark4 =='-' && mark2 == '{' || mark4 == 'x'&& mark2 =='{' || mark4 == '<' && mark2 == '{'){//Если фигурная скобка - Скалярное умножение.
		counter = 0;
		mark3 = ' ';// обнуляем значение нашего флажка.
		while (file >> tmp && file >> mark3) {//цикл считывания чисел до знака | формат вектора - {x,y,z}
			if (mark3 == '}') {
				array2[counter] = tmp;
				break;
			}
			array2[counter] = tmp; // делаем наполнение 
			counter++;
		}
		
		temp.first.setX(array[0]);
		temp.first.setY(array[1]);
		temp.first.setZ(array[2]);
		temp.second.setX(array2[0]);
		temp.second.setY(array2[1]);
		temp.second.setZ(array2[2]);
		temp.symbol = mark4;
	}
	else {
		inputError(file);
		return file;
	}
	file >> mark4;
	if (mark4 != ';') {
		inputError(file);
		return file;
	}
	arraySize++;
	return file;
}
Vector simpleOperation(char symbol, Vector first, Vector second) {
	Vector tmp; // создаем пустышку для наполнения
	switch (symbol)
	{
	case '+':
		tmp.setX(first.getX() + second.getX());
		tmp.setY(first.getY() + second.getY());
		tmp.setZ(first.getZ() + second.getZ());
		break;
	case '-':
		tmp.setX(first.getX() - second.getX());
		tmp.setY(first.getY() - second.getY());
		tmp.setZ(first.getZ() - second.getZ());
		break;
	default:
		break;
	}
	return tmp;
}
void error(std::string str) {
	std::cout << str << std::endl;
}
void inputError(std::istream& is) {
	is.clear(std::ios_base::failbit);
	error("Ошибка, неверный формат входящего файла.\n");
}
void alloc(OutputState*& arr,int& sz) 
// Если в нашем динамическом массиве не будет хватать выделяемой память, эта функция ее зарезервирует без потери данных.
{
	OutputState* temp = new OutputState[sz*2]; //так как arraySize> sz то массив в arraySize-1 будет равен нашему начальному размеру
	for (int i = 0; i < sz; i++) 
		temp[i] = arr[i];
	
	sz = sz * 2;
	delete[]arr;
	arr = temp;
	
}
float hardOperation(char symbol, Vector* first, Vector* second) {
	float result=0;
	constexpr float P = 3.1415926535897;
	switch (symbol)
	{
	case'*':
		result = first->getX() * second->getX() + first->getY() * second->getY() + first->getZ() * second->getZ();
		break;
	case'x':
		result = hardOperation('|', first, first) * hardOperation('|', second, second) * sin(hardOperation('<', first, second));
		break;
	case'|':
		result = sqrt(first->getX()*first->getX()+first->getY()*first->getY()+first->getZ()*first->getZ());
		break;
	case'<': {
		float h = hardOperation('*', first, second) / (hardOperation('|', first, first) * hardOperation('|', second, second));//для того, что бы найти градус между двумя векторами, нужно взять арккосинус от отношения скалярного произведения на умножение двух длинн. 
		result = acos(h)*180/P;
	}
		break;
	default:
		break;
	}
	return result;
}
std::ostream& operator<<(std::ostream& file, OutputState& temp) {
	if (temp.symbol == '+' || temp.symbol == '-') {
		file << "{" << temp.first.getX() << "," << temp.first.getY() << "," << temp.first.getZ() << "}" << temp.symbol << "{" << temp.second.getX() << "," << temp.second.getY() << "," << temp.second.getZ() << "}=" << "{" << temp.result.getX() << "," << temp.result.getY() << "," << temp.result.getZ() << "};\n";
	}
	else if (temp.symbol == '*' || temp.symbol == 'x' || temp.symbol == '<') {
		file << "{" << temp.first.getX() << "," << temp.first.getY() << "," << temp.first.getZ() << "}" << temp.symbol << "{" << temp.second.getX() << "," << temp.second.getY() << "," << temp.second.getZ() << "}=" << temp.resul<<"\n";
	}
	else if (temp.symbol == '|') {
		file << "|" << temp.first.getX() << "," << temp.first.getY() << "," << temp.first.getZ() << '|=' << temp.resul;
	}
	return file;
}