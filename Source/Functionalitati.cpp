#include "../Headers/Functionalitati.h"
#include "../Headers/Transformari.h"
#include "../Headers/PoligonTools.h"
#include "../Headers/Model_data.h"
#include "../Headers/Deseneaza.h"
#include "../Headers/UndoRedo.h"
#include "../Headers/Fisiere.h"
#include "../Headers/Utils.h"

#include <graphics.h>
#include <algorithm>
#include <math.h>

void displayText(char* text, const int &x1, const int &y1, const int &x2, const int &y2) {
    setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
    bar(x1 + 1, y1 + 1, x2 - 1, y2 - 1);

    setbkcolor(COLOR(70, 70, 70));
    setcolor(WHITE);

    int boxWidth = x2 - x1;
    int boxHeight = y2 - y1;

    int textWidth = textwidth(text);
    int textHeight = textheight((char*) "A");

    int startX = x1 + (boxWidth - textWidth) / 2;
    int startY = y1 + (boxHeight - textHeight) / 2;

    outtextxy(startX, startY, text);
}

void displayCursor(const int &cursorPos, char* text, const int &x1, const int &y1, const int &x2, const int &y2, const bool &showCursor) {
    int boxWidth = x2 - x1;
    int boxHeight = y2 - y1;

    int textWidth = textwidth(text);
    int textHeight = textheight((char*) "A");

    int startX = x1 + (boxWidth - textWidth) / 2;
    int startY = y1 + (boxHeight - textHeight) / 2;

    int cursorX = startX + textwidth(text) - textwidth(text + cursorPos);
    int cursorY = startY;

    if (showCursor) {
        line(cursorX, cursorY, cursorX, cursorY + textHeight);
    }
    else {
        setcolor(COLOR(70, 70, 70));
        line(cursorX, cursorY, cursorX, cursorY + textHeight);
        setcolor(WHITE);
    }
}

bool isValidCharacter(char &ch, const char* input, const int &cursorPos) {
    ch = '#';
    for(int i = 0; i < 10; i++)
        if((GetAsyncKeyState('0' + i) & 0x8000)) {
            ch = '0' + i;
            break;
        }
    
    if((selectareInput >= 11 && selectareInput <= 13) || (selectareInput >= 22 && selectareInput <= 24) || (selectareInput >= 26 && selectareInput <= 28) || (selectareInput >= 30 && selectareInput <= 32)) {
        if(ch < '0' || ch > '9')
            return false;
        
        string s = string(input);
        s.insert(cursorPos, string(1, ch));

        return stoi(s) <= 255;
    }

    if (ch >= '0' && ch <= '9')
        return true;

    if ((GetAsyncKeyState(VK_OEM_MINUS) & 0x8000) && cursorPos == 0 && strchr(input, '-') == nullptr) {
        ch = '-';
        return true;
    }

    if ((GetAsyncKeyState(VK_OEM_PERIOD) & 0x8000) && strchr(input, '.') == nullptr) {
        ch = '.';
        return true;
    }

    return false;
}

