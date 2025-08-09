#pragma once

#include <windows.h>

#include <vector>
#include <stack>

using namespace std;

#define razaPunct 4
#define POV 15

struct Punct2D {
    double x;
    double y;
};

struct Punct3D {
    double x;
    double y;
    double z;
};

struct Obiect {
    bool activ;

    double rotatieX, rotatieY, rotatieZ;
    double marimeX, marimeY, marimeZ;
    double deplasareX, deplasareY, deplasareZ;

    vector<Punct3D> varfuri;
    vector<pair<int, int>> muchii;

    vector<vector<int>> fete, culoareFete;
    vector<int> culoareFata, indexFata;

    Punct3D centru, centruPentruAxe;

    Punct3D axaOX, axaOY, axaOZ;

    vector<Punct3D> axePunctSelectat, axeObiectStabile;
    
    //first -> axa; second -> angle value
    stack<pair<char, double>> rotatiiAnterioare;
    stack<pair<char, double>> stackDeplasare, stackMarire;
    stack<pair<char, double>> stackRedoRotatie, stackRedoDeplasare, stackRedoMarire;

    Obiect() {}
};

struct Undo {
    int alegere;
    int numarRotatii;

    char axa;
    bool local;
    vector<pair<int, double>> coordonate, indexFete;
    vector<vector<int>> culoareFete;
    vector<vector<int>> fete;
    vector<int> index;
    Punct3D puncteEliminat;
};

//Window management
extern WNDPROC OldWndProc;
extern int lungimeFereastra;
extern int inaltimeFereastra;
extern int pagina;
extern bool inchideEditor, fereastraActiva;

//Objects
extern vector<Obiect> obiecte;
extern vector<int> obiecteSelectate;
extern int obiectSelectat, nrObiect;
extern bool axeMiscareObiect, obiectCentrat;

//Vertices
extern Punct2D pozitieMouseUnirePuncte;
extern vector<int> puncteSelectate, culoarePuncteSelectate, culoarePuncte;
extern int varfSelectat, marimeAxeVarfSelectat;
extern bool selectarePuncte, deseneazaPuncte, axePunct;

//Edges
extern vector<int> culoareMuchii;
extern bool deseneazaMuchii;

//Faces
extern vector<int> copieCuloareFata;
extern int fataSelectata;
extern bool deseneazaFete, colorarePuncteSelectate, unestePuncte, adaugaPunct, eliminaPuncte;

//Functionalities
extern char axaSelectata;
extern double zoom, unghiRotatie, coeficientMarire, coeficientDeplasare, coeficientZoom;
extern int ultimaPozitieMouseX, ultimaPozitieMouseY, numarareRotatii, numarareDeplasare, numarareMarire, axeObiectSelectat, indexStart;
extern bool  mouseApasat, local, undoRotatieGrid, max360, xRay;
extern stack<Undo> undo;
extern stack<Undo> redo;

//Frontend
extern Obiect grid;
extern vector<int> col;
extern vector<bool> hoverButoane;
extern vector<vector<int>> coordonateInputBox, coordonateButoaneHover;
extern int butonHover, butonGrid, selectareInput, fereastraDreapta, fereastraStanga;
extern bool butonApasat, modificaPagina, fereastraFile, fereastraAdauga, nuDesena;