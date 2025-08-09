#include "../Headers/Structuri.h"

//Window management
WNDPROC OldWndProc = NULL;
int lungimeFereastra;
int inaltimeFereastra;
int pagina;
bool inchideEditor, fereastraActiva;

//Objects
vector<Obiect> obiecte;
vector<int> obiecteSelectate;
int obiectSelectat, nrObiect;
bool axeMiscareObiect, obiectCentrat;

//Vertices
Punct2D pozitieMouseUnirePuncte;
vector<int> puncteSelectate, culoarePuncteSelectate, culoarePuncte;
int varfSelectat, marimeAxeVarfSelectat;
bool selectarePuncte, deseneazaPuncte, axePunct;

//Edges
vector<int> culoareMuchii;
bool deseneazaMuchii;

//Faces
vector<int> copieCuloareFata;
int fataSelectata;
bool deseneazaFete, colorarePuncteSelectate, unestePuncte, adaugaPunct, eliminaPuncte;

//Functionalities
char axaSelectata;
double zoom, unghiRotatie, coeficientMarire, coeficientDeplasare, coeficientZoom;
int ultimaPozitieMouseX, ultimaPozitieMouseY, numarareRotatii, numarareDeplasare, numarareMarire, axeObiectSelectat, indexStart;
bool  mouseApasat, local, undoRotatieGrid, max360, xRay;
stack<Undo> undo;
stack<Undo> redo;

//Frontend
Obiect grid;
vector<int> col;
vector<bool> hoverButoane;
vector<vector<int>> coordonateInputBox, coordonateButoaneHover;
int butonHover, butonGrid, selectareInput, fereastraDreapta, fereastraStanga;
bool butonApasat, modificaPagina, fereastraFile, fereastraAdauga, nuDesena;