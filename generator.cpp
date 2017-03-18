#define _USE_MATH_DEFINES
#include "Ponto.h" 
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip> 
#include <math.h>

using namespace std;

//separador dos pontos
std::string sep = ";";

//Recebe os pontos que formam um triangulo
void printTriangulo(ofstream& file, string sep, Ponto p1, Ponto p2, Ponto p3) {

	p1.printFile(file, sep);
	p2.printFile(file, sep);
	p3.printFile(file, sep);
}

//Para dividir os espaços da string de input
vector<string> splitString(string str) {
	string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream

	vector<string> tokens; // Create vector to hold our words

	while (ss >> buf)
		tokens.push_back(buf);

	return tokens;
}

	// Dado o lado do quadrado e o nome do ficheiro, esta função
	// escreve no ficheiro os vértices do quadrado
void plano(int lado, FILE *nomeFicheiro) {
	float ponto = ((float)lado / (float)2);

	ofstream outputFile(nomeFicheiro);
	Ponto p1 = Ponto(ponto, 0, ponto);
	Ponto p2 = Ponto(ponto, 0, -ponto);
	Ponto p3 = Ponto(-ponto, 0, -ponto);
	Ponto p4= Ponto(-ponto, 0, ponto);

	outputFile << "4" << endl;
	outputFile << "2" << endl;
	printTriangulo(outputFile, sep, p1, p2, p3);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p3, p4, p1);

}

void box(int comp_x, int alt_y, int lar_z, FILE *nomeFicheiro) {
	float ponto_x = ((float)comp_x / (float)2);
	float ponto_y = ((float)alt_y / (float)2);
	float ponto_z = ((float)lar_z / (float)2);

	ofstream outputFile(nomeFicheiro);
	Ponto p1 = Ponto(ponto_x, ponto_y, ponto_z);
	Ponto p2 = Ponto(-ponto_x, ponto_y, ponto_z);
	Ponto p3 = Ponto(-ponto_x, -ponto_y, ponto_z);
	Ponto p4 = Ponto(ponto_x, -ponto_y, ponto_z);
	Ponto p5 = Ponto(-ponto_x, ponto_y, -ponto_z);
	Ponto p6 = Ponto(ponto_x, ponto_y, -ponto_z);
	Ponto p7 = Ponto(-ponto_x, -ponto_y, -ponto_z);
	Ponto p8 = Ponto(ponto_x, -ponto_y, -ponto_z);


	outputFile << "8" << endl;
	outputFile << "12" << endl;
	//frente
	printTriangulo(outputFile, sep, p1, p2, p3);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p1, p3, p4);
	outputFile << "; " << endl;
	// lado esquerdo
	printTriangulo(outputFile, sep, p2, p5, p7);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p2, p7, p3);
	outputFile << "; " << endl;
	//lado direito
	printTriangulo(outputFile, sep, p1, p4, p8);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p1, p8, p6);
	outputFile << "; " << endl;
	//tras
	printTriangulo(outputFile, sep, p5, p6, p8);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p5, p8, p7);
	outputFile << "; " << endl;
	//cima
	printTriangulo(outputFile, sep, p1, p6, p5);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p1, p5, p2);
	outputFile << "; " << endl;
	//baixo
	printTriangulo(outputFile, sep, p3, p7, p4);
	outputFile << "; " << endl;
	printTriangulo(outputFile, sep, p4, p7, p8);
	outputFile << "; " << endl;
}

