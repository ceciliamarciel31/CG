#include "Ponto.h" 
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip> 
#include <math.h>

Ponto::Ponto() {}

Ponto::Ponto(double xx, double yy, double zz) {
		x = xx;
		y = yy;
		z = zz;
	}

double Ponto::getx() { return x; }
double Ponto::getz() { return z; }
double Ponto::gety() { return y; }

void Ponto::setX(double x) { this->x = x; }
void Ponto::setY(double y) { this->y = y; }
void Ponto::setZ(double z) { this->z = z; }


void Ponto::printFile(ofstream& file, string sep) {
		//Passa o float para string e set the precision to 1 
		stringstream stream_x;
		stringstream stream_y;
		stringstream stream_z;
		stream_x << fixed << setprecision(1) << x;
		stream_y << fixed << setprecision(1) << y;
		stream_z << fixed << setprecision(1) << z;
		string sx = stream_x.str();
		string sy = stream_y.str();
		string sz = stream_z.str();

		file << sx << sep << sy << sep << sz << endl;

	}

