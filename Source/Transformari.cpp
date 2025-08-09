#include "../Headers/Transformari.h"
#include "../Headers/Utils.h"
#include "../Headers/Deseneaza.h"

#include <math.h>
#include <winbgim.h>

//-------------------------------------------------- MOVE TOOL ------------------------------------------------------------------

void DeplaseazaX(Obiect &obj) {
    obj.deplasareX += coeficientDeplasare;

    for(int i = 0; i < obj.varfuri.size(); i++)
        obj.varfuri[i].x += coeficientDeplasare;

    obj.axaOX.x += coeficientDeplasare;
    obj.axaOY.x += coeficientDeplasare;
    obj.axaOZ.x += coeficientDeplasare;

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i].x += coeficientDeplasare;
}

void DeplaseazaY(Obiect &obj) {
    obj.deplasareY += coeficientDeplasare;

    for(int i = 0; i < obj.varfuri.size(); i++)
        obj.varfuri[i].y += coeficientDeplasare;

    obj.axaOX.y += coeficientDeplasare;
    obj.axaOY.y += coeficientDeplasare;
    obj.axaOZ.y += coeficientDeplasare;

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i].y += coeficientDeplasare;
}

void DeplaseazaZ(Obiect &obj) {
    obj.deplasareZ += coeficientDeplasare;

    for(int i = 0; i < obj.varfuri.size(); i++)
        obj.varfuri[i].z += coeficientDeplasare;

    obj.axaOX.z += coeficientDeplasare;
    obj.axaOY.z += coeficientDeplasare;
    obj.axaOZ.z += coeficientDeplasare;

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i].z += coeficientDeplasare;
}

void VerificareDeplasare(Obiect &obj) {
    if(!obj.activ)
        return;
    
    bool x = GetAsyncKeyState('X') & 0x8000;
    bool y = GetAsyncKeyState('Y') & 0x8000;
    bool z = GetAsyncKeyState('Z') & 0x8000;
    bool up = GetAsyncKeyState(VK_UP) & 0x8000, down = GetAsyncKeyState(VK_DOWN) & 0x8000;
    bool left = GetAsyncKeyState(VK_LEFT) & 0x8000, right = GetAsyncKeyState(VK_RIGHT) & 0x8000;

    if(!(x && left) && !(x && right) && !(y && up) && !(y && down) && !(z && up) && !(z && down)) {
        if(numarareDeplasare != 0) {
            clearStack(redo);
            Undo temp;
            temp.alegere = 2;
            temp.local = local;
            temp.numarRotatii = numarareDeplasare;
            numarareDeplasare = 0;
            undo.push(temp);
        }

        return;
    }
    
    if(left || (y && up) || (z && down && !y))
        coeficientDeplasare = -coeficientDeplasare;
    
    if(local) 
        EditareRotatie(obj, true);

    if(x && (left || right)) {
        DeplaseazaX(obj);
        obj.stackDeplasare.push({'x', coeficientDeplasare});
        numarareDeplasare++;
    }
    if(y && (up || down)) {
        DeplaseazaY(obj);
        obj.stackDeplasare.push({'y', coeficientDeplasare});
        numarareDeplasare++;
    }
    else if(z && (up || down)) {
        DeplaseazaZ(obj);
        obj.stackDeplasare.push({'z', coeficientDeplasare});
        numarareDeplasare++;
    }

    if(local)
        EditareRotatie(obj, false);

    if(left || (y && up) || (z && down && !y))
        coeficientDeplasare = -coeficientDeplasare;

    obj.centru = GetMijlocObiect(obj);
    obj.centruPentruAxe = obj.centru;

    Deseneaza(obj);
}

//---------------------------------------------- END OF MOVE TOOL ---------------------------------------------------------------

//------------------------------------------------ ROTATION TOOL ----------------------------------------------------------------

void RotestePunctX(Punct3D &punct) {
    double x = punct.x;

    punct.x = cos(unghiRotatie) * x - sin(unghiRotatie) * punct.z;
    punct.z = sin(unghiRotatie) * x + cos(unghiRotatie) * punct.z;
}

void RotestePunctY(Punct3D &punct) {
    double y = punct.y;

    punct.y = cos(-unghiRotatie) * y - sin(-unghiRotatie) * punct.z;
    punct.z = sin(-unghiRotatie) * y + cos(-unghiRotatie) * punct.z;    
}

void RotestePunctZ(Punct3D &punct) {
    double x = punct.x;

    punct.x = cos(unghiRotatie) * x - sin(unghiRotatie) * punct.y;
    punct.y = sin(unghiRotatie) * x + cos(unghiRotatie) * punct.y;
}

void RotesteObiectX(Obiect &obj) {
    obj.rotatieX += unghiRotatie;

    for(Punct3D &varf : obj.varfuri)
        RotestePunctX(varf);
    
    RotestePunctX(obj.axaOX);
    RotestePunctX(obj.axaOY);
    RotestePunctX(obj.axaOZ);

    for(Punct3D &pct : obj.axeObiectStabile)
        RotestePunctX(pct);

    for(Punct3D &pct : obj.axePunctSelectat)
        RotestePunctX(pct);
    
    //Rotate the grid with ALT
    if((butonGrid && (GetAsyncKeyState(VK_MENU) & 0x8000)) || undoRotatieGrid)
        for(Punct3D &i : grid.varfuri)
            RotestePunctX(i);
}