// radius - raio; slices - vertical; stacks - horizontal
void sphere(int radius, int slices, int stacks, FILE *nomeFicheiro) {
	double anguloAlfa = (2 * M_PI) / slices;
	double anguloBeta = (M_PI) / stacks;
	double anguloB = -(M_PI) / 2 + anguloBeta;
	double anguloBCima = (M_PI) / 2 - anguloBeta;
	double anguloA = 0, anguloAPolos = 0;
	size_t size = stacks + stacks - 2;
	std::vector<Ponto> triangulos(size);
	ofstream outputFile(nomeFicheiro);
	int nrTriangulos = slices*(stacks-1)*2;
	int nrVertices = 2 + (slices*(stacks - 1));

	outputFile << nrVertices << endl;
	outputFile << nrTriangulos << endl;

	// Para imprimir a esfera, começando de baixo
	// Imprime a primeira stack debaixo, com origem em (0,-raio,0)
	for (int i = 0; i < slices; i++) {
		
		Ponto poBaixo = Ponto(0, -radius, 0);
		double xPBaixo = radius*cos(anguloB)*sin(anguloAPolos);
		double yPBaixo = radius*sin(anguloB);
		double zPBaixo = radius*cos(anguloB)*cos(anguloAPolos);

		double x1PBaixo = radius*cos(anguloB)*sin(anguloAPolos + anguloAlfa);
		double y1PBaixo = radius*sin(anguloB);
		double z1PBaixo = radius*cos(anguloB)*cos(anguloAPolos + anguloAlfa);

		Ponto pBaixo = Ponto(xPBaixo, yPBaixo, zPBaixo);
		Ponto po1Baixo = Ponto(x1PBaixo, y1PBaixo, z1PBaixo);

		printTriangulo(outputFile, sep, poBaixo, po1Baixo, pBaixo);
		//outputFile << ";" << endl;
		anguloAPolos = anguloAPolos + anguloAlfa;

		
	}

	for (int i = 0; i < slices; i++) {
		for (int j = 0, k = 0; j < (stacks-1); j++, k = k + 2) {

			double x = radius*cos(anguloB)*sin(anguloA);
			double y = radius*sin(anguloB);
			double z = radius*cos(anguloB)*cos(anguloA);

			double x1 = radius*cos(anguloB)*sin(anguloA + anguloAlfa);
			double y1 = radius*sin(anguloB);
			double z1 = radius*cos(anguloB)*cos(anguloA + anguloAlfa);

			Ponto p = Ponto(x, y, z);
			Ponto p1 = Ponto(x1, y1, z1);

			triangulos[k] = p;
			triangulos[k + 1] = p1;
		
			anguloB = anguloB + anguloBeta;
		}

		for (int i = 0; i <= (stacks - 2)*2 ; i = i + 2) {
			printTriangulo(outputFile, sep, triangulos[i+1], triangulos[i+2], triangulos[i]);
			//outputFile << ";" << endl;
			printTriangulo(outputFile, sep, triangulos[i + 1], triangulos[i + 3], triangulos[i + 2]);
			//outputFile << ";" << endl;
		}
		anguloB = -(M_PI) / 2 + anguloBeta;
		anguloA = anguloA + anguloAlfa;
	}

	// Imprime a primeira stack de cima, com origem em (0,raio,0)
	for (int i = 0; i < slices; i++) {
		Ponto poCima = Ponto(0, radius, 0);
		double xPCima = radius*cos(anguloBCima)*sin(anguloAPolos);
		double yPCima = radius*sin(anguloBCima);
		double zPCima = radius*cos(anguloBCima)*cos(anguloAPolos);

		double x1PCima = radius*cos(anguloBCima)*sin(anguloAPolos + anguloAlfa);
		double y1PCima = radius*sin(anguloBCima);
		double z1PCima = radius*cos(anguloBCima)*cos(anguloAPolos + anguloAlfa);

		Ponto pCima = Ponto(xPCima, yPCima, zPCima);
		Ponto p1Cima = Ponto(x1PCima, y1PCima, z1PCima);

		printTriangulo(outputFile, sep, poCima, pCima, p1Cima);
		//outputFile << ";" << endl;
		anguloAPolos = anguloAPolos + anguloAlfa;
	}
}
	
void circunferenciaBaixo(int radius, int slices, ofstream &file) {
	double angulo = (2 * M_PI) / slices;
	double a = 0;
	for (int i = 0; i < slices; i++) {
		//ponto atual
		double px = radius * sin(a);
		double pz = radius * cos(a);
		Ponto p = Ponto(px, 0, pz);

		//ponto seguinte
		double pxNext = radius * sin(a+angulo);
		double pzNext = radius * cos(a+angulo);
		Ponto pNext = Ponto(pxNext, 0, pzNext);

		Ponto pOrigem = Ponto(0, 0, 0);
		printTriangulo(file, sep, pOrigem, pNext, p);
		//file << ";" << endl;

		a = a + angulo;
	}
}