void getInputWithCursor(char input[20], const int &maxLength, const int &x1, const int &y1, const int &x2, const int &y2, Obiect &obj, const int &selectie) {
    int cursorPos = strlen(input);

    clearmouseclick(WM_LBUTTONDOWN);

    bool showCursor = true;
    clock_t lastToggleTime = clock();
    double ultimaLocatie = 0;
    if(varfSelectat != -1)
        ultimaLocatie = obj.varfuri[varfSelectat].x;
    modificaPagina = false;

    if(selectie == 0) {
        Undo temp;
        temp.alegere = 4;
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
        
        if(selectareInput == 0)
            temp.axa = 'x';
        else if(selectareInput == 1)
            temp.axa = 'y';
        else
            temp.axa = 'z';
        
        for(int i = 0; i < 3; i++) {
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].x});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].y});
            temp.coordonate.push_back({-1, obj.axePunctSelectat[i].z});
        }
        
        clearStack(redo);
        undo.push(temp);
    }
    else if(selectie == 4) {
        Undo temp;
        temp.alegere = 9;
        temp.index = vector<int>(3);
        temp.fete.push_back(obj.fete[fataSelectata]);
        temp.index[0] = obj.culoareFete[fataSelectata][0];
        temp.index[1] = obj.culoareFete[fataSelectata][1];
        temp.index[2] = obj.culoareFete[fataSelectata][2];

        clearStack(redo);
        undo.push(temp);
    }

    int salvareDimensiuneRotatii = static_cast<int>(obj.rotatiiAnterioare.size());
    int salvareDimensiuneDeplasari = static_cast<int>(obj.stackDeplasare.size());
    int salvareDimensiuneMarimi = static_cast<int>(obj.stackMarire.size());

    displayCursor(cursorPos, input, x1, y1, x2, y2, true);

    while (true) {
        if ((clock() - lastToggleTime) > 500) {
            showCursor = !showCursor;
            lastToggleTime = clock();
            displayCursor(cursorPos, input, x1, y1, x2, y2, showCursor);
        }

        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            delay(100);
            break;
        }

        if(ismouseclick(WM_LBUTTONDOWN)) {
            int x = mousex(), y = mousey();
            if(!(x >= x1 && y >= y1 && x <= x2 && y <= y2)) {
                clearmouseclick(WM_LBUTTONDOWN);
                break;
            }

            clearmouseclick(WM_LBUTTONDOWN);
        }
        else if ((GetAsyncKeyState(VK_BACK) & 0x8000) && cursorPos > 0) {
            memmove(input + cursorPos - 1, input + cursorPos, strlen(input) - cursorPos + 1);
            cursorPos--;

            string s = string(input);
            if(s.length() == 0)
                s = "0";
            else if(s.length() <= 1 && (s[0] == '-' || s[0] == '.'))
                s = "0";
            else if(s.length() == 2 && (s == ".-" || s == "-."))
                s = "0";
            else if(s.length() >= 2 && s[0] == '-' && s[1] == '.')
                s.insert(1, "0");
            
            if(selectie == 0) {
                if(puncteSelectate.size() > 0) {
                    for(int i = 0; i < puncteSelectate.size(); i++) {
                        if(selectareInput % 3 == 0)
                            obj.varfuri[puncteSelectate[i]].x = stod(s) / 10;
                        else if(selectareInput % 3 == 1)
                            obj.varfuri[puncteSelectate[i]].y = -stod(s) / 10;
                        else
                            obj.varfuri[puncteSelectate[i]].z = stod(s) / 10;
                    }
                }
                else if(varfSelectat != -1) {
                    if(selectareInput % 3 == 0) {
                        obj.varfuri[varfSelectat].x = stod(s) / 10;
                    }
                    else if(selectareInput % 3 == 1)
                        obj.varfuri[varfSelectat].y = -stod(s) / 10;
                    else
                        obj.varfuri[varfSelectat].z = stod(s) / 10;
                }

                obj.centru = GetMijlocObiect(obj);
                EditareRotatie(obj, true);

                for(int j = 0; j < 3; j++)
                    obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];

                obj.axePunctSelectat[0].x += 0.5;
                obj.axePunctSelectat[1].y -= 0.5;
                obj.axePunctSelectat[2].z += 0.5;
                
                obj.axaOX = obj.centru;
                obj.axaOY = obj.centru;
                obj.axaOZ = obj.centru;
                obj.axaOX.x += 0.5;
                obj.axaOY.y -= 0.5;
                obj.axaOZ.z += 0.5;

                EditareRotatie(obj, false);
            }
            else if(selectie == 1) {
                if(selectareInput == 11)
                    culoarePuncteSelectate[0] = stoi(s);
                else if(selectareInput == 12)
                    culoarePuncteSelectate[1] = stoi(s);
                else
                    culoarePuncteSelectate[2] = stoi(s);
            }
            else if(selectie == 2) {
                if(selectareInput == 22)
                    culoarePuncte[0] = stoi(s);
                else if(selectareInput == 23)
                    culoarePuncte[1] = stoi(s);
                else
                    culoarePuncte[2] = stoi(s);
            }
            else if(selectie == 3) {
                if(selectareInput == 26)
                    culoareMuchii[0] = stoi(s);
                else if(selectareInput == 27)
                    culoareMuchii[1] = stoi(s);
                else
                    culoareMuchii[2] = stoi(s);
            }
            else if(selectie == 4) {
                if(selectareInput == 30)
                    obj.culoareFete[fataSelectata][0] = stoi(s);
                else if(selectareInput == 31)
                    obj.culoareFete[fataSelectata][1] = stoi(s);
                else
                    obj.culoareFete[fataSelectata][2] = stoi(s);
            }
            else if(selectie == 5) {
                if(local)
                    EditareRotatie(obj, true);
                
                Punct3D centruNou = obj.centru;

                if(selectareInput == 37)
                    centruNou.x = stod(s) / 10;
                else if(selectareInput == 38)
                    centruNou.y = -stod(s) / 10;
                else
                    centruNou.z = stod(s) / 10;
                
                for(auto &j : obj.varfuri) {
                    j.x += centruNou.x - obj.centru.x;
                    j.y += centruNou.y - obj.centru.y;
                    j.z += centruNou.z - obj.centru.z;
                }

                if(selectareInput == 37)
                    obj.stackDeplasare.push({'x', centruNou.x - obj.centru.x});
                else if(selectareInput == 38)
                    obj.stackDeplasare.push({'y', centruNou.y - obj.centru.y});
                else
                    obj.stackDeplasare.push({'z', centruNou.z - obj.centru.z});

                obj.centru = centruNou;

                if(varfSelectat != -1) {
                    for(int j = 0; j < 3; j++)
                        obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];

                    obj.axePunctSelectat[0].x += 0.5;
                    obj.axePunctSelectat[1].y -= 0.5;
                    obj.axePunctSelectat[2].z += 0.5;
                }

                if(!local)
                    EditareRotatie(obj, true);

                    obj.axaOX = obj.centru;
                    obj.axaOY = obj.centru;
                    obj.axaOZ = obj.centru;
                    obj.axaOX.x += 0.5;
                    obj.axaOY.y -= 0.5;
                    obj.axaOZ.z += 0.5;

                    EditareRotatie(obj, false);
            }
            else if(selectie == 6) {
                double saveUnghiRotatie = unghiRotatie;
                CentreazaObiect(obj);

                if(selectareInput == 41) {
                    unghiRotatie = stod(s) * 3.14 / 180.0 - obj.rotatieX;
                    RotesteObiectX(obj);
                    obj.rotatiiAnterioare.push({'x', unghiRotatie});
                }
                else if(selectareInput == 42) {
                    unghiRotatie = stod(s) * 3.14 / 180.0 - obj.rotatieY;
                    RotesteObiectY(obj);
                    obj.rotatiiAnterioare.push({'y', unghiRotatie});
                }
                else {
                    unghiRotatie = stod(s) * 3.14 / 180.0 - obj.rotatieZ;
                    RotesteObiectZ(obj);
                    obj.rotatiiAnterioare.push({'z', unghiRotatie});
                }
                
                unghiRotatie = saveUnghiRotatie;

                RefacePozitia(obj);
            }
            else if(selectie == 7) {
                EditareRotatie(obj, true);
                obiectCentrat = false;
                CentreazaObiect(obj);
                double saveCoeficientMarime = coeficientMarire;

                if(selectareInput == 45) {
                    coeficientMarire = stod(s) - obj.marimeX;
                    MaresteX(obj);
                    obj.stackMarire.push({'x', coeficientMarire});
                }
                else if(selectareInput == 46) {
                    coeficientMarire = stod(s) - obj.marimeY;
                    MaresteY(obj);
                    obj.stackMarire.push({'y', coeficientMarire});
                }
                else {
                    coeficientMarire = stod(s) - obj.marimeZ;
                    MaresteZ(obj);
                    obj.stackMarire.push({'z', coeficientMarire});
                }

                coeficientMarire = saveCoeficientMarime;
                RefacePozitia(obj);
                EditareRotatie(obj, false);

                obj.centru = GetMijlocObiect(obj);
                obj.centruPentruAxe = obj.centru;
            }
            else if(selectie == 8) {
                if(selectareInput == 48)
                    coeficientDeplasare = stod(s);
                else if(selectareInput == 49)
                    unghiRotatie = stod(s) / 180 * 3.14;
                else
                    coeficientMarire = stod(s);
            }
            
            Deseneaza(obj);
            displayText(input, x1, y1, x2, y2);

            displayCursor(cursorPos, input, x1, y1, x2, y2, true);
            showCursor = false;

            delay(100);
        }
        else if((GetAsyncKeyState(VK_LEFT) & 0x8000) || (GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
            if((GetAsyncKeyState(VK_LEFT) & 0x8000) && cursorPos > 0) // Left arrow
                cursorPos--;
            else if((GetAsyncKeyState(VK_RIGHT) & 0x8000) && cursorPos < strlen(input)) // Right arrow
                cursorPos++;
            
            displayText(input, x1, y1, x2, y2);

            displayCursor(cursorPos, input, x1, y1, x2, y2, true);
            showCursor = false;

            delay(100);
        }
        else { 
            char ch;
            if(isValidCharacter(ch, input, cursorPos) && strlen(input) < maxLength - 1 + (input[0] == '-')) {
                memmove(input + cursorPos + 1, input + cursorPos, strlen(input) - cursorPos + 1);
                input[cursorPos] = ch;
                cursorPos++;

                string s = string(input);
                if(s.length() == 0)
                    s = "0";
                else if(s.length() == 1 && (s[0] == '-' || s[0] == '.'))
                    s = "0";
                else if(s.length() == 2 && (s == ".-" || s == "-."))
                    s = "0";
                else if(s.length() >= 2 && s[0] == '-' && s[1] == '.')
                    s.insert(1, "0");

                if(selectie == 0) {
                    if(puncteSelectate.size() > 0) {
                        for(int i = 0; i < puncteSelectate.size(); i++) {
                            if(selectareInput % 3 == 0)
                                obj.varfuri[puncteSelectate[i]].x = stod(s) / 10;
                            else if(selectareInput % 3 == 1)
                                obj.varfuri[puncteSelectate[i]].y = -stod(s) / 10;
                            else
                                obj.varfuri[puncteSelectate[i]].z = stod(s) / 10;
                        }
                    }
                    else if(varfSelectat != -1) {
                        if(selectareInput % 3 == 0)
                            obj.varfuri[varfSelectat].x = stod(s) / 10;
                        else if(selectareInput % 3 == 1)
                            obj.varfuri[varfSelectat].y = -stod(s) / 10;
                        else
                            obj.varfuri[varfSelectat].z = stod(s) / 10;
                    }

                    obj.centru = GetMijlocObiect(obj);
                    EditareRotatie(obj, true);

                    for(int j = 0; j < 3; j++)
                        obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];

                    obj.axePunctSelectat[0].x += 0.5;
                    obj.axePunctSelectat[1].y -= 0.5;
                    obj.axePunctSelectat[2].z += 0.5;

                    obj.axaOX = obj.centru;
                    obj.axaOY = obj.centru;
                    obj.axaOZ = obj.centru;
                    obj.axaOX.x += 0.5;
                    obj.axaOY.y -= 0.5;
                    obj.axaOZ.z += 0.5;

                    EditareRotatie(obj, false);
                }
                else if(selectie == 1) {
                    if(selectareInput == 11)
                        culoarePuncteSelectate[0] = stoi(s);
                    else if(selectareInput == 12)
                        culoarePuncteSelectate[1] = stoi(s);
                    else
                        culoarePuncteSelectate[2] = stoi(s);
                }
                else if(selectie == 2) {
                    if(selectareInput == 22)
                        culoarePuncte[0] = stoi(s);
                    else if(selectareInput == 23)
                        culoarePuncte[1] = stoi(s);
                    else
                        culoarePuncte[2] = stoi(s);
                }
                else if(selectie == 3) {
                    if(selectareInput == 26)
                        culoareMuchii[0] = stoi(s);
                    else if(selectareInput == 27)
                        culoareMuchii[1] = stoi(s);
                    else
                        culoareMuchii[2] = stoi(s);
                }
                else if(selectie == 4) {
                    if(selectareInput == 30)
                        obj.culoareFete[fataSelectata][0] = stoi(s);
                    else if(selectareInput == 31)
                        obj.culoareFete[fataSelectata][1] = stoi(s);
                    else
                        obj.culoareFete[fataSelectata][2] = stoi(s);
                }
                else if(selectie == 5) {
                    if(local)
                        EditareRotatie(obj, true);
                    
                    Punct3D centruNou = obj.centru;

                    if(selectareInput == 37)
                        centruNou.x = stod(s) / 10;
                    else if(selectareInput == 38)
                        centruNou.y = -stod(s) / 10;
                    else
                        centruNou.z = stod(s) / 10;
                    
                    for(auto &j : obj.varfuri) {
                        j.x += centruNou.x - obj.centru.x;
                        j.y += centruNou.y - obj.centru.y;
                        j.z += centruNou.z - obj.centru.z;
                    }

                    if(selectareInput == 37)
                        obj.stackDeplasare.push({'x', centruNou.x - obj.centru.x});
                    else if(selectareInput == 38)
                        obj.stackDeplasare.push({'y', centruNou.y - obj.centru.y});
                    else
                        obj.stackDeplasare.push({'z', centruNou.z - obj.centru.z});

                    obj.centru = centruNou;

                    if(varfSelectat != -1) {
                        for(int j = 0; j < 3; j++)
                            obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];

                        obj.axePunctSelectat[0].x += 0.5;
                        obj.axePunctSelectat[1].y -= 0.5;
                        obj.axePunctSelectat[2].z += 0.5;
                    }

                    if(!local)
                        EditareRotatie(obj, true);
                    
                    obj.axaOX = obj.centru;
                    obj.axaOY = obj.centru;
                    obj.axaOZ = obj.centru;
                    obj.axaOX.x += 0.5;
                    obj.axaOY.y -= 0.5;
                    obj.axaOZ.z += 0.5;

                    EditareRotatie(obj, false);
                }
                else if(selectie == 6) {
                    double saveUnghiRotatie = unghiRotatie;
                    CentreazaObiect(obj);

                    if(selectareInput == 41) {
                        unghiRotatie = stod(s) * 3.14 / 180.0 - obj.rotatieX;
                        RotesteObiectX(obj);
                        obj.rotatiiAnterioare.push({'x', unghiRotatie});
                    }
                    else if(selectareInput == 42) {
                        unghiRotatie = stod(s) * 3.14 / 180.0 - obj.rotatieY;
                        RotesteObiectY(obj);
                        obj.rotatiiAnterioare.push({'y', unghiRotatie});
                    }
                    else {
                        unghiRotatie = stod(s) * 3.14 / 180.0 - obj.rotatieZ;
                        RotesteObiectZ(obj);
                        obj.rotatiiAnterioare.push({'z', unghiRotatie});
                    }
                    
                    unghiRotatie = saveUnghiRotatie;

                    RefacePozitia(obj);
                }   
                else if(selectie == 7) {
                    EditareRotatie(obj, true);
                    obiectCentrat = true;
                    CentreazaObiect(obj);
                    double saveCoeficientMarime = coeficientMarire;

                    if(selectareInput == 45) {
                        coeficientMarire = stod(s) - obj.marimeX;
                        MaresteX(obj);
                        obj.stackMarire.push({'x', coeficientMarire});
                    }
                    else if(selectareInput == 46) {
                        coeficientMarire = stod(s) - obj.marimeY;
                        MaresteY(obj);
                        obj.stackMarire.push({'y', coeficientMarire});
                    }
                    else {
                        coeficientMarire = stod(s) - obj.marimeZ;
                        MaresteZ(obj);
                        obj.stackMarire.push({'z', coeficientMarire});
                    }

                    RefacePozitia(obj);
                    coeficientMarire = saveCoeficientMarime;
                    EditareRotatie(obj, false);

                    obj.centru = GetMijlocObiect(obj);
                    obj.centruPentruAxe = obj.centru;
                }
                else if(selectie == 8) {
                    if(selectareInput == 48)
                        coeficientDeplasare = stod(s);
                    else if(selectareInput == 49)
                        unghiRotatie = stod(s) / 180 * 3.14;
                    else
                        coeficientMarire = stod(s);
                }

                Deseneaza(obj);
                displayText(input, x1, y1, x2, y2);

                displayCursor(cursorPos, input, x1, y1, x2, y2, true);
                showCursor = false;

                delay(100);
            }
        }

        delay(10);
    }

    if(salvareDimensiuneRotatii != (int) obj.rotatiiAnterioare.size()) {
        Undo temp;
        temp.alegere = 1;
        temp.numarRotatii = (int) obj.rotatiiAnterioare.size() - salvareDimensiuneRotatii;

        clearStack(redo);
        undo.push(temp);
    }
    else if(salvareDimensiuneDeplasari != (int) obj.stackDeplasare.size()) {
        Undo temp;
        temp.alegere = 2;
        temp.numarRotatii = (int) obj.stackDeplasare.size() - salvareDimensiuneDeplasari;

        clearStack(redo);
        undo.push(temp);
    }
    else if(salvareDimensiuneMarimi != (int) obj.stackMarire.size()) {
        Undo temp;
        temp.alegere = 3;
        temp.numarRotatii = (int) obj.stackMarire.size() - salvareDimensiuneMarimi;

        clearStack(redo);
        undo.push(temp);
    }
    else if(selectie == 4 && undo.top().index.size() == 3 && undo.top().index[0] == obj.culoareFete[fataSelectata][0] && undo.top().index[1] == obj.culoareFete[fataSelectata][1] && undo.top().index[2] == obj.culoareFete[fataSelectata][2]) {
        undo.pop();
    }
    else if(selectie == 0) {
        int n = undo.top().coordonate.size() - 1;

        if(selectareInput == 0 && obj.varfuri[varfSelectat].x == undo.top().coordonate[n].second)
            undo.pop();
        else if(selectareInput == 1 && obj.varfuri[varfSelectat].y == undo.top().coordonate[n].second)
            undo.pop();
        else if(selectareInput == 2 && obj.varfuri[varfSelectat].z == undo.top().coordonate[n].second)
            undo.pop();
    }

    modificaPagina = true;
    selectareInput = -1;
    setactivepage(pagina);

    Deseneaza(obj);

    setvisualpage(pagina);

    displayCursor(cursorPos, input, x1, y1, x2, y2, false);
}