void RotesteObiectY(Obiect &obj) {
    obj.rotatieY += unghiRotatie;

    for(int i = 0; i < obj.varfuri.size(); i++)
        RotestePunctY(obj.varfuri[i]);
    
    RotestePunctY(obj.axaOX);
    RotestePunctY(obj.axaOY);
    RotestePunctY(obj.axaOZ);

    for(int i = 1; i < 4; i++)
        RotestePunctY(obj.axeObiectStabile[i]);
    
    if((butonGrid == 2 && (GetAsyncKeyState(VK_MENU) & 0x8000)) || undoRotatieGrid) //ALT
        for(Punct3D &i : grid.varfuri)
            RotestePunctY(i);

    for(int i = 0; i < 3; i++)
        RotestePunctY(obj.axePunctSelectat[i]);
}

void RotesteObiectZ(Obiect &obj) {
    obj.rotatieZ += unghiRotatie;

    for(int i = 0; i < obj.varfuri.size(); i++)
        RotestePunctZ(obj.varfuri[i]);
    
    RotestePunctZ(obj.axaOX);
    RotestePunctZ(obj.axaOY);
    RotestePunctZ(obj.axaOZ);
    
    for(int i = 1; i < 4; i++)
        RotestePunctZ(obj.axeObiectStabile[i]);

    for(int i = 0; i < 3; i++)
        RotestePunctZ(obj.axePunctSelectat[i]);
}

void EditareRotatie(Obiect &obj, const bool &resetareRotatie) {
    CentreazaObiect(obj);

    stack<pair<char, double>> save;
    double saveUnghiRotatie = unghiRotatie;
    int resetare;
    
    if(resetareRotatie)
        resetare = -1;
    else
        resetare = 1;

    while(!obj.rotatiiAnterioare.empty()) {
        char axa = obj.rotatiiAnterioare.top().first;
        unghiRotatie = resetare * obj.rotatiiAnterioare.top().second;

        save.push(obj.rotatiiAnterioare.top());
        obj.rotatiiAnterioare.pop();
        
        if(axa == 'x') {
            RotesteObiectX(obj);
        }
        else if(axa == 'y')
                RotesteObiectY(obj);
        else
            RotesteObiectZ(obj);
    }

    unghiRotatie = saveUnghiRotatie;
    obj.rotatiiAnterioare = save;

    RefacePozitia(obj);
}

void VerificareRotatie(Obiect &obj) {
    if(!obj.activ)
        return;
    
    bool x = GetAsyncKeyState('X') & 0x8000;
    bool y = GetAsyncKeyState('Y') & 0x8000;
    bool z = GetAsyncKeyState('Z') & 0x8000;
    bool up = GetAsyncKeyState(VK_UP) & 0x8000, down = GetAsyncKeyState(VK_DOWN) & 0x8000;
    bool left = GetAsyncKeyState(VK_LEFT) & 0x8000, right = GetAsyncKeyState(VK_RIGHT) & 0x8000;
    
    bool rotireDiagonala = (left && up) || (left && down) || (right && up) || (right && down);
    double saveUnghiRotatie = unghiRotatie;

    if(x || y || (z && !left && !right) || (!left && !right && !up && !down) || (fereastraStanga && mousex() <= 140)) {
       if(numarareRotatii != 0) {
            clearStack(redo);

            Undo temp;
            temp.alegere = 1;
            temp.numarRotatii = numarareRotatii;
            numarareRotatii = 0;

            if(undoRotatieGrid)
                temp.axa = 'g';
            
            undo.push(temp);
        }
        undoRotatieGrid = false;

        return;
    }

    if(numarareRotatii != 0 && undoRotatieGrid != ((GetAsyncKeyState(VK_MENU) & 0x8000) && butonGrid == 2)) {
        clearStack(redo);

        Undo temp;
        temp.alegere = 1;
        temp.numarRotatii = numarareRotatii;
        numarareRotatii = 0;

        if(undoRotatieGrid)
            temp.axa = 'g';
        
        undo.push(temp);
    }

    undoRotatieGrid = (GetAsyncKeyState(VK_MENU) & 0x8000) && butonGrid == 2;

    int salvareSize = (int) obj.rotatiiAnterioare.size();

    if(rotireDiagonala)
        unghiRotatie /= 1.5;

    if((up || down || left || right))
        CentreazaObiect(obj);

    if(left) {
        unghiRotatie = -unghiRotatie;
        if(z) {
            RotesteObiectZ(obj);

            obj.rotatiiAnterioare.push({'z', unghiRotatie});
        }
        else {
            RotesteObiectX(obj);

            obj.rotatiiAnterioare.push({'x', unghiRotatie});
        }

        unghiRotatie = -unghiRotatie;
    }

    if(right) {
        if(z) {
            RotesteObiectZ(obj);

            obj.rotatiiAnterioare.push({'z', unghiRotatie});
        }
        else {
            RotesteObiectX(obj);

            obj.rotatiiAnterioare.push({'x', unghiRotatie});
        }
    }

    if(up) {
        RotesteObiectY(obj);

        obj.rotatiiAnterioare.push({'y', unghiRotatie});
    }

    if(down) {
        unghiRotatie = -unghiRotatie;

        RotesteObiectY(obj);

        obj.rotatiiAnterioare.push({'y', unghiRotatie});

        unghiRotatie = -unghiRotatie;
    }

    numarareRotatii += (int) obj.rotatiiAnterioare.size() - salvareSize;
    
    if(rotireDiagonala)
        unghiRotatie = saveUnghiRotatie;

    if((up || down || left || right))
        RefacePozitia(obj);

    if(nuDesena) {
        obj.rotatieX = 0;
        obj.rotatieY = 0;
        obj.rotatieZ = 0;
    }
            
    Deseneaza(obj);
}

