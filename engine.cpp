#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <iomanip> 
#include <GL/glut.h>
#include "tinyxml.h"
#include <list>
#include "Ponto.h"

#define _USE_MATH_DEFINES
#include <math.h>


using namespace std;

typedef struct color {

	double red, green, blue;

}color;


color colorList[] = { (1.0,0.0,0.0), (0.0,1.0,0.0), (0.0,0.0,1.0), (0.0,1.0,1.0), (1.0,0.0,1.0), (1.0,1.0,0.0) };

void getColor(int i) {
	switch (i)
	{
		case 0: glColor3f(1.0, 0.0, 0.0); break;
		case 1: glColor3f(0.0, 1.0, 0.0); break;
		case 2: glColor3f(0.0, 0.0, 1.0); break;
		case 3: glColor3f(1.0, 1.0, 0.0); break;
		case 4: glColor3f(1.0, 0.0, 1.0); break;
		case 5: glColor3f(0.0, 1.0, 1.0); break;
	}
	
}


typedef vector <Ponto> modelo;
typedef vector <modelo> cena;

cena CENA;

float ax = 0.0, ay = 0.0, az = 0.0, xx = 0.0, zz= 0.0;
float xa = 0.0, ya = 0.0, za = 0.0;
float rotx, roty, rotz;
float a = 0.0, b = 0.0, r = 25.0;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {

	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
	gluLookAt(rotx, roty, rotz,
		xa, ya, za,
		0.0f, 1.0f, 0.0f);

	glTranslatef(xx, 0, zz);
	glRotatef(ax, 1, 0, 0);
	glRotatef(ay, 0, 1, 0);
	glRotatef(az, 0, 0, 1);
	// put drawing instructions here
	glBegin(GL_TRIANGLES);



	int i = 0;
	
	// ciclo para cada modelo numa cena
	for (vector<modelo>::iterator modelo = CENA.begin(); modelo != CENA.end(); modelo++) {
		// ciclo para cada Ponto num modelo
		for (vector<Ponto>::iterator Ponto = modelo->begin(); Ponto != modelo->end(); Ponto++) {
			

			getColor(i);
			//glColor3f(1.0, 0.0, 0.0);
			
			glVertex3d(Ponto->getx(), Ponto->gety(), Ponto->getz());
			//cout << Ponto::Ponto->getx() << endl;
			//cout << Ponto->gety() << endl;
			//cout << Ponto->getz() << endl;
			if (i >= 5) i = 0;
			else i++;
		}
	
	glEnd();


	}
	

	// End of frame
	glutSwapBuffers();
}

void processKeys(unsigned char c, int x, int y) {
	char k = tolower(c);
	// put code to process regular keys in here
	switch (k)
	{
		case 'w': xa -= 1; break;
		case 's': xa += 1; break;
		case 'e': ya += 1; break;
		case 'q': ya -= 1; break;
		case 'd': za += 1; break;
		case 'a': za -= 1; break;
	}
	glutPostRedisplay();
	
}


void processSpecialKeys(int key, int x, int y) {
	
	// put code to process special keys in here
	switch (key) {
		case GLUT_KEY_RIGHT :
		a -= 0.1; break;

	case GLUT_KEY_LEFT:
		a += 0.1; break;

	case GLUT_KEY_UP: b += 0.1f;
		if (b > 1.5f) b = 1.5f;
		break;

	case GLUT_KEY_DOWN: b -= 0.1f;
		if (b < -1.5f) b = -1.5f;
		break;

	case GLUT_KEY_PAGE_DOWN: r -= 0.5f;
		if (r < 0.1f) r = 0.1f;
		break;

	case GLUT_KEY_PAGE_UP: r += 0.5f; break;
	}
	
	rotx = r * cos(b) * sin(a);
	roty = r * sin(b);
	rotz = r * cos(b) * cos(a);

	glutPostRedisplay();

	
	
}
vector<string> splitString(string s, string delimiter) {
	//string buf;
	//stringstream ss(s);
	size_t pos = 0;
	std::string token;
	vector<string> tokens;

	
		while ((pos = s.find(delimiter)) != std::string::npos) {
			token = s.substr(0, pos);
			
			tokens.push_back(token);
			s.erase(0, pos + delimiter.length());
			
		}
		
		tokens.push_back(s);
		return tokens;
	
}
/*string buf; // Have a buffer string
	stringstream ss(str); // Insert the string into a stream

	vector<string> tokens; // Create vector to hold our words

	while (ss >> buf)
		if (str.compare(delim) != 0) {
			tokens.push_back(buf);
		}
	return tokens;
}*/


// Devolve os pontos do ficheiro .3d
vector <Ponto> parser(string nome) {
	vector <Ponto> pontos;
	int i = 0;
	double x= 0, y=0, z=0;
	string line ;
	ifstream file(nome);
	//streamsize n = file.size();
	while (file && i<2)
	{
		getline(file, line);
		i++;
	}
	while (file && getline(file, line)) {
		//if (line.compare(";") != 0) {
			vector<string> stri = splitString(line, ";");
			//cout << stri.size << endl;
			x = atof(stri[0].c_str());
			y = atof(stri[1].c_str());
			z = atof(stri[2].c_str());

			//cout << stri[0] << endl;
			//cout << stri[1] << endl;
			//cout << stri[2] << endl;
			//sscanf(stri[0].c_str(), "%lf", x);
			//sscanf(stri[1].c_str(), "%lf", y);
			//sscanf(stri[2].c_str(), "%lf", z);
			Ponto p = Ponto(x, y, z);

			pontos.push_back(p);
		//}
	}
	file.close();
	return pontos;
}

// Devolve o nome dos ficheros .3d que se encontram no XML
vector <string> get_3d(char* nome) {
	vector<string> files;
	TiXmlDocument doc(nome);
	if (doc.LoadFile()) {
		TiXmlElement* root = doc.RootElement();
		
		TiXmlElement* modelo = root->FirstChild("model")->ToElement();
		while (modelo) {
			const string nome = modelo->Attribute("file");
			files.push_back(nome);
			modelo = modelo->NextSiblingElement();
		}
		
	}
	
	

	return files;
	
}


int main(int argc, char **argv) {

	

	// adiciona o path do ficheiro ao nome dado anteriormente
	string path = "C:/Users/PC/Desktop/TP_CG/3dFiles/";
	
	

	// Load do XML (falta testar)
	TiXmlDocument doc("C:/Users/PC/Desktop/TP_CG/configure.xml");
	bool loadOkay = doc.LoadFile();
	if (!loadOkay)
	{
		cout << "Ficheiro XML nao carregado.\n";
		return 1;
	}
	

	
	// Descobre os ficheiros 3D mencionados no XML
	
	vector<string> files = get_3d("C:/Users/PC/Desktop/TP_CG/configure.xml");
	
	int count = files.size();
	for (vector<string>::iterator file = files.begin(); file != files.end(); ++file) {
	
		path += *file;
		// Descobre os pontos existentes no ficheiro 3D
		CENA.push_back(parser(path));
	}
  

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("CG@DI-UM");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();



	return 1;
}