void EditareInputBox(Obiect &obj, const int &selectie) { 
    if(selectareInput == -1 || !obj.activ)
        return;

    char text[20] = "";
    int i = 0;
    string s;

    if(selectie == 0) {
        if(selectareInput % 3 == 0)
            s = to_string(obj.varfuri[varfSelectat].x * 10);
        else if(selectareInput % 3 == 1)
            s = to_string(-obj.varfuri[varfSelectat].y * 10);
        else
            s = to_string(obj.varfuri[varfSelectat].z * 10);
    }
    else if(selectie == 1) {
        if(selectareInput == 11)
            s = to_string(culoarePuncteSelectate[0]);
        else if(selectareInput == 12)
            s = to_string(culoarePuncteSelectate[1]);
        else
            s = to_string(culoarePuncteSelectate[2]);
    }
    else if(selectie == 2) {
         if(selectareInput == 22)
            s = to_string(culoarePuncte[0]);
        else if(selectareInput == 23)
            s = to_string(culoarePuncte[1]);
        else
            s = to_string(culoarePuncte[2]);
    }
    else if(selectie == 3) {
         if(selectareInput == 26)
            s = to_string(culoareMuchii[0]);
        else if(selectareInput == 27)
            s = to_string(culoareMuchii[1]);
        else
            s = to_string(culoareMuchii[2]);
    }
    else if(selectie == 4) {
        if(selectareInput == 30)
            s = to_string(obj.culoareFete[fataSelectata][0]);
        else if(selectareInput == 31)
            s = to_string(obj.culoareFete[fataSelectata][1]);
        else
            s = to_string(obj.culoareFete[fataSelectata][2]);
    }
    else if(selectie == 5) {
        if(selectareInput == 37)
            s = to_string(obj.centru.x * 10);
        else if(selectareInput == 38)
            if(obj.centru.y != 0)
                s = to_string(-obj.centru.y * 10);
            else
                s = "0.00";
        else
            s = to_string(obj.centru.z * 10);
    }
    else if(selectie == 6) {
        if(selectareInput == 41)
            if(obj.rotatieX == 0)
                s = "0.00";
            else if(!max360)
                s = to_string(obj.rotatieX * 180 / 3.14);
            else {
                double unghi;
                double fractie = modf(obj.rotatieX * 180 / 3.14, &unghi);

                unghi = (int) unghi % 360;
                if(unghi < 0)
                    unghi += 360;
                
                s = to_string(unghi + fractie);
            }
        else if(selectareInput == 42)
            if(obj.rotatieY == 0)
                s = "0.00";
            else if(!max360)
                s = to_string(obj.rotatieY * 180 / 3.14);
            else {
                double unghi;
                double fractie = modf(obj.rotatieY * 180 / 3.14, &unghi);

                unghi = (int) unghi % 360;
                if(unghi < 0)
                    unghi += 360;
                
                s = to_string(unghi + fractie);
            }
        else
            if(obj.rotatieZ == 0)
                s = "0.00";
            else if(!max360)
                s = to_string(obj.rotatieZ * 180 / 3.14);
            else {
                double unghi;
                double fractie = modf(obj.rotatieZ * 180 / 3.14, &unghi);

                unghi = (int) unghi % 360;
                if(unghi < 0)
                    unghi += 360;
                
                s = to_string(unghi + fractie);
            }
    }
    else if(selectie == 7) {
        if(selectareInput == 45)
            s = to_string(obj.marimeX);
        else if(selectareInput == 46)
            s = to_string(obj.marimeY);
        else
            s = to_string(obj.marimeZ);
    }
    else if(selectie == 8) {
        if(selectareInput == 48)
            s = to_string(coeficientDeplasare);
        else if(selectareInput == 49)
            s = to_string(unghiRotatie * 180 / 3.14);
        else
            s = to_string(coeficientMarire);
    }
    
    while(i < s.length() && s[i] != '.') {
        text[i] = s[i];
        i++;
    }

    if(selectie == 0 || selectie == 5 || selectie == 6 || selectie == 7 || selectie == 8) {
        text[i] = '.';
        text[i + 1] = s[i + 1];
        text[i + 2] = s[i + 2];
        text[i + 3] = '\0';
    }
    else
        text[i] = '\0';

    setvisualpage(1-pagina);
    setactivepage(1-pagina);
    
    displayText(text, coordonateInputBox[selectareInput][0], coordonateInputBox[selectareInput][1], coordonateInputBox[selectareInput][2], coordonateInputBox[selectareInput][3]);
    getInputWithCursor(text, 8, coordonateInputBox[selectareInput][0], coordonateInputBox[selectareInput][1], coordonateInputBox[selectareInput][2], coordonateInputBox[selectareInput][3], obj, selectie);
}