//------------------------------------------- END OF ROTATION TOOL --------------------------------------------------------------

//----------------------------------------------- SCALING TOOL ------------------------------------------------------------------

void MaresteX(Obiect &obj) {
    obj.marimeX += coeficientMarire;

    for(int i = 0; i < obj.varfuri.size(); i++)
        if(obj.varfuri[i].x < 0)
            obj.varfuri[i].x = min(obj.varfuri[i].x - coeficientMarire, -0.0001);
        else
            obj.varfuri[i].x = max(obj.varfuri[i].x + coeficientMarire, 0.0001);
    
    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i].x = max(obj.axePunctSelectat[i].x + coeficientMarire, 0.0001);
}

void MaresteY(Obiect &obj) {
    obj.marimeY += coeficientMarire;

    for(int i = 0; i < obj.varfuri.size(); i++)
        if(obj.varfuri[i].y < 0)
            obj.varfuri[i].y = min(obj.varfuri[i].y - coeficientMarire, -0.0001);
        else
            obj.varfuri[i].y = max(obj.varfuri[i].y + coeficientMarire, 0.0001);

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i].y = max(obj.axePunctSelectat[i].y + coeficientMarire, 0.0001);
}

void MaresteZ(Obiect &obj) {
    obj.marimeZ += coeficientMarire;

    for(int i = 0; i < obj.varfuri.size(); i++)
        if(obj.varfuri[i].z < 0)
            obj.varfuri[i].z = min(obj.varfuri[i].z - coeficientMarire, -0.0001);
        else
            obj.varfuri[i].z = max(obj.varfuri[i].z + coeficientMarire, 0.0001);

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i].z = max(obj.axePunctSelectat[i].z + coeficientMarire, 0.0001);
}

void VerificareMarire(Obiect &obj) {
    if(!obj.activ)
        return;
    
    bool x = GetAsyncKeyState('X') & 0x8000;
    bool y = GetAsyncKeyState('Y') & 0x8000;
    bool z = GetAsyncKeyState('Z') & 0x8000;
    bool plus = GetAsyncKeyState(VK_ADD) & 0x8000;
    bool minus = GetAsyncKeyState(VK_SUBTRACT) & 0x8000;

    if((minus && plus) || !(x || y || z) || !(minus || plus)) {
        if(numarareMarire != 0) {
            clearStack(redo);

            Undo temp;
            temp.alegere = 3;
            temp.numarRotatii = numarareMarire;
            numarareMarire = 0;

            undo.push(temp);
        }

        return;
    }
    if(minus && ((x && obj.marimeX <= coeficientMarire) || (y && obj.marimeY <= coeficientMarire) || (z && obj.marimeZ <= coeficientMarire))) {
        if(numarareMarire != 0) {
            clearStack(redo);

            Undo temp;
            temp.alegere = 3;
            temp.numarRotatii = numarareMarire;
            numarareMarire = 0;

            undo.push(temp);
        }

        return;
    }
    
    EditareRotatie(obj, true);

    obiectCentrat = false;
    CentreazaObiect(obj);

    if(minus)
        coeficientMarire = -coeficientMarire;

    if(x) {
        MaresteX(obj);
        obj.stackMarire.push({'x', coeficientMarire});
        numarareMarire++;
    }
    if(y) {
        MaresteY(obj);
        obj.stackMarire.push({'y', coeficientMarire});
        numarareMarire++;
    }
    if(z) {
        MaresteZ(obj); 
        obj.stackMarire.push({'z', coeficientMarire});
        numarareMarire++;
    }

    RefacePozitia(obj);

    if(varfSelectat != -1) {
        for(int j = 0; j < 3; j++) {
                obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];
            }

            obj.axePunctSelectat[0].x += 0.5;
            obj.axePunctSelectat[1].y -= 0.5;
            obj.axePunctSelectat[2].z += 0.5;
    }

    EditareRotatie(obj, false);

    if(minus)
        coeficientMarire = -coeficientMarire;

    obj.centru = GetMijlocObiect(obj);
    obj.centruPentruAxe = obj.centru;
    
    Deseneaza(obj);
}

//-------------------------------------------- END OF SCALING TOOL --------------------------------------------------------------
