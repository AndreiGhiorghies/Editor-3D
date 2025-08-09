#include "../Headers/PoligonTools.h"
#include "../Headers/Structuri.h"
#include "../Headers/Utils.h"
#include "../Headers/Transformari.h"
#include "../Headers/Deseneaza.h"

#include <winbgim.h>
#include <math.h>
#include <algorithm>

void VerificaMiscareMousePeAxa(Obiect &obj, const int &alegere) {
    bool rotatieLocala = local;

    Undo temp;
    temp.alegere = 4;
    temp.axa = axaSelectata;
   
    if(alegere == 0) {
        if(selectarePuncte) {
            for(const int &i : puncteSelectate) {
                temp.coordonate.push_back({i, obj.varfuri[i].x});
                temp.coordonate.push_back({i, obj.varfuri[i].y});
                temp.coordonate.push_back({i, obj.varfuri[i].z});
            }
        }
        else {
            temp.coordonate.push_back({varfSelectat, obj.varfuri[varfSelectat].x});
            temp.coordonate.push_back({varfSelectat, obj.varfuri[varfSelectat].y});
            temp.coordonate.push_back({varfSelectat, obj.varfuri[varfSelectat].z});
        }
        
        for(int i = 0; i < 3; i++) {
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].x});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].y});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].z});
        }
    }
    else if(alegere == 1) {
        for(int i = 0; i < obj.varfuri.size(); i++) {
            temp.coordonate.push_back({i, obj.varfuri[i].x});
            temp.coordonate.push_back({i, obj.varfuri[i].y});
            temp.coordonate.push_back({i, obj.varfuri[i].z});
        }

        for(int i = 0; i < 3; i++) {
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].x});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].y});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].z});
        }
    }

    clearStack(redo);
    undo.push(temp);
    
    while (!ismouseclick(WM_LBUTTONUP)) {
        int mouseX = mousex();
        int mouseY = mousey();

        if(ultimaPozitieMouseX == mouseX && ultimaPozitieMouseY == mouseY)  
            continue;
            
        if(alegere == 0) {
            if(local)
                EditareRotatie(obj, true);
            
            if(selectarePuncte) {
                for(int i = 0; i < puncteSelectate.size(); i++) {
                    if (axaSelectata == 'x')
                        obj.varfuri[puncteSelectate[i]].x += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);
                    else if (axaSelectata == 'y')
                        obj.varfuri[puncteSelectate[i]].y += (mouseY - ultimaPozitieMouseY) / (double) (zoom - POV);
                    else if (axaSelectata == 'z')
                        obj.varfuri[puncteSelectate[i]].z += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);
                }

                if(axaSelectata == 'x')
                    for(int i = 0; i < 3; i++)
                        obj.axePunctSelectat[i].x += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);
                else if(axaSelectata == 'y')
                    for(int i = 0; i < 3; i++)
                        obj.axePunctSelectat[i].y += (mouseY - ultimaPozitieMouseY) / (double) (zoom - POV);
                else
                    for(int i = 0; i < 3; i++)
                        obj.axePunctSelectat[i].z += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);
            }
            else {
                if(axaSelectata == 'x') {
                    obj.varfuri[varfSelectat].x += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);

                    for(int i = 0; i < 3; i++)
                        obj.axePunctSelectat[i].x += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);
                } else if (axaSelectata == 'y') {
                    obj.varfuri[varfSelectat].y += (mouseY - ultimaPozitieMouseY) / (double) (zoom - POV);

                    for(int i = 0; i < 3; i++)
                        obj.axePunctSelectat[i].y += (mouseY - ultimaPozitieMouseY) / (double) (zoom - POV);     
                } else if (axaSelectata == 'z') {
                    obj.varfuri[varfSelectat].z += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);

                    for(int i = 0; i < 3; i++)
                        obj.axePunctSelectat[i].z += (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);
                }
            }

            if(local)
                EditareRotatie(obj, false);
        }
        else if(alegere == 1) {
            int saveCoeficient = coeficientDeplasare;
            coeficientDeplasare = (mouseX - ultimaPozitieMouseX) / (double) (zoom - POV);

            if(local)
                EditareRotatie(obj, true);

            if(axaSelectata == 'x')
                DeplaseazaX(obj);
            else if(axaSelectata == 'y')
                DeplaseazaY(obj);
            else if(axaSelectata == 'z')
                DeplaseazaZ(obj);
                
            if(local)
                EditareRotatie(obj, false);
                
            coeficientDeplasare = saveCoeficient;
        }

        obj.centru = GetMijlocObiect(obj);

        EditareRotatie(obj, true);

        obj.axaOX = obj.centru;
        obj.axaOY = obj.centru;
        obj.axaOZ = obj.centru;

        obj.axaOX.x += 0.5;
        obj.axaOY.y -= 0.5;
        obj.axaOZ.z += 0.5;

        EditareRotatie(obj, false);

        Deseneaza(obj);

        ultimaPozitieMouseX = mouseX;
        ultimaPozitieMouseY = mouseY;
    }

    axaSelectata = '\0';
}