void VerificareZoom(Obiect &obj) {
    bool ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
    bool plus = GetAsyncKeyState(VK_ADD) & 0x8000;
    bool minus = GetAsyncKeyState(VK_SUBTRACT) & 0x8000;

    if(!ctrl || (plus && minus) || (!plus && !minus))
        return;
    
    if(plus) {
        if(zoom + coeficientZoom <= 200)
            zoom += coeficientZoom;
    }
    else if(zoom - coeficientZoom > 1)
            zoom -= coeficientZoom;
    
    Deseneaza(obj);
}

void VerificaScrool(Obiect &obj) {
    if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && fereastraStanga == 1) {
        puncteSelectate.clear();

        for(int i = 0; i < obj.varfuri.size(); i++)
            puncteSelectate.push_back(i);
        
        varfSelectat = static_cast<int>(obj.varfuri.size()) - 1;
        selectarePuncte = true;
        EditareRotatie(obj, true);

        for(int j = 0; j < 3; j++)
            obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];
        
        obj.axePunctSelectat[0].x += 0.5;
        obj.axePunctSelectat[1].y -= 0.5;
        obj.axePunctSelectat[2].z += 0.5;

        EditareRotatie(obj, false);
        Deseneaza(obj);

        return;
    }

    if((GetAsyncKeyState(VK_UP) & 0x8000) == (GetAsyncKeyState(VK_DOWN) & 0x8000) || !fereastraStanga)
        return;
    
    int x = mousex(), y = mousey();
    if(y < inaltimeFereastra / 35 || x > 140)
        return;
    
    if((GetAsyncKeyState(VK_UP) & 0x8000) && indexStart - 1 >= 0)
        indexStart--;
    else if((GetAsyncKeyState(VK_DOWN) & 0x8000)) {
            if(fereastraStanga == 1 && indexStart + 1 <= (int) obj.varfuri.size() - 24)
                indexStart++;
            else if(fereastraStanga == 2 && indexStart + 1 <= (int) obj.fete.size() - 24)
                    indexStart++;
            else if(fereastraStanga == 3 && indexStart + 1 <= (int) obiecte.size() - 24)
                    indexStart++;
    }
    
    Deseneaza(obj);

    delay(2);
}

void VerificaApasareButonBaraSus(Obiect &obj) {
    if(!ismouseclick(WM_LBUTTONDOWN))
        return;

    fereastraDreapta = (fereastraDreapta + 1) % 4;

    Deseneaza(obj);

    clearmouseclick(WM_LBUTTONDOWN);
}

