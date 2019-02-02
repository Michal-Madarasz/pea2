#include "pch.h"
#include "Menu.h"


Menu::Menu()
{
	sa = new SA();
	tabu = new Tabu();
	choice = -1;
	cities = 0;
	measurement_error = 0.0;
	worst = 0.0;
	avg_distance = 0.0;
	avg_time = 0.0;
}


Menu::~Menu()
{
}

void Menu::showMenu() {
	system("cls");
	std::cout << "1. Wczytaj dane\n";
	std::cout << "2. Wprowadz kryterium zatrzymania\n";
	std::cout << "3. Symulowane wyrza¿anie\n";
	std::cout << "4. Tabu Search\n";
	std::cout << "5. Wyjscie\n";
}

void Menu::showSubmenu() {
	system("cls");
	std::cout << "Pliki testowe: br17, ftv70, ftv170\n";
	std::cout << "Wybierz plik (bez rozszerzenia): ";
}

bool Menu::wyborOpcji() {
	std::cout << "Wybierz: ";
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		showSubmenu();
		std::cin >> filename;
		if(readFile(filename, matrix, cities, optimum))
			readed = true;
		system("pause");
		break;
	case 2:
		system("cls");
		std::cout << "Podaj czas dzialania algorytmu (w sekundach): \n";
		std::cin >> runtime;
		break;
	case 3:
		system("cls");
		if (readed) {
			std::cout << "Rozpoczeto";
			int result = INT_MAX;
			sa->setOptimum(optimum);

			measurement = sa->sa(matrix, cities, result, runtime);

			avg_time += measurement;
			avg_distance += result;

			if (result < max_result)
			{
				max_result = result;
			}

			double x = max_result - optimum;

			measurement_error = (x * 100) / optimum;
			std::cout << "Najkrotsza znana odleglosc: ";
			std::cout << optimum << "\n";
			std::cout << "Najmniejszy obliczony koszt: ";
			std::cout << max_result << "\n";
			std::cout << "Czas wykonania: ";
			std::cout << avg_time << "\n";
			std::cout << "Blad: ";
			std::cout << measurement_error << "%" << "\n";

			std::cout << "\n" << "\n";
			max_result = DBL_MAX;

			std::cout << "\n" << "\n" << "Zakonczono obliczenia." << "\n" << "\n";

			std::cout << "\n";
		}
		else {
			std::cout << "Brak danych";
		}
		system("pause");
		break;
	case 4:
		system("cls");
		if (readed) {
			int result1 = INT_MAX;
			char sign;
			tabu->setOptimum(optimum);

			std::cout << "Czy zastosowac dywersyfikacje ? [t/n]: ";
			std::cin >> sign;

			if (sign == 't') {
				diver = true;
			}
			else
				diver = false;

			measurement1 = tabu->ts(runtime, matrix, cities, result1, diver);

			avg_time += measurement1;
			avg_distance += result1;
			if (result1 < max_result)
			{
				max_result = result1;
			}

			avg_time /= 1;
			avg_distance /= 1;
			double x = avg_distance - optimum;
			std::cout << "Wynik: \n";
			measurement_error = (x * 100) / optimum;
			std::cout << "Najkrotsza znana odleglosc: ";
			std::cout << optimum << std::endl;
			std::cout << "Sredni obliczony koszt: ";
			std::cout << avg_distance << std::endl;
			std::cout << "Najmniejszy obliczony koszt: ";
			std::cout << result1 << std::endl;
			std::cout << "Sredni czas: ";
			std::cout << avg_time << std::endl;
			std::cout << "Blad: ";
			std::cout << measurement_error << "%" << std::endl;

			std::cout << std::endl << std::endl;
			avg_time = 0;
			avg_distance = 0;
		}
		else {
			std::cout << "Brak danych";
		}
		system("pause");
		break;
	case 5:
		return true;
		break;
	default:
		break;
	}
	return false;
}

bool Menu::readFile(std::string filename, double **&matrix, int &cities, int &optimum) {
	std::fstream file;
	file.open((filename + ".txt").c_str(), std::ios::in);

	if (file.good()) {

		file >> cities >> optimum;

		matrix = new double *[cities];

		for (int i = 0; i < cities; ++i) {
			*(matrix + i) = new double[cities]; // number of columns
			for (int j = 0; j < cities; ++j) {

				file >> matrix[i][j];

			}

		}

		//displaying matrix

		/*for (int i = 0; i < cities; i++){
			for (int j = 0; j < cities; j++){
				std::cout << std::setw(2) << matrix[i][j] << " ";
			}
			std::cout << "\n";
		}*/

		std::cout << "Plik odczytany poprawnie." << std::endl;
		std::cout << std::endl;

		file.close();
		return true;

	}
	else {
		std::cout << "Blad. " << std::endl;
		system("pause");
		file.close();
		return false;
	}
}