bool esteAproapeDeLinie(const Punct2D &start, const Punct2D &end, const int &px, const int &py, const int &toleranta) {
    float numarator = abs((end.x - start.x) * (start.y - py) - (start.x - px) * (end.y - start.y));
    float numitor = sqrt(pow(end.x - start.x, 2) + pow(end.y - start.y, 2));

    float distanta = numarator / numitor;

    return distanta <= toleranta;
}

bool VerificaMousePeAxa(Obiect &obj, const int &mouseX, const int &mouseY) {
    mouseApasat = false;
    ultimaPozitieMouseX = mouseX;
    ultimaPozitieMouseY = mouseY;

    int toleranta = 3, alegere = 0, varf = varfSelectat;
    Punct2D varfSelectat2D = {0, 0};
    if(varf != -1)
        varfSelectat2D = Transforma2D(obj.varfuri[varfSelectat]);
    Punct2D centruObiect = Transforma2D(obj.centru);
    Punct2D varf2D;

    if(varf != -1 && static_cast<int>(puncteSelectate.size()) > 0)
        varf = puncteSelectate[static_cast<int>(puncteSelectate.size()) - 1];
    
    if(varf != -1)
        varf2D = Transforma2D(obj.varfuri[varf]);
    
    if(!local) {
        if(varf != -1 && esteAproapeDeLinie(varf2D, Transforma2D({obj.varfuri[varf].x + 0.5, obj.varfuri[varf].y, obj.varfuri[varf].z}), mouseX, mouseY, toleranta))
            axaSelectata = 'x';
        else if(varf != -1 && esteAproapeDeLinie(varf2D, Transforma2D({obj.varfuri[varf].x, obj.varfuri[varf].y - 0.5, obj.varfuri[varf].z}), mouseX, mouseY, toleranta))
            axaSelectata = 'y';
        else if(varf != -1 && esteAproapeDeLinie(varf2D, Transforma2D({obj.varfuri[varf].x + 0.25, obj.varfuri[varf].y - 0.25, obj.varfuri[varf].z}), mouseX, mouseY, toleranta))
            axaSelectata = 'z';
        else if(esteAproapeDeLinie(centruObiect, Transforma2D({obj.centru.x + 0.5, obj.centru.y, obj.centru.z}), mouseX, mouseY, toleranta)) {
            axaSelectata = 'x';
            alegere = 1;
        }
        else if(esteAproapeDeLinie(centruObiect, Transforma2D({obj.centru.x, obj.centru.y - 0.5, obj.centru.z}), mouseX, mouseY, toleranta)) {
            axaSelectata = 'y';
            alegere = 1;
        }
        else if(esteAproapeDeLinie(centruObiect, Transforma2D({obj.centru.x + 0.25, obj.centru.y - 0.25, obj.centru.z}), mouseX, mouseY, toleranta)) {
            axaSelectata = 'z';
            alegere = 1;
        }
        else
            return false;
    }
    else {
        if(esteAproapeDeLinie(varfSelectat2D, Transforma2D(obj.axePunctSelectat[0]), mouseX, mouseY, toleranta))
            axaSelectata = 'x';
        else if(esteAproapeDeLinie(varfSelectat2D, Transforma2D(obj.axePunctSelectat[1]), mouseX, mouseY, toleranta))
            axaSelectata = 'y';
        else if(esteAproapeDeLinie(varfSelectat2D, Transforma2D(obj.axePunctSelectat[2]), mouseX, mouseY, toleranta))
            axaSelectata = 'z';
        else if(esteAproapeDeLinie(centruObiect, Transforma2D(obj.axaOX), mouseX, mouseY, toleranta)) {
            axaSelectata = 'x';
            alegere = 1;
        }
        else if(esteAproapeDeLinie(centruObiect, Transforma2D(obj.axaOY), mouseX, mouseY, toleranta)) {
            axaSelectata = 'y';
            alegere = 1;
        }
        else if(esteAproapeDeLinie(centruObiect, Transforma2D(obj.axaOZ), mouseX, mouseY, toleranta)) {
            axaSelectata = 'z';
            alegere = 1;
        }
        else
            return false;
    }

    VerificaMiscareMousePeAxa(obj, alegere);

    return true;
}

