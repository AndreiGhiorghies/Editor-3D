#include "../Headers/UndoRedo.h"
#include "../Headers/Utils.h"
#include "../Headers/Transformari.h"
#include "../Headers/Deseneaza.h"
#include "../Headers/PoligonTools.h"

#include <winbgim.h>

void UndoChange(Obiect &obj, const bool &skip) {
    if(((!GetAsyncKeyState(VK_CONTROL) || !GetAsyncKeyState('Z')) && !skip) || undo.empty())
        return;

    int alegere = undo.top().alegere, saveLocal = local;
    local = false;

    if(alegere == 1) {
        int nrRotatii = undo.top().numarRotatii;
        double saveUnghiRotatie = unghiRotatie;

        redo.push(undo.top());
        CentreazaObiect(obj);

        while(nrRotatii--) {
            unghiRotatie = -obj.rotatiiAnterioare.top().second;
            obj.stackRedoRotatie.push(obj.rotatiiAnterioare.top());

            if(undo.top().axa == 'g')
                undoRotatieGrid = true;
            
            if(obj.rotatiiAnterioare.top().first == 'x')
                RotesteObiectX(obj);
            else if(obj.rotatiiAnterioare.top().first == 'y')
                RotesteObiectY(obj);
            else
                RotesteObiectZ(obj);
            
            obj.rotatiiAnterioare.pop();
            undoRotatieGrid = false;
        }

        unghiRotatie = saveUnghiRotatie;

        RefacePozitia(obj);
    }
    else if(alegere == 2) {
        int nrDeplasari = undo.top().numarRotatii;
        double saveCoeficientDeplasare = coeficientDeplasare;
        redo.push(undo.top());

        if(undo.top().local) 
            EditareRotatie(obj, true);
        
        while(nrDeplasari--) {
            coeficientDeplasare = -obj.stackDeplasare.top().second;
            obj.stackRedoDeplasare.push(obj.stackDeplasare.top());

            if(obj.stackDeplasare.top().first == 'x')
                DeplaseazaX(obj);
            else if(obj.stackDeplasare.top().first == 'y')
                DeplaseazaY(obj);
            else
                DeplaseazaZ(obj);
            
            obj.stackDeplasare.pop();
        }

        if(undo.top().local) 
            EditareRotatie(obj, false);
        
        coeficientDeplasare = saveCoeficientDeplasare;
        obj.centru = GetMijlocObiect(obj);
        obj.centruPentruAxe = obj.centru;
    }
    else if(alegere == 3) {
        int nrMariri = undo.top().numarRotatii;
        double saveCoeficientMarire = coeficientMarire;
        redo.push(undo.top());

        EditareRotatie(obj, true);
        CentreazaObiect(obj);

        while(nrMariri--) {
            coeficientMarire = -obj.stackMarire.top().second;
            obj.stackRedoMarire.push(obj.stackMarire.top());

            if(obj.stackMarire.top().first == 'x')
                MaresteX(obj);
            else if(obj.stackMarire.top().first == 'y')
                MaresteY(obj);
            else
                MaresteZ(obj);
            
            obj.stackMarire.pop();
        }

        coeficientMarire = saveCoeficientMarire;
        
        EditareRotatie(obj, false);

        obj.centru = GetMijlocObiect(obj);
        obj.centruPentruAxe = obj.centru;
    }
    else if(alegere == 4) {
        char axa = undo.top().axa;
        Undo temp;
        temp.alegere = 4;
        temp.axa = axa;

        for(int i = 0; i < (int) undo.top().coordonate.size() - 9; i++) {
            temp.coordonate.push_back({undo.top().coordonate[i].first, obj.varfuri[undo.top().coordonate[i].first].x});
            obj.varfuri[undo.top().coordonate[i].first].x = undo.top().coordonate[i].second;
            i++;

            temp.coordonate.push_back({undo.top().coordonate[i].first, obj.varfuri[undo.top().coordonate[i].first].y});
            obj.varfuri[undo.top().coordonate[i].first].y = undo.top().coordonate[i].second;
            i++;

            temp.coordonate.push_back({undo.top().coordonate[i].first, obj.varfuri[undo.top().coordonate[i].first].z});
            obj.varfuri[undo.top().coordonate[i].first].z = undo.top().coordonate[i].second;
        }

        for(int i = 0; i < 3; i++) {
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].x});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].y});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].z});
        }

        for(int i = 0; i < 9; i += 3) {
            obj.axePunctSelectat[i / 3] = {undo.top().coordonate[undo.top().coordonate.size() - 9 + i].second, 
            undo.top().coordonate[undo.top().coordonate.size() - 8 + i].second, undo.top().coordonate[undo.top().coordonate.size() - 7 + i].second};
        }

        redo.push(temp);
        obj.centru = GetMijlocObiect(obj);
        EditareRotatie(obj, true);

        obj.axaOX = obj.centru;
        obj.axaOY = obj.centru;
        obj.axaOZ = obj.centru;
        obj.axaOX.x += 0.5;
        obj.axaOY.y -= 0.5;
        obj.axaOZ.z += 0.5;

        EditareRotatie(obj, false);
    }
    else if(alegere == 5) {
        Undo temp;
        temp.alegere = 5;
        temp.puncteEliminat = obj.varfuri[obj.varfuri.size() - 1];
        redo.push(temp);
        obj.varfuri.pop_back();

        if(obj.varfuri.size() > 0) {
            obj.centru = GetMijlocObiect(obj);
            EditareRotatie(obj, true);

            obj.axaOX = obj.centru;
            obj.axaOY = obj.centru;
            obj.axaOZ = obj.centru;
            obj.axaOX.x += 0.5;
            obj.axaOY.y -= 0.5;
            obj.axaOZ.z += 0.5;

            EditareRotatie(obj, false);
        }
    }
    else if(alegere == 6) {
        int nr = undo.top().numarRotatii;
        Undo temp;
        temp.alegere = 6;
        temp.numarRotatii = nr;

        while(nr--) {
            temp.coordonate.push_back({obj.muchii[obj.muchii.size() - 1].first, obj.muchii[obj.muchii.size() - 1].second});
            obj.muchii.pop_back();
        }

        redo.push(temp);
    }
    else if(alegere == 7) {
        int index = undo.top().numarRotatii;
        int k = 0;

        Undo temp;
        temp.alegere = 7;
        temp.numarRotatii = index;
        redo.push(temp);
        obj.varfuri.insert(obj.varfuri.begin() + index, undo.top().puncteEliminat);

        for(auto &i : obj.fete)
            for(int &j : i)
                if(j >= index)
                    j++;
        
        for(pair<int, int> &i : obj.muchii) {
            if(i.first >= index)
                i.first++;
            if(i.second >= index)
                i.second++;
        }

        for(const auto &i : undo.top().fete) {
            obj.fete.insert(obj.fete.begin() + undo.top().index[k], i);
            obj.culoareFete.insert(obj.culoareFete.begin() + undo.top().index[k], undo.top().culoareFete[k]);
            k++;
        }

        for(const auto &i : undo.top().coordonate) {
            obj.muchii.insert(obj.muchii.begin() + undo.top().index[k++], {i.first, i.second});
        }

        for(const auto &i : undo.top().indexFete) {
            for(auto &j : obj.indexFata)
                if(j >= i.second)
                    j++;
            
            obj.indexFata.insert(obj.indexFata.begin() + i.first, i.second);
        }
    }
    else if(alegere == 8) {
        for(int i = 0; i < obj.fete.size(); i++)
            if(obj.fete[i] == undo.top().fete[0]) {
                Undo temp;
                temp.alegere = 8;
                temp.fete.push_back(obj.fete[i]);
                temp.culoareFete.push_back(obj.culoareFete[i]);

                redo.push(temp);
                obj.fete.erase(obj.fete.begin() + i);
                obj.culoareFete.erase(obj.culoareFete.begin() + i);

                break;
            }
        
        fataSelectata = -1;
        for(int i = 0; i < obj.indexFata.size(); i++)
            if(static_cast<int>(obj.indexFata.size()) - 1 == obj.indexFata[i]) {
                obj.indexFata.erase(obj.indexFata.begin() + i);

                break;
            }
        
    }
    else if(alegere == 9) {
        for(int i = 0; i < obj.fete.size(); i++)
            if(obj.fete[i] == undo.top().fete[0]) {
                Undo temp;
                temp.alegere = 9;
                temp.fete.push_back(obj.fete[i]);
                temp.index = {obj.culoareFete[i][0], obj.culoareFete[i][1], obj.culoareFete[i][2]};

                redo.push(temp);
                obj.culoareFete[i] = {undo.top().index[0], undo.top().index[1], undo.top().index[2]};

                break;
            }
    }

    undo.pop();

    local = saveLocal;

    Deseneaza(obj);

    delay(200);
}