void VerificaApasareVarf(Obiect &obj) {
    if(!obj.activ)
        return;
    
    if(ismouseclick(WM_LBUTTONUP)) {
        mouseApasat = false;

        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONUP);
    }

    int x = mousex(), y = mousey();

    if(fereastraFile) {
        if(((butonHover < 2 || butonHover > 4) && butonHover != 6 && butonHover != 7) && !(x >= coordonateButoaneHover[0][0] && y >= coordonateButoaneHover[0][1] && x <= coordonateButoaneHover[0][2] && coordonateButoaneHover[0][3])) {
            fereastraFile = false;

            Deseneaza(obj);
        }
        else if(ismouseclick(WM_LBUTTONDOWN)) {
            if(butonHover == 2) {
                string adresa = GetAdresaFisier();

                if(adresa != "") {
                    Obiect obj2;

                    if(adresa.substr(adresa.size() - 4) == ".obj")
                        obj2 = IncarcaObiect_Obj(adresa);
                    else
                        obj2 = IncarcaObiect(adresa);
                    
                    obj2.activ = true;
                    clearStack(undo);
                    clearStack(redo);
                    clearStack(obj.stackDeplasare);
                    clearStack(obj.stackMarire);
                    clearStack(obj.stackRedoRotatie);
                    clearStack(obj.stackRedoMarire);
                    clearStack(obj.stackRedoDeplasare);
                    
                    if(adresa.substr(static_cast<int>(adresa.size()) - 4) == ".obj")
                        obiecte.push_back(obj2);
                    
                    obiectSelectat = static_cast<int>(obiecte.size()) - 1;
                    obiecteSelectate.clear();
                    obiecteSelectate.push_back(obiectSelectat);

                    Deseneaza(obj);
                }
            }
            else if(butonHover == 4)
                inchideEditor = true;
            else if(butonHover == 3) {
                string adresa = SalveazaFisier();

                if(adresa != "")
                    if(adresa.substr(adresa.size() - 4) == ".obj")
                        SalveazaObiect_Obj(obj, adresa);
                    else
                        SalveazaObiect(obj, adresa);
            }
            else if(butonHover == 6)
                UndoChange(obj, true);
            else if(butonHover == 7)
                RedoChange(obj, true);

            clearmouseclick(WM_LBUTTONDOWN);
        }

        return;
    }

    if(fereastraAdauga) {
        if(!(butonHover >= 35 && butonHover <= 41)) {
            fereastraAdauga = false;
            Deseneaza(obj);
        }
        else if(ismouseclick(WM_LBUTTONDOWN)) {
            const char* data = nullptr;

            if(butonHover == 37)
                data = cub;
            else if(butonHover == 38)
                data = cilindru;
            else if(butonHover == 39)
                data = con;
            else if(butonHover == 40)
                data = sfera;
            else if(butonHover == 41)
                data = masca;
            
            if(data != nullptr) {    
                Obiect obj2;

                obj2 = IncarcaObiectDefault(data);
                obj2.activ = true;

                clearStack(undo);
                clearStack(redo);
                clearStack(obj.stackDeplasare);
                clearStack(obj.stackMarire);
                clearStack(obj.stackRedoRotatie);
                clearStack(obj.stackRedoMarire);
                clearStack(obj.stackRedoDeplasare);

                obiecte.push_back(obj2);
                obiectSelectat = static_cast<int>(obiecte.size()) - 1;
                obiecteSelectate.clear();
                obiecteSelectate.push_back(obiectSelectat);
            }
            else {
                Obiect obj2;

                obj2.axeObiectStabile = {{0, 0, 0}, {0.30, 0, 0}, {0, -0.30, 0}, {0, 0, 0.30}};
                varfSelectat = -1;
                fataSelectata = -1;
                puncteSelectate.clear();
                obj2.axePunctSelectat = vector<Punct3D>(3, {0, 0, 0});
                selectareInput = -1;
                obj2.centru = {0, 0, 0};
                obj2.centruPentruAxe = obj2.centru;

                obj2.axaOX = {obj2.centru.x + 0.5, obj2.centru.y, obj2.centru.z};
                obj2.axaOY = {obj2.centru.x, obj2.centru.y - 0.5, obj2.centru.z};
                obj2.axaOZ = {obj2.centru.x, obj2.centru.y, obj2.centru.z + 0.5};

                obj2.rotatieX = 0;
                obj2.rotatieY = 0;
                obj2.rotatieZ = 0;
                obj2.marimeX = 1;
                obj2.marimeY = 1;
                obj2.marimeZ = 1;
                obj2.deplasareX = 0;
                obj2.deplasareY = 0;
                obj2.deplasareZ = 0;
                obj2.activ = true;


                obiecte.push_back(obj2);
                obiecteSelectate.clear();
                obiectSelectat = (int) obiecte.size() - 1;
                obiecteSelectate.push_back(obiectSelectat);
            }

            Deseneaza(obj);
            clearmouseclick(WM_LBUTTONDOWN);
        }

        return;
    }

    if(obiectSelectat == -1)
        return;

    if(varfSelectat != -1 && (GetAsyncKeyState(VK_DELETE) & 0x8000)) {
        sort(puncteSelectate.begin(), puncteSelectate.end(), greater<int>());
        for(auto i : puncteSelectate) {
            varfSelectat = i;
            EliminaPunct(obj);
        }

        puncteSelectate.clear();

        varfSelectat = -1;
        fataSelectata = -1;

        Deseneaza(obj);
        delay(150);

        return;
    }

    if(!ismouseclick(WM_LBUTTONDOWN) || !butonApasat || mouseApasat || (GetAsyncKeyState(VK_LCONTROL) & 0x8000) || adaugaPunct || selectareInput != -1 || (fereastraDreapta && mousex() >= lungimeFereastra - 250) || mousey() <= inaltimeFereastra / 35 || mousex() <= 147)
        return;
    
    for(int i = 0; i < coordonateInputBox.size(); i++)
        if((x >= coordonateInputBox[i][0] && y >= coordonateInputBox[i][1] && x <= coordonateInputBox[i][2] && y <= coordonateInputBox[i][3]))
            return;
    
    mouseApasat = true;
    Punct2D mouse = {(double) mousex(), (double) mousey()};
    
    if((varfSelectat != -1 && axePunct) || axeMiscareObiect) {
        clearmouseclick(WM_LBUTTONDOWN);

        if(VerificaMousePeAxa(obj, mouse.x, mouse.y))
            return;
    }

    int saveVarfSelectat = varfSelectat;
    varfSelectat = -1;
    
    for(int i = 0; i < obj.varfuri.size(); i++)
        if(estePunctApropiat(Transforma2D(obj.varfuri[i]), mouse) && i != saveVarfSelectat) {
            varfSelectat = i;
            
            if(!unestePuncte) {
                EditareRotatie(obj, true);
            
                for(int j = 0; j < 3; j++)
                    obj.axePunctSelectat[j] = obj.varfuri[i];

                obj.axePunctSelectat[0].x += 0.5;
                obj.axePunctSelectat[1].y -= 0.5;
                obj.axePunctSelectat[2].z += 0.5;

                EditareRotatie(obj, false);
            }

            varfSelectat = i;
        }
    
    if(varfSelectat == -1) {
        //if I want to deselect a face with a misclick:
        fataSelectata = -1;

        Deseneaza(obj);
    }

    if(!deseneazaPuncte && !axeMiscareObiect) {
        varfSelectat = -1;
        puncteSelectate.clear();

        Deseneaza(obj);

        return;
    }
    
    if(!deseneazaPuncte) {
        varfSelectat = -1;
        puncteSelectate.clear();

        Deseneaza(obj);

        return;
    }
    
    if(unestePuncte) {
        clearmouseclick(WM_LBUTTONDOWN);

        ultimaPozitieMouseX = x;
        ultimaPozitieMouseY = y;
        UnestePuncte(obj);
        varfSelectat = -1;

        return;
    }

    if(eliminaPuncte) {
        clearmouseclick(WM_LBUTTONDOWN);

        EliminaPunct(obj);
        varfSelectat = -1;

        return;
    }

    if(saveVarfSelectat != varfSelectat) {
        if(selectarePuncte)
            puncteSelectate.push_back(varfSelectat);
        
        Deseneaza(obj);
    }

    if(varfSelectat != saveVarfSelectat) {
        puncteSelectate.clear();

        Deseneaza(obj);
    }
}