bool estePunctApropiat(const Punct2D &punct, const Punct2D &mouse) {
    return sqrt(pow(mouse.x - punct.x, 2) + pow(mouse.y - punct.y, 2)) <= razaPunct * 2;
}

void UnestePuncte(Obiect &obj) {
    while (!ismouseclick(WM_LBUTTONUP)) {
        int mouseX = mousex();
        int mouseY = mousey();

        if(ultimaPozitieMouseX == mouseX && ultimaPozitieMouseY == mouseY)  
            continue;
        
        pozitieMouseUnirePuncte = {static_cast<double>(mouseX), static_cast<double>(mouseY)};

        for(int i = 0; i < obj.varfuri.size(); i++)
            if(estePunctApropiat(Transforma2D(obj.varfuri[i]), pozitieMouseUnirePuncte))
                pozitieMouseUnirePuncte = Transforma2D(obj.varfuri[i]);
        
        Deseneaza(obj);

        ultimaPozitieMouseX = mouseX;
        ultimaPozitieMouseY = mouseY;
    }

    for(int i = 0; i < obj.varfuri.size(); i++)
        if(estePunctApropiat(Transforma2D(obj.varfuri[i]), pozitieMouseUnirePuncte)) {
            bool ok = true;

            for(int j = 0; j < obj.muchii.size(); j++)
                if((i == obj.muchii[j].first && varfSelectat == obj.muchii[j].second) || (i == obj.muchii[j].second && varfSelectat == obj.muchii[j].first)) {
                    ok = false;
                    break;
                }
            
            if(ok) {
                obj.muchii.push_back({varfSelectat, i});

                clearStack(redo);

                Undo temp;
                temp.alegere = 6;
                temp.numarRotatii = 1;

                undo.push(temp);

                break;
            }
        }
    
    varfSelectat = -1;
        
    Deseneaza(obj);

    clearmouseclick(WM_LBUTTONUP);
}

void AdaugaPunct(Obiect &obj) {
    if(!deseneazaPuncte || !ismouseclick(WM_LBUTTONDOWN) || !((GetAsyncKeyState(VK_LCONTROL) & 0x8000) || adaugaPunct) || (fereastraDreapta && mousex() >= lungimeFereastra - 250) || mousey() <= inaltimeFereastra / 35 || (fereastraStanga && mousex() <= 140))
        return;
    
    obj.varfuri.push_back({((double) mousex() - lungimeFereastra / 2) / zoom, ((double) mousey() - inaltimeFereastra / 2) / zoom, 0});

    Undo temp;
    clearStack(redo);
    temp.alegere = 5;
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

    Deseneaza(obj);

    clearmouseclick(WM_LBUTTONDOWN);
}

