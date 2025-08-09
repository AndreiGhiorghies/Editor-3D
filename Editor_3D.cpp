#include <string>
#include <winbgim.h>

#include "Headers/Structuri.h"
#include "Headers/Deseneaza.h"
#include "Headers/Functionalitati.h"
#include "Headers/Model_data.h"
#include "Headers/PoligonTools.h"
#include "Headers/Utils.h"
#include "Headers/Fisiere.h"
#include "Headers/Transformari.h"
#include "Headers/UndoRedo.h"

#include "Icon/resource.h"

LRESULT CALLBACK WndProcCustom(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_ACTIVATE) {
        fereastraActiva = (LOWORD(wParam) != WA_INACTIVE);
    }

    return CallWindowProc(OldWndProc, hwnd, msg, wParam, lParam);
}

void InitializareFereastra() {
    RECT workArea;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &workArea, 0);

    lungimeFereastra = workArea.right - workArea.left;
    inaltimeFereastra = workArea.bottom - workArea.top;
 
    initwindow(lungimeFereastra, inaltimeFereastra, "Editor 3D", workArea.left, workArea.top);

    HWND hwnd = GetForegroundWindow();

    HICON hIconBig = (HICON)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDI_ICON1),
        IMAGE_ICON,
        32, 32,
        0
    );
    SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIconBig);

    HICON hIconSmall = (HICON)LoadImage(
        GetModuleHandle(NULL),
        MAKEINTRESOURCE(IDI_ICON1),
        IMAGE_ICON,
        16, 16,
        0
    );
    SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSmall);

    SetWindowLong(hwnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
    ShowWindow(hwnd, SW_MAXIMIZE);

    setviewport(0, 0, lungimeFereastra - 1, inaltimeFereastra - 1, 1);

    OldWndProc = (WNDPROC)SetWindowLongPtr(hwnd, GWLP_WNDPROC, (LONG_PTR)WndProcCustom);
}

void InitializareVariabileGlobale() {
    coordonateInputBox = vector<vector<int>>(51, {0, 0, 0, 0});
    coordonateButoaneHover = vector<vector<int>>(42, {0, 0, 0, 0}); //0-10 normal butons; 10-33 for vertices
    copieCuloareFata = vector<int>(3, 100);

    culoarePuncteSelectate = {0, 255, 0};
    culoarePuncte = {255, 255, 255};
    culoareMuchii = {255, 255, 255};

    deseneazaFete = true;
    deseneazaPuncte = false;
    deseneazaMuchii = false;

    fereastraAdauga = false;
    obiectCentrat = false;
    modificaPagina = true;
    axePunct = false;
    local = false;
    xRay = false;

    fereastraDreapta = 0;
    fereastraStanga = 0;
    butonGrid = 0;
    axeObiectSelectat = 0;

    varfSelectat = -1;
    fataSelectata = -1;
    butonHover = -1;

    zoom = 100;
    unghiRotatie = 2 / 180.0 * 3.14;
    coeficientMarire = 0.02;
    coeficientDeplasare = 0.05;
    coeficientZoom = 0.5;
}

void CreazaGrid(const int &lungime, const int &latime) {
    for(int i = 0; i <= lungime; i++)
        for(int j = 0; j <= latime; j++) {
            grid.varfuri.push_back({(double) (i - lungime / 2) * 3, 3, (double) (j - 10) * 3});

            if(j < latime)
                grid.muchii.push_back({i * (latime + 1) + j, i * (latime + 1) + j + 1});
            
            if(i < lungime)
                grid.muchii.push_back({(i + 1) * (latime + 1) + j, i * (latime + 1) + j});
        }
    
    grid.centru = GetMijlocObiect(grid);
    
    for(int i = 0; i < grid.varfuri.size(); i++) {
        grid.varfuri[i].x -= grid.centru.x;
        grid.varfuri[i].z -= grid.centru.z;
    }
}

int main() {
    InitializareFereastra();

    InitializareVariabileGlobale();

    CreazaGrid(10, 6);

    fereastraActiva = true;

    //obj is a copy from the obiecte vector for use when there are no selected objects
    Obiect obj = IncarcaObiectDefault(cub);
    obj.activ = true;
    obiecte.push_back(obj);
    obiectSelectat = static_cast<int>(obiecte.size()) - 1;
    obiecteSelectate.push_back(obiectSelectat);

    Deseneaza(obj);
    Deseneaza(obj);

    while(!inchideEditor) {
        if(!fereastraActiva) {
            delay(200);

            continue;
        }

        if(obiectSelectat == -1 || !obiecte[obiectSelectat].activ) {
            VerificaHoverButoane(obj);  
            VerificaApasareVarf(obj);

            if(obiectSelectat != -1)
                VerificaApasareButon(obiecte[obiectSelectat]);

            VerificareZoom(obj);

            //For rotating only the grid with ALT when there are no objects selected
            if(butonGrid && (GetAsyncKeyState(VK_MENU) & 0x8000))
                VerificareRotatie(obj);
            
            if(ismouseclick(WM_LBUTTONDOWN))
                clearmouseclick(WM_LBUTTONDOWN);
            
            delay(3);
            
            continue;
        }

        //For selecting faces: E -> next face; Q -> previous face; W -> deselect face
        if(GetAsyncKeyState('Q') & 0x8000) {
            if(fataSelectata == -1)
               fataSelectata = 0;
            else 
                SelecteazaFata(obiecte[obiectSelectat], obiecte[obiectSelectat].indexFata[fataSelectata] - 1);
        }
        else if(GetAsyncKeyState('E') & 0x8000) {
                if(fataSelectata == -1)
                    fataSelectata = 0;
                else 
                    SelecteazaFata(obiecte[obiectSelectat], obiecte[obiectSelectat].indexFata[fataSelectata] + 1);
            }
        else if(GetAsyncKeyState('W') & 0x8000 && fataSelectata != -1) {
                fataSelectata = -1;

                Deseneaza(obj);
            }
            
        VerificaApasareButon(obiecte[obiectSelectat]);
        VerificaApasareVarf(obiecte[obiectSelectat]);

        VerificareZoom(obiecte[obiectSelectat]);  
        VerificaScrool(obiecte[obiectSelectat]);

        UndoChange(obiecte[obiectSelectat], false);
            
        RedoChange(obiecte[obiectSelectat], false);

        VerificareRotatie(obiecte[obiectSelectat]);

        VerificareMarire(obiecte[obiectSelectat]);

        VerificareDeplasare(obiecte[obiectSelectat]);

        VerificareZoom(obiecte[obiectSelectat]);
        
        CrearePoligon(obiecte[obiectSelectat]);
            
        AdaugaPunct(obiecte[obiectSelectat]);
            
        VerificaHoverButoane(obiecte[obiectSelectat]);
    }

    return 0;
}