void RedoChange(Obiect &obj, const bool &skip) {
    if(((!GetAsyncKeyState(VK_CONTROL) || !GetAsyncKeyState('Y')) && !skip) || redo.empty())
        return;
    
    int alegere = redo.top().alegere, saveLocal = local;
    local = false;

    if(alegere == 1) {
        int nrRotatii = redo.top().numarRotatii;
        double saveUnghiRotatie = unghiRotatie;

        CentreazaObiect(obj);
        undo.push(redo.top());

        while(nrRotatii--) {
            char axa = obj.stackRedoRotatie.top().first;
            unghiRotatie = obj.stackRedoRotatie.top().second;

            if(redo.top().axa == 'g')
                undoRotatieGrid = true;
            obj.rotatiiAnterioare.push(obj.stackRedoRotatie.top());

            if(axa == 'x')
                RotesteObiectX(obj);
            else if(axa == 'y')
                RotesteObiectY(obj);
            else
                RotesteObiectZ(obj);
            
            obj.stackRedoRotatie.pop();
            undoRotatieGrid = false;
        }

        unghiRotatie = saveUnghiRotatie;
        RefacePozitia(obj);
    }
    else if(alegere == 2) {
        int nrDeplasari = redo.top().numarRotatii;
        double saveCoeficientDeplasare = coeficientDeplasare;
        undo.push(redo.top());

        if(redo.top().local) 
            EditareRotatie(obj, true);
        
        while(nrDeplasari--) {
            coeficientDeplasare = obj.stackRedoDeplasare.top().second;
            obj.stackDeplasare.push(obj.stackRedoDeplasare.top());

            if(obj.stackDeplasare.top().first == 'x')
                DeplaseazaX(obj);
            else if(obj.stackDeplasare.top().first == 'y')
                DeplaseazaY(obj);
            else
                DeplaseazaZ(obj);
            
            obj.stackRedoDeplasare.pop();
        }

        if(redo.top().local) 
            EditareRotatie(obj, false);
        
        coeficientDeplasare = saveCoeficientDeplasare;
        obj.centru = GetMijlocObiect(obj);
        obj.centruPentruAxe = obj.centru;
    }
    else if(alegere == 3) {
        int nrMariri = redo.top().numarRotatii;
        double saveCoeficientMarire = coeficientMarire;
        undo.push(redo.top());

        EditareRotatie(obj, true);
        CentreazaObiect(obj);

        while(nrMariri--) {
            coeficientMarire = obj.stackRedoMarire.top().second;
            obj.stackMarire.push(obj.stackRedoMarire.top());

            if(obj.stackMarire.top().first == 'x')
                MaresteX(obj);
            else if(obj.stackMarire.top().first == 'y')
                MaresteY(obj);
            else
                MaresteZ(obj);

            obj.stackRedoMarire.pop();
        }

        coeficientMarire = saveCoeficientMarire;
        
        EditareRotatie(obj, false);
        obj.centru = GetMijlocObiect(obj);
        obj.centruPentruAxe = obj.centru;
    }
    else if(alegere == 4) {
        char axa = redo.top().axa;
        Undo temp;
        temp.alegere = 4;
        temp.axa = axa;

        for(int i = 0; i < redo.top().coordonate.size() - 9; i++) {
            temp.coordonate.push_back({redo.top().coordonate[i].first, obj.varfuri[redo.top().coordonate[i].first].x});
            obj.varfuri[redo.top().coordonate[i].first].x = redo.top().coordonate[i].second;
            i++;

            temp.coordonate.push_back({redo.top().coordonate[i].first, obj.varfuri[redo.top().coordonate[i].first].y});
            obj.varfuri[redo.top().coordonate[i].first].y = redo.top().coordonate[i].second;
            i++;

            temp.coordonate.push_back({redo.top().coordonate[i].first, obj.varfuri[redo.top().coordonate[i].first].z});
            obj.varfuri[redo.top().coordonate[i].first].z = redo.top().coordonate[i].second;
        }
        
        for(int i = 0; i < 3; i++) {
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].x});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].y});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].z});
        }

        for(int i = 0; i < 9; i += 3) {
            obj.axePunctSelectat[i / 3] = {redo.top().coordonate[redo.top().coordonate.size() - 9 + i].second, 
            redo.top().coordonate[redo.top().coordonate.size() - 8 + i].second, redo.top().coordonate[redo.top().coordonate.size() - 7 + i].second};
        }

        undo.push(temp);

        obj.centru = GetMijlocObiect(obj);
        EditareRotatie(obj, true);

        obj.axaOX = obj.centru;
        obj.axaOY = obj.centru;
        obj.axaOZ = obj.centru;
        obj.axaOX.x += 0.5;
        obj.axaOY.y -= 0.5;
        obj.axaOZ.z += 0.5;

        EditareRotatie(obj, false);
    }
    else if(alegere == 5) {
        Undo temp;
        temp.alegere = 5;
        undo.push(temp);
        obj.varfuri.push_back(redo.top().puncteEliminat);

        obj.centru = GetMijlocObiect(obj);
        EditareRotatie(obj, true);

        obj.axaOX = obj.centru;
        obj.axaOY = obj.centru;
        obj.axaOZ = obj.centru;
        obj.axaOX.x += 0.5;
        obj.axaOY.y -= 0.5;
        obj.axaOZ.z += 0.5;
        
        EditareRotatie(obj, false);
    }
    else if(alegere == 6) {
        int nr = redo.top().numarRotatii;
        int k = 0;
        Undo temp;
        temp.alegere = 6;
        temp.numarRotatii = nr;

        while(nr--) {
            obj.muchii.push_back({redo.top().coordonate[k].first, redo.top().coordonate[k++].second});
        }

        undo.push(temp);
    }
    else if(alegere == 7) {
        int index = redo.top().numarRotatii;
        int saveVarf = varfSelectat;

        varfSelectat = index;
        modificaPagina = false;

        EliminaPunct(obj);

        varfSelectat = saveVarf;
        modificaPagina = true;
    }
    else if(alegere == 8) {
        Undo temp;
        temp.alegere = 8;
        temp.fete.push_back(redo.top().fete[0]);

        undo.push(temp);
        obj.fete.push_back(redo.top().fete[0]);
        obj.culoareFete.push_back(redo.top().culoareFete[0]);
        obj.indexFata.push_back((int) obj.indexFata.size());
    }
    else if(alegere == 9) {
        for(int i = 0; i < obj.fete.size(); i++)
            if(obj.fete[i] == redo.top().fete[0]) {
                Undo temp;
                temp.alegere = 9;
                temp.fete.push_back(obj.fete[i]);
                temp.index = {obj.culoareFete[i][0], obj.culoareFete[i][1], obj.culoareFete[i][2]};

                undo.push(temp);
                obj.culoareFete[i] = {redo.top().index[0], redo.top().index[1], redo.top().index[2]};

                break;
            }
    }

    redo.pop();

    local = saveLocal;

    Deseneaza(obj);
    delay(200);
}