void EliminaPunct(Obiect &obj) {
    Undo temp;
    temp.alegere = 7;
    temp.numarRotatii = varfSelectat;
    temp.puncteEliminat = obj.varfuri[varfSelectat];

    obj.varfuri.erase(obj.varfuri.begin() + varfSelectat);
    int nrEliminariFete = 0;

    int ok;
    for(int i = 0; i < obj.fete.size(); i++){
        ok = 0;

        for(int j : obj.fete[i])
            if(j == varfSelectat) {
                for(int k = 0; k < obj.indexFata.size(); k++)
                    if(obj.indexFata[k] == i) {
                        temp.indexFete.insert(temp.indexFete.begin(), {k, i});
                        obj.indexFata.erase(obj.indexFata.begin() + k);

                        k--;
                    }
                    else if(obj.indexFata[k] > i)
                            obj.indexFata[k]--;

                temp.fete.push_back(obj.fete[i]);
                obj.fete.erase(obj.fete.begin() + i);
                temp.index.push_back(i + nrEliminariFete);
                temp.culoareFete.push_back(obj.culoareFete[i]);
                obj.culoareFete.erase(obj.culoareFete.begin() + i);

                i--;
                nrEliminariFete++;
                ok = 1;

                break;
            }

            if(!ok)
                for(int &j:obj.fete[i])
                     if(j > varfSelectat)
                        j--;
    }

    nrEliminariFete = 0;

    for(int i = 0; i < obj.muchii.size(); i++)
        if(obj.muchii[i].first == varfSelectat || obj.muchii[i].second == varfSelectat) {
            obj.muchii.erase(obj.muchii.begin() + i);
            temp.coordonate.push_back({obj.muchii[i].first, obj.muchii[i].second});
            temp.index.push_back(i + nrEliminariFete);

            nrEliminariFete++;
            i--;
        }
        else { 
            if(obj.muchii[i].first > varfSelectat)
                obj.muchii[i].first--;
            if(obj.muchii[i].second > varfSelectat)
                obj.muchii[i].second--;
        }

    varfSelectat = -1;
    //puncteSelectate.clear();

    clearStack(redo);
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
    
    Deseneaza(obj);
}

void SorteazaFetele(Obiect &obj) {
    if(static_cast<int>(obj.fete.size()) == 0)
        return;
    
    vector<double> Zmedie(static_cast<int>(obj.fete.size()));

    for (int i = 0; i < obj.fete.size(); i++) {
        double sumaZ = 0;

        for (const int &j : obj.fete[i])
            sumaZ += obj.varfuri[j].z;
        
        Zmedie[i] = (double) sumaZ / static_cast<double>(obj.fete.size());
    }
    
    bool ok;

    do {
        ok = true;

        for(int i = 0; i < obj.fete.size() - 1; i++) {
            if(Zmedie[i] < Zmedie[i + 1]) {
                swap(Zmedie[i], Zmedie[i + 1]);
                swap(obj.fete[i], obj.fete[i + 1]);
                swap(obj.culoareFete[i], obj.culoareFete[i + 1]);

                int firstIndex, secondIndex;
                for(int j = 0; j < obj.indexFata.size(); j++)
                    if(obj.indexFata[j] == i)
                        firstIndex = j;
                    else if(obj.indexFata[j] == i + 1)
                            secondIndex = j;
                
                swap(obj.indexFata[firstIndex], obj.indexFata[secondIndex]);
                
                if(fataSelectata == i)
                    fataSelectata = i + 1;
                else if(fataSelectata == i + 1)
                    fataSelectata = i;
                
                ok = false;
            }
        }
    }while(!ok);
}

void CrearePoligon(Obiect &obj) {
    if(!selectarePuncte || !deseneazaPuncte)
        return;
    
    if(ismouseclick(WM_LBUTTONDOWN)) {
        int x = mousex();
        if((fereastraDreapta && x >= lungimeFereastra - 250) || mousey() <= inaltimeFereastra / 35)
            return;
        
        bool ok = false;
        for(int i = 0; i < obj.varfuri.size(); i++)
            if(estePunctApropiat(Transforma2D(obj.varfuri[i]), {(double) mousex(), (double) mousey()})) {
                ok = true;

                if(find(puncteSelectate.begin(), puncteSelectate.end(), i) == puncteSelectate.end())
                    puncteSelectate.push_back(i);
                else
                    puncteSelectate.erase(find(puncteSelectate.begin(), puncteSelectate.end(), i));
                
                if(puncteSelectate.size() > 0) {
                    varfSelectat = puncteSelectate[puncteSelectate.size() - 1];

                    EditareRotatie(obj, true);

                    for(int j = 0; j < 3; j++)
                        obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];

                    obj.axePunctSelectat[0].x += 0.5;
                    obj.axePunctSelectat[1].y -= 0.5;
                    obj.axePunctSelectat[2].z += 0.5;

                    EditareRotatie(obj, false);
                }
                else
                    varfSelectat = -1;

                Deseneaza(obj);
            }
        
        if(ok)
            clearmouseclick(WM_LBUTTONDOWN);    
    }
}