void VerificaHoverButoane(Obiect &obj) {
    int x = mousex(), y = mousey();

    int ultimaValoare = butonHover;
    butonHover = -1;

    for(int i = 0; i < coordonateButoaneHover.size(); i++)
        if(x >= coordonateButoaneHover[i][0] && y >= coordonateButoaneHover[i][1] && x <= coordonateButoaneHover[i][2] && y <= coordonateButoaneHover[i][3]) {
            if(!fereastraFile && !(i >= 2 && i <= 4) && i != 6 && i != 7) {
                butonHover = i;
                break;
            }
            else if(fereastraFile) {
                butonHover = i;
                break;
            }
        }
    
    if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState('A') & 0x8000) && fereastraStanga == 3) {
        obiecteSelectate.clear();
        for(int i = 0; i < obiecte.size(); i++)
            obiecteSelectate.push_back(i);
        obiectSelectat = (int) obiecte.size() - 1;

        clearStack(undo);
                        clearStack(redo);
                        clearStack(obj.stackDeplasare);
                        clearStack(obj.stackMarire);
                        clearStack(obj.stackRedoRotatie);
                        clearStack(obj.stackRedoMarire);
                        clearStack(obj.stackRedoDeplasare);

        Deseneaza(obj);

        return;
    }
    else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && (GetAsyncKeyState(VK_DELETE) & 0x8000) && obiecte.size() > 0) {
        sort(obiecteSelectate.begin(), obiecteSelectate.end(), greater<int>());

        for(const int &i : obiecteSelectate)
            obiecte.erase(obiecte.begin() + i);
        
        obiecteSelectate.clear();
        obiectSelectat = (int) obiecte.size() - 1;
        obiecteSelectate.push_back(obiectSelectat);
        varfSelectat = -1;
        fataSelectata = -1;
        clearStack(undo);
        clearStack(redo);
        clearStack(obj.stackDeplasare);
        clearStack(obj.stackMarire);
        clearStack(obj.stackRedoRotatie);
        clearStack(obj.stackRedoMarire);
        clearStack(obj.stackRedoDeplasare);

        Deseneaza(obj);

        delay(200);

        return;
    }
    else if((GetAsyncKeyState('O') & 0x8000) && fereastraStanga == 3) {
        Obiect obj2;

        obj2.axeObiectStabile = {{0, 0, 0}, {0.30, 0, 0}, {0, -0.30, 0}, {0, 0, 0.30}};
        varfSelectat = -1;
        fataSelectata = -1;
        puncteSelectate.clear();

        obj2.axePunctSelectat = vector<Punct3D>(3, {0, 0, 0});
        selectareInput = -1;
        obj2.centru = {0, 0, 0};
        obj2.centruPentruAxe = obj2.centru;

        obj2.axaOX = {obj2.centru.x + 0.5, obj2.centru.y, obj2.centru.z};
        obj2.axaOY = {obj2.centru.x, obj2.centru.y - 0.5, obj2.centru.z};
        obj2.axaOZ = {obj2.centru.x, obj2.centru.y, obj2.centru.z + 0.5};

        obj2.rotatieX = 0;
        obj2.rotatieY = 0;
        obj2.rotatieZ = 0;
        obj2.marimeX = 1;
        obj2.marimeY = 1;
        obj2.marimeZ = 1;
        obj2.deplasareX = 0;
        obj2.deplasareY = 0;
        obj2.deplasareZ = 0;
        obj2.activ = true;

        obiecte.push_back(obj2);
        obiecteSelectate.clear();
        obiectSelectat = (int) obiecte.size() - 1;
        obiecteSelectate.push_back(obiectSelectat);

        clearStack(undo);
        clearStack(redo);
        clearStack(obj.stackDeplasare);
        clearStack(obj.stackMarire);
        clearStack(obj.stackRedoRotatie);
        clearStack(obj.stackRedoMarire);
        clearStack(obj.stackRedoDeplasare);

        Deseneaza(obj2);

        delay(200);

        return;
    }
    
    if(ultimaValoare != butonHover) {
        Deseneaza(obj);

        return;
    }

    if(butonHover == 1)
        VerificaApasareButonBaraSus(obj);
    
    if(butonHover == 0) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        fereastraFile = true;

        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(butonHover == 5) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        axeObiectSelectat = (axeObiectSelectat + 1) % 3;

        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(butonHover == 8) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        butonGrid = (butonGrid + 1) % 3;

        if(butonGrid == 1) {
            grid.varfuri.clear();
            grid.muchii.clear();
            int latime = 12, lungime = 12;

            for(int i = 0; i <= lungime; i++) {
                bool adauga = false;

                for(int j = 0; j <= latime; j++) {
                    grid.varfuri.push_back({(double) (i - lungime / 2) * 1.5, 3, (double) (j - 10) * 1.5});

                    if(adauga && i % 2 && i < lungime)
                        col.push_back(grid.varfuri.size() - 1);
                    if(j < latime)
                        grid.muchii.push_back({i * (latime + 1) + j, i * (latime + 1) + j + 1});
                    if(i < lungime)
                        grid.muchii.push_back({(i + 1) * (latime + 1) + j, i * (latime + 1) + j});
                    
                    if(i > 0 && i < lungime)
                        adauga = !adauga;
                }
            }

            grid.centru = GetMijlocObiect(grid);
            
            for(int i = 0; i < grid.varfuri.size(); i++) {
                grid.varfuri[i].x -= grid.centru.x;
                grid.varfuri[i].z -= grid.centru.z;
            }
        }

        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(butonHover == 9) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        local = !local;

        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(butonHover > 9 && butonHover < 34 && fereastraStanga) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        int index = butonHover - 10 + indexStart;
        if(fereastraStanga == 1) {
            if(index > obj.varfuri.size() - 1) {
                clearmouseclick(WM_LBUTTONDOWN);
                return;
            }
        
            if(index == varfSelectat) {
                puncteSelectate.pop_back();

                if(puncteSelectate.size() > 0)
                    varfSelectat = puncteSelectate[puncteSelectate.size() - 1];
                else
                    varfSelectat = -1;
            }
            else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && find(puncteSelectate.begin(), puncteSelectate.end(), index) != puncteSelectate.end()) {
                for(int i = 0; i < puncteSelectate.size(); i++)
                    if(puncteSelectate[i] == index) {
                        puncteSelectate.erase(puncteSelectate.begin() + i);
                        break;
                    }
            }
            else if(index < obj.varfuri.size()) {
                if(GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                    selectarePuncte = true;
                    if(varfSelectat != -1)
                        puncteSelectate.push_back(index);
                    
                    varfSelectat = index;
                }
                else {
                    puncteSelectate.clear();
                    varfSelectat = index;
                    puncteSelectate.push_back(index);
                }
            }
        
            if(varfSelectat != -1) {
                EditareRotatie(obj, true);
                for(int j = 0; j < 3; j++) {
                    obj.axePunctSelectat[j] = obj.varfuri[varfSelectat];
                }

                obj.axePunctSelectat[0].x += 0.5;
                obj.axePunctSelectat[1].y -= 0.5;
                obj.axePunctSelectat[2].z += 0.5;

                EditareRotatie(obj, false);
            }
        }
        else if(fereastraStanga == 2) {
            if(index > obj.fete.size() - 1) {
                clearmouseclick(WM_LBUTTONDOWN);
                return;
            }

            if(obj.indexFata[index] == fataSelectata)
                fataSelectata = -1;
            else
                fataSelectata = obj.indexFata[index];
        }
        else if(fereastraStanga == 3) {
            if(index > obiecte.size() - 1) {
                clearmouseclick(WM_LBUTTONDOWN);
                return;
            }

            clearStack(undo);
            clearStack(redo);
            clearStack(obj.stackDeplasare);
            clearStack(obj.stackMarire);
            clearStack(obj.stackRedoRotatie);
            clearStack(obj.stackRedoMarire);
            clearStack(obj.stackRedoDeplasare);

            if(index == obiectSelectat) {
                obiecteSelectate.pop_back();
                if(static_cast<int>(obiecteSelectate.size()) > 0)
                    obiectSelectat = obiecteSelectate[obiecteSelectate.size() - 1];
                else
                    obiectSelectat = -1;
            }
            else if((GetAsyncKeyState(VK_CONTROL) & 0x8000) && find(obiecteSelectate.begin(), obiecteSelectate.end(), index) != obiecteSelectate.end()) {
                for(int i = 0; i < obiecteSelectate.size(); i++)
                    if(obiecteSelectate[i] == index) {
                        obiecteSelectate.erase(obiecteSelectate.begin() + i);
                        break;
                    }
            }
            else if(index < static_cast<int>(obiecte.size())) {
                if(GetAsyncKeyState(VK_CONTROL) & 0x8000) {
                    selectarePuncte = true;
                    if(obiectSelectat != -1)
                        obiecteSelectate.push_back(index);
                    
                    obiectSelectat = index;
                }
                else {
                    obiecteSelectate.clear();
                    obiectSelectat = index;
                    obiecteSelectate.push_back(index);
                }
            }
                
            varfSelectat = -1;
            fataSelectata = -1;
        }
        
        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(butonHover == 34) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        fereastraStanga = (fereastraStanga + 1) % 4;
        indexStart = 0;

        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(butonHover == 35) {
        if(!ismouseclick(WM_LBUTTONDOWN))
            return;
        
        fereastraAdauga = !fereastraAdauga;

        Deseneaza(obj);

        clearmouseclick(WM_LBUTTONDOWN);
    }
} 

