//
// Created by Jasiek on 17.05.2019.
//

#ifndef IAD_MLP_KLASYFIKACJA_H
#define IAD_MLP_KLASYFIKACJA_H
#pragma once
#include "ReadData.h"
#include "Net.h"
#include "Teach.h"
#include "gnuplot_i.hpp"
#include <vector>
#include <fstream>
#include <string>

void Klasyfikacja()
{
	tuple<vector<vector<double>>, vector<vector<double>>> Data1 = ReadData(1, 1, "C://Users//Jasiek//Desktop//IAD_MLP//Dane//data.txt");
	tuple<vector<vector<double>>, vector<vector<double>>> Data2 = ReadData(1, 1, "C://Users//Jasiek//Desktop//IAD_MLP//Dane//datakrotka.txt");
	tuple<vector<vector<double>>, vector<vector<double>>> DataT = ReadData(1, 1, "C://Users//Jasiek//Desktop//IAD_MLP//Dane//datatestowa.txt");
#pragma region na 3
	//


	//Net network1({ 4, 1, 4 });
	//Teach nauka1(network1);
	//Net network2({ 4, 2, 4 });
	//Teach nauka2(network2);
	//Net network3({ 4, 3, 4 });
	//Teach nauka3(network3);

	//nauka1.FeedData(std::get<0>(Data), std::get<1>(Data));
	//nauka2.FeedData(std::get<0>(Data), std::get<1>(Data));
	//nauka3.FeedData(std::get<0>(Data), std::get<1>(Data));



	//nauka1.Execute();
	//nauka2.Execute();
	//nauka3.Execute();
	//std::cout << "done!" << std::endl;


	//network1.FeedData({ 1, 0, 0, 0 });
	//std::cout << nauka1.GetIterationsCount() << std::endl;
	//std::cout << network1.toString();


	//network2.FeedData({ 1, 0, 0, 0 });
	//std::cout << nauka2.GetIterationsCount() << std::endl;
	//std::cout << network2.toString();

	//network3.FeedData({ 1, 0, 0, 0 });
	//std::cout << nauka3.GetIterationsCount() << std::endl;
	//std::cout << network3.toString();


	//std::vector<int> epoki1, epoki2, epoki3;
	//for (int i = 0; i < nauka1.GetIterationsCount(); i++)
	//{
	//	epoki1.push_back(i);
	//}
	//for (int i = 0; i < nauka2.GetIterationsCount(); i++)
	//{
	//	epoki2.push_back(i);
	//}
	//for (int i = 0; i < nauka3.GetIterationsCount(); i++)
	//{
	//	epoki3.push_back(i);
	//}
	//std::vector<double> MSE1, MSE2, MSE3;
	//MSE1 = nauka1.allerrors();
	//MSE2 = nauka2.allerrors();
	//MSE3 = nauka3.allerrors();

	////std::fstream plik;
	////plik.open("wyniki.txt", std::ios::out);
	////if (plik.good()) {
	////	std::cout << "DONE?" << std::endl;;
	////	for (double i = 0.1; i < 1; i += 0.1) {
	////		Net* tempnet = new Net({ 4, 2, 4 });
	////		Teach* tempteach = new Teach(*tempnet);
	////		tempnet->UpdateEta(i);
	////		tempteach->FeedData(std::get<0>(Data), std::get<1>(Data));
	////		tempteach->Execute();
	////		std::vector<int>epoki;
	////		std::vector<double> MSE;
	////		MSE = tempteach->allerrors();
	////		for (int j = 0; j < tempteach->GetIterationsCount(); j++)
	////		{
	////			epoki.push_back(j);
	////			plik << j << " " << i << " " << MSE[j] << std::endl;
	////		}
	////		delete tempnet;
	////		delete tempteach;
	////	}
	////}
	////	plik.close();
	//std::vector<std::vector<double>> bledy;

	//int z = 0;
	//	for (double i = 0.1; i < 1; i += 0.2) {
	//			Net* tempnet = new Net({ 4, 1, 4 });
	//			Teach* tempteach = new Teach(*tempnet);
	//			tempnet->UpdateAlfa(i);
	//			tempteach->FeedData(std::get<0>(Data), std::get<1>(Data));
	//			tempteach->Execute();
	//			bledy.push_back(tempteach->allerrors());
	//			z++;
	//			delete tempnet;
	//			delete tempteach;
	//		}



#pragma endregion
		std::vector<std::vector<double>> bledy;
		//for (unsigned int u =6; u < 7; u++) {
				for(int i = 0; i<3; i++){
				Net* tempnet = new Net({ 1, 7, 1 });
				Teach* tempteach = new Teach(*tempnet);
				tempteach->NumberOfIterations = 1000 + 1000 * i;
				tempteach->FeedData(std::get<0>(Data1), std::get<1>(Data1));
				tempteach->Execute();
				/*bledy.push_back(tempteach->allerrors());*/
				std::vector<double> tempvec;
				for (int i = 0; i < std::get<0>(DataT).size(); i++)
				{
					tempnet->FeedData(std::get<0>(DataT)[i], std::get<1>(DataT)[i]);
					tempvec.push_back(tempnet->GetError());
				}
				bledy.push_back(tempvec);

				delete tempnet;
				delete tempteach;
			}


		std::vector<int> epoki;
		for(int i=0; i<bledy[0].size(); i++)
		{
			epoki.push_back(i);
		}
	Gnuplot wykres;
	wykres.set_grid();
	wykres.set_style("lines");
	wykres.set_title("Błędy dla zadanych warstości testowych");
	wykres.set_xlabel("Wartości testowe");
	wykres.set_ylabel("Średni błąd kwadratowy");
	//wykres.set_yrange(0, 10);

	for(int u = 0; u < bledy.size(); u++)
	{
		std::string ile = "Ilosc epok nauki: " + std::to_string(1000 + 1000*u);
		wykres.plot_xy(epoki, bledy[u], ile);
	}




	system("pause");
}


#endif //IAD_MLP_KLASYFIKACJA_H