void cone(int bottomRadius, int height, int slices, int stacks, FILE *nomeFicheiro) {
	ofstream outputFile(nomeFicheiro);
	int nrVertices = slices + 1;
	int nrTriangulos = slices * 2;
	outputFile << nrVertices << endl;
	outputFile << nrTriangulos << endl;
	circunferenciaBaixo(bottomRadius, slices, outputFile);
	Ponto pico = Ponto(0, height, 0);

	

	double angulo = (2 * M_PI) / slices;
	double a = 0;
	for (int i = 0; i < slices; i++) {
		//ponto atual
		double px = bottomRadius * sin(a);
		double pz = bottomRadius * cos(a);
		Ponto p = Ponto(px, 0, pz);

		//ponto seguinte
		double pxNext = bottomRadius * sin(a + angulo);
		double pzNext = bottomRadius * cos(a + angulo);
		Ponto pNext = Ponto(pxNext, 0, pzNext);

		printTriangulo(outputFile, sep, pNext, pico, p);

		a = a + angulo;

	}
}
// Tentativa de fazer o cone com stacks
	/*double anguloAlfa = (2 * M_PI) / slices;
	double anguloBeta = (M_PI/2) / stacks;
	double anguloA = 0;
	double anguloB = 0, beta=0;
	ofstream outputFile(nomeFicheiro);
	size_t size = stacks *2;
	double alturaY = height / stacks;
	double altura = height/ stacks;
	double r;
		
	circunferenciaBaixo(bottomRadius, slices, outputFile);

	for (int i = 0; i < slices; i++) {
		double rLinha = bottomRadius * cos(0);
		std::vector<Ponto> triangulos(size);
		for (int j = 0, k = 0; j < (stacks); j++, k = k + 2) {
			rLinha = rLinha * cos(anguloB);

			double x = rLinha* sin(anguloA);
			double y = altura*sin(anguloB);
			double z = rLinha*cos(anguloA);

			double x1 = rLinha*sin(anguloA + anguloAlfa);
			double y1 = altura*sin(anguloB);
			double z1 = rLinha*cos(anguloA + anguloAlfa);

			/*double x = bottomRadius*cos(anguloB)* sin(anguloA);
			double y = bottomRadius*sin(anguloB);
			double z = bottomRadius*cos(anguloB)*cos(anguloA);

			double x1 = bottomRadius*cos(anguloB)*sin(anguloA + anguloAlfa);
			double y1 = bottomRadius*sin(anguloB);
			double z1 = bottomRadius*cos(anguloB)*cos(anguloA + anguloAlfa);*

			Ponto p = Ponto(x, y, z);
			Ponto p1 = Ponto(x1, y1, z1);

			triangulos[k] = p;
			triangulos[k + 1] = p1;

			anguloB = anguloB + anguloBeta;
			r = rLinha;
			altura = altura + alturaY;
		}
	
		anguloA = anguloA + anguloAlfa;
		beta = anguloB;
		anguloB=0;
		
		for (int i = 0; i <= (stacks - 1)*2; i = i + 2) {
			printTriangulo(outputFile, sep, triangulos[i+1], triangulos[i + 2], triangulos[i]);
			//outputFile << ";" << endl;
			printTriangulo(outputFile, sep, triangulos[i + 1], triangulos[i+3], triangulos[i + 2]);
			//outputFile << ";" << endl;
		}
	}

	//double r = rLinha;
	double anguloAPolos = 0;
	for (int i = 0; i < slices; i++) {
		double anguloBCima = (M_PI) / 2 - anguloBeta;
		//double r = rLinha * cos(anguloBCima);
		Ponto poCima = Ponto(0, height, 0);
		double xPCima = r*sin(anguloAPolos);
		double yPCima = r*sin(beta);
		double zPCima = r*cos(anguloAPolos);

		double x1PCima = r*sin(anguloAPolos + anguloAlfa);
		double y1PCima = r*sin(beta);
		double z1PCima = r*cos(anguloAPolos + anguloAlfa);

		Ponto pCima = Ponto(xPCima, yPCima, zPCima);
		Ponto p1Cima = Ponto(x1PCima, y1PCima, z1PCima);

		printTriangulo(outputFile, sep, poCima, pCima, p1Cima);
		//outputFile << ";" << endl;
		anguloAPolos = anguloAPolos + anguloAlfa;
	}	*/

 
int main(int argc, char **argv) {

	//deixa o utilizador escrever no terminal o nome do ficheiro
	std::string name;
	std::getline(std::cin, name);

	//cria o vector
	vector<string>vectorInput = splitString(name);

	//numero de elementos do vetor
	int count = vectorInput.size();

	// adiciona o path do ficheiro ao nome dado anteriormente
	string path = "C:/Users/PC/Desktop/TP_CG/3dFiles/";
	path += vectorInput[count-1];

	if (strcmp("generator", vectorInput[0].c_str()) == 0) {
		// para criar o ficheiro;
		// o c_str converte o std::string para um standard C string.
		FILE *pFile;
		fopen_s(&pFile, path.c_str(), "w");

		if (strcmp("plane", vectorInput[1].c_str()) == 0) {
			plano(atoi(vectorInput[2].c_str()), pFile);
		}
		else if (strcmp("box", vectorInput[1].c_str()) == 0) {
			box(atoi(vectorInput[2].c_str()), atoi(vectorInput[3].c_str()), atoi(vectorInput[4].c_str()), pFile);
		}
		else if (strcmp("sphere", vectorInput[1].c_str()) == 0) {
			sphere(atoi(vectorInput[2].c_str()), atoi(vectorInput[3].c_str()), atoi(vectorInput[4].c_str()), pFile);
		}
		else if (strcmp("cone", vectorInput[1].c_str()) == 0) {
			cone(atoi(vectorInput[2].c_str()), atoi(vectorInput[3].c_str()), atoi(vectorInput[4].c_str()), atoi(vectorInput[5].c_str()), pFile);
		}

	}

	//Depois arranjar maneira de não sair do programa qd da erro
	else cout << "Erro" << endl;

	return 0;
}