void VerificaApasareButon(Obiect &obj) {
    butonApasat = true;
    if(!ismouseclick(WM_LBUTTONDOWN))
        return;
    
    int x = mousex(), y = mousey();
    selectareInput = -1;

    for(int i = 0; i < 25 && fereastraDreapta == 1; i++)
        if(i != 20 && x >= coordonateInputBox[i][0] && y >= coordonateInputBox[i][1] && x <= coordonateInputBox[i][2] && y <= coordonateInputBox[i][3]) {
            selectareInput = i;
        }

    for(int i = 25; i < 36 && fereastraDreapta == 2; i++)
        if(x >= coordonateInputBox[i][0] && y >= coordonateInputBox[i][1] && x <= coordonateInputBox[i][2] && y <= coordonateInputBox[i][3]) {
            selectareInput = i;
        }
    
    if(fereastraDreapta == 2 && x >= coordonateInputBox[20][0] && y >= coordonateInputBox[20][1] && x <= coordonateInputBox[20][2] && y <= coordonateInputBox[20][3])
        selectareInput = 20;

    for(int i = 36; i < coordonateInputBox.size() && fereastraDreapta == 3; i++)
        if(x >= coordonateInputBox[i][0] && y >= coordonateInputBox[i][1] && x <= coordonateInputBox[i][2] && y <= coordonateInputBox[i][3]) {
            selectareInput = i;
        }
    
    //selectie: 0 -> position; 1 -> color(RGB)
    if(selectareInput != -1 && varfSelectat != -1) {
        if(selectareInput < 9)
            EditareInputBox(obj, 0);
    }

    if(selectareInput == 9) {
        axePunct = !axePunct;

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(selectareInput == 10) {
        colorarePuncteSelectate = !colorarePuncteSelectate;

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(colorarePuncteSelectate && selectareInput >= 11 && selectareInput <= 13) {
        EditareInputBox(obj, 1);
    }
    else if(selectareInput == 14) {
        selectarePuncte = !selectarePuncte;
        unestePuncte = false;
        adaugaPunct = false;
        eliminaPuncte = false;

        if(!selectarePuncte) {
            puncteSelectate.clear();
            varfSelectat = -1;
        }
        else if(varfSelectat != -1)
                puncteSelectate.push_back(varfSelectat);
        
        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(selectareInput == 15) {
        clearmouseclick(WM_LBUTTONDOWN);
        setactivepage(1-pagina);
        setcolor(COLOR(60, 60, 60));
        rectangle(coordonateInputBox[15][0] - 1, coordonateInputBox[15][1] - 1, coordonateInputBox[15][2] + 1, coordonateInputBox[15][3] + 1);

        Undo temp;
        temp.alegere = 6;
        temp.numarRotatii = 0;
        for(int i = 1; i < puncteSelectate.size(); i++) {
            bool ok = true;

            for(int j = 0; j < obj.muchii.size(); j++)
                if((obj.muchii[j].first == puncteSelectate[0] && obj.muchii[j].second == puncteSelectate[i]) || (obj.muchii[j].first == puncteSelectate[i] && obj.muchii[j].second == puncteSelectate[0])) {
                    ok = false;
                    break;
                }
            
            if(ok) {
                obj.muchii.push_back({puncteSelectate[0], puncteSelectate[i]});
                temp.numarRotatii++;
            }
        }

        if(temp.numarRotatii > 0) {
            clearStack(redo);
            undo.push(temp);
        }

        delay(150);
        modificaPagina = false;
        Deseneaza(obj);
        modificaPagina = true;
        setactivepage(pagina);
    }
    else if(selectareInput == 16) { //connect consecutive points
        clearmouseclick(WM_LBUTTONDOWN);
        setactivepage(1 - pagina);
        setcolor(COLOR(60, 60, 60));
        rectangle(coordonateInputBox[16][0] - 1, coordonateInputBox[16][1] - 1, coordonateInputBox[16][2] + 1, coordonateInputBox[16][3] + 1);
        
        Undo temp;
        temp.alegere = 6;
        temp.numarRotatii = 0;
        for(int i = 0; i < static_cast<int>(puncteSelectate.size()) - 1; i++) {
            bool ok = true;
            for(int j = 0; j < obj.muchii.size(); j++)
                if((obj.muchii[j].first == puncteSelectate[i] && obj.muchii[j].second == puncteSelectate[i + 1]) || (obj.muchii[j].first == puncteSelectate[i + 1] && obj.muchii[j].second == puncteSelectate[i])) {
                    ok = false;
                    break;
                }
            
            if(ok) {
                obj.muchii.push_back({puncteSelectate[i], puncteSelectate[i + 1]});
                temp.numarRotatii++;
            }
        }

        if(temp.numarRotatii > 0) {
            clearStack(redo);
            undo.push(temp);
        }

        delay(150);
        modificaPagina = false;
        Deseneaza(obj);
        modificaPagina = true;
        setactivepage(pagina);
    }
    else if(selectareInput == 17) {
        unestePuncte = !unestePuncte;
        selectarePuncte = false;
        eliminaPuncte = false;
        adaugaPunct = false;
        varfSelectat = -1;
        puncteSelectate.clear();

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(selectareInput == 18) {
        adaugaPunct = !adaugaPunct;
        eliminaPuncte = false;
        unestePuncte = false;
        selectarePuncte = false;
        varfSelectat = -1;
        puncteSelectate.clear();

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(selectareInput == 19) {
        eliminaPuncte = !eliminaPuncte;
        adaugaPunct = false;
        unestePuncte = false;
        selectarePuncte = false;
        varfSelectat = -1;
        puncteSelectate.clear();

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
    }
    else if(selectareInput == 20) {
        clearmouseclick(WM_LBUTTONDOWN);
        setactivepage(1-pagina);
        setcolor(COLOR(60, 60, 60));
        rectangle(coordonateInputBox[16][0] - 1, coordonateInputBox[16][1] - 1, coordonateInputBox[16][2] + 1, coordonateInputBox[16][3] + 1);

        if(static_cast<int>(puncteSelectate.size()) >= 3) {
            obj.fete.push_back({});
            int n = obj.fete.size() - 1;

            for(auto i : puncteSelectate)
                obj.fete[n].push_back(i);

            for(int i = 0; i < puncteSelectate.size(); i++) {
                vector<pair<int, int>>::iterator it1 = find_if(obj.muchii.begin(), obj.muchii.end(), [&](const pair<int, int> &p) {
                    return (p.first == puncteSelectate[i] && p.second == puncteSelectate[(i + 1) % static_cast<int>(puncteSelectate.size())])
                    || (p.second == puncteSelectate[i] && p.first == puncteSelectate[(i + 1) % static_cast<int>(puncteSelectate.size())]);
                });

                if(it1 != obj.muchii.end()) {
                    obj.muchii.erase(obj.muchii.begin() + i);
                    continue;
                }
            }
        
            obj.culoareFete.push_back({100, 100, 100});
            obj.indexFata.push_back((int) obj.indexFata.size());
            Undo temp;
            temp.alegere = 8;
            temp.fete.push_back(obj.fete[obj.fete.size() - 1]);
            clearStack(redo);
            undo.push(temp);
        }

        modificaPagina = false;
        Deseneaza(obj);
        modificaPagina = true;
        setactivepage(pagina);
        delay(150);
    }
    else if(selectareInput == 21) {
        clearmouseclick(WM_LBUTTONDOWN);
        deseneazaPuncte = !deseneazaPuncte;
        varfSelectat = -1;
        puncteSelectate.clear();

        Deseneaza(obj);
        delay(150);
    }
    else if(selectareInput >= 22 && selectareInput <= 24)
        EditareInputBox(obj, 2);
    else if(selectareInput == 25) {
        deseneazaMuchii = !deseneazaMuchii;

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(150);
    }
    else if(selectareInput >= 26 && selectareInput <= 28)
        EditareInputBox(obj, 3);
    else if(selectareInput == 29) {
        deseneazaFete = !deseneazaFete;
        xRay = false;
        if(!deseneazaFete)
            fataSelectata = -1;
        
        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(150);
    }
    else if(selectareInput >= 30 && selectareInput <= 32 && fataSelectata != -1) {
        EditareInputBox(obj, 4);
    }
    else if(selectareInput == 33 && fataSelectata != -1) {
        clearmouseclick(WM_LBUTTONDOWN);
        setactivepage(1-pagina);
        setcolor(COLOR(60, 60, 60));
        rectangle(coordonateInputBox[33][0] - 1, coordonateInputBox[33][1] - 1, coordonateInputBox[33][2] + 1, coordonateInputBox[33][3] + 1);

        copieCuloareFata = obj.culoareFete[fataSelectata];

        modificaPagina = false;
        Deseneaza(obj);
        modificaPagina = true;
        setactivepage(pagina);
        delay(150);
    }
    else if(selectareInput == 34 && fataSelectata != -1) {
        clearmouseclick(WM_LBUTTONDOWN);
        setactivepage(1-pagina);
        setcolor(COLOR(60, 60, 60));
        rectangle(coordonateInputBox[33][0] - 1, coordonateInputBox[33][1] - 1, coordonateInputBox[33][2] + 1, coordonateInputBox[33][3] + 1);

        if(obj.culoareFete[fataSelectata] != copieCuloareFata) {
            Undo temp;
            temp.alegere = 9;
            temp.index = vector<int>(3);
            temp.fete.push_back(obj.fete[fataSelectata]);
            temp.index[0] = obj.culoareFete[fataSelectata][0];
            temp.index[1] = obj.culoareFete[fataSelectata][1];
            temp.index[2] = obj.culoareFete[fataSelectata][2];

            clearStack(redo);
            undo.push(temp);
        }

        obj.culoareFete[fataSelectata] = copieCuloareFata;

        modificaPagina = false;
        Deseneaza(obj);
        modificaPagina = true;
        setactivepage(pagina);

        delay(150);
    }
    else if(selectareInput == 35) {
        xRay = !xRay;
        deseneazaFete = false;
        if(xRay) {
            deseneazaMuchii = true;
            deseneazaFete = true;
        }
        fataSelectata = -1;

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(150);
    }
    else if(selectareInput == 36) {
        for(const int &i : obiecteSelectate)
            obiecte[i].activ = !obiecte[i].activ;
        
        fataSelectata = -1;
        varfSelectat = -1;
        puncteSelectate.clear();
        
        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(150);
    }
    else if(selectareInput >= 37 && selectareInput <= 39) {
        EditareInputBox(obj, 5);
    }
    else if(selectareInput == 40) {
        axeMiscareObiect = !axeMiscareObiect;

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(150);
    }
    else if(selectareInput >= 41 && selectareInput <= 43) {
        EditareInputBox(obj, 6);
    }
    else if(selectareInput == 44) {
        max360 = !max360;

        Deseneaza(obj);
        clearmouseclick(WM_LBUTTONDOWN);
        delay(150);
    }
    else if(selectareInput >= 45 && selectareInput <= 47)
        EditareInputBox(obj, 7);
    else if(selectareInput >= 48 && selectareInput <= 50)
        EditareInputBox(obj, 8);

    if((fereastraDreapta && mousex() >= lungimeFereastra - 250) || mousey() <= inaltimeFereastra / 35)
        clearmouseclick(WM_LBUTTONDOWN);
}  

void SelecteazaFata(Obiect &obj, const int &fataIndex) {
    if(!deseneazaFete || obj.fete.size() == 0)
        return;
    
    if(fataIndex >= 0 && fataIndex < static_cast<int>(obj.fete.size())) {
        for(int i = 0; i < obj.indexFata.size(); i++)
            if(obj.indexFata[i] == fataIndex) {
                fataSelectata = i;
                break;
            }
    }
    else if (fataIndex < 0) {
        for(int i = 0; i < obj.indexFata.size(); i++)
            if(obj.indexFata[i] == static_cast<int>(obj.indexFata.size()) - 1) {
                fataSelectata = i;
                break;
            }
    }
    else {
        for(int i = 0; i < obj.indexFata.size(); i++)
            if(obj.indexFata[i] == 0) {
                fataSelectata = i;
                break;
            }
    }
    
    Deseneaza(obj);

    //delay because one key pressed produce more calls on this function if there is no delay
    delay(200);
}
