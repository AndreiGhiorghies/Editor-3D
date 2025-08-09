#include <math.h>
#include <algorithm>
#include <winbgim.h>
#include <iostream>

#include "../Headers/Deseneaza.h"

//create a declaration of this function here to get rid of a circular include dependence
Punct2D Transforma2D(const Punct3D &punct);
void SorteazaFetele(Obiect &obj);

void isHover(const int &i) {
    if(i == butonHover)
        setbkcolor(COLOR(70, 70, 70));
    else
        setbkcolor(COLOR(50, 50, 50));
}

void DeseneazaBaraComenzi() {
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(0, 0, lungimeFereastra, inaltimeFereastra / 35);

    char ss[200];
    setcolor(WHITE);
    int inaltime = 4;
    
    isHover(0);
    sprintf(ss, " File ");
    outtextxy(8, inaltime, ss);
    coordonateButoaneHover[0] = {8, inaltime, 8 + textwidth((char*) " File "), inaltime + textheight((char*) " File ")};

    isHover(1);
    if(fereastraDreapta == 0) {
        sprintf(ss, " Ascuns ");
        coordonateButoaneHover[1] = {1380, inaltime, 1380 + textwidth((char*) " Ascuns "), inaltime + textheight((char*) " Ascuns ")};
    }
    else if(fereastraDreapta == 1) {
        sprintf(ss, " Puncte ");
        coordonateButoaneHover[1] = {1380, inaltime, 1380 + textwidth((char*) " Puncte "), inaltime + textheight((char*) " Puncte ")};
    }
    else if(fereastraDreapta == 2) {
        sprintf(ss, " Muchii/Fete ");
        coordonateButoaneHover[1] = {1380, inaltime, 1380 + textwidth((char*) " Muchii/Fete "), inaltime + textheight((char*) " Muchii/Fete ")};
    }
    else if(fereastraDreapta == 3) {
        sprintf(ss, " Obiect ");
        coordonateButoaneHover[1] = {1380, inaltime, 1380 + textwidth((char*) " Obiect "), inaltime + textheight((char*) " Obiect ")};
    }
    outtextxy(1380, inaltime, ss);

    isHover(5);
    if(axeObiectSelectat == 0) {
        sprintf(ss, " Ascuns ");
        coordonateButoaneHover[5] = {1470, inaltime, 1470 + textwidth((char*) " Ascuns "), inaltime + textheight((char*) " Ascuns ")};
    }
    else if(axeObiectSelectat == 1) {
        sprintf(ss, " Obiect ");
        coordonateButoaneHover[5] = {1470, inaltime, 1470 + textwidth((char*) " Obiect "), inaltime + textheight((char*) " Obiect ")};
    }
    else if(axeObiectSelectat == 2) {
        sprintf(ss, " Fixat ");
        coordonateButoaneHover[5] = {1470, inaltime, 1470 + textwidth((char*) " Fixat "), inaltime + textheight((char*) " Fixat ")};
    }
    outtextxy(1470, inaltime, ss);
    
    if(fereastraFile) {
        setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
        setbkcolor(COLOR(50, 50, 50));

        bar(0, inaltimeFereastra / 35, 100, inaltimeFereastra / 35 + 130);

        isHover(2);
        coordonateButoaneHover[2] = {0, inaltimeFereastra / 35, 100, inaltimeFereastra / 35 + 25};
        if(butonHover == 2) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[2][0], coordonateButoaneHover[2][1], coordonateButoaneHover[2][2], coordonateButoaneHover[2][3]);
        }
        sprintf(ss, " Deschide ");
        outtextxy(50 - textwidth((char*) " Deschide ") / 2, inaltimeFereastra / 35 + textheight((char*) " Deschide ") / 2 - 3, ss);

        isHover(3);
        coordonateButoaneHover[3] = {0, inaltimeFereastra / 35 + 25, 100, inaltimeFereastra / 35 + 50};
        if(butonHover == 3) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[3][0], coordonateButoaneHover[3][1], coordonateButoaneHover[3][2], coordonateButoaneHover[3][3]);
        }
        sprintf(ss, " Salveaza ");
        outtextxy(50 - textwidth((char*) " Salveaza ") / 2, inaltimeFereastra / 35 + textheight((char*) " Salveaza ") / 2 - 3 + 25, ss);
        
        isHover(6);
        coordonateButoaneHover[6] = {0, inaltimeFereastra / 35 + 50, 100, inaltimeFereastra / 35 + 75};
        if(butonHover == 6) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[6][0], coordonateButoaneHover[6][1], coordonateButoaneHover[6][2], coordonateButoaneHover[6][3]);
        }
        sprintf(ss, " Undo ");
        outtextxy(50 - textwidth((char*) " Undo ") / 2, inaltimeFereastra / 35 + textheight((char*) " Undo ") / 2 - 3 + 50, ss);
        
        isHover(7);
        coordonateButoaneHover[7] = {0, inaltimeFereastra / 35 + 75, 100, inaltimeFereastra / 35 + 100};
        if(butonHover == 7) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[7][0], coordonateButoaneHover[7][1], coordonateButoaneHover[7][2], coordonateButoaneHover[7][3]);
        }
        sprintf(ss, " Redo ");
        outtextxy(50 - textwidth((char*) " Redo ") / 2, inaltimeFereastra / 35 + textheight((char*) " Redo ") / 2 - 3 + 75, ss);

        isHover(4);
        coordonateButoaneHover[4] = {0, inaltimeFereastra / 35 + 100, 100, inaltimeFereastra / 35 + 130};
        if(butonHover == 4) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[4][0], coordonateButoaneHover[4][1], coordonateButoaneHover[4][2], coordonateButoaneHover[4][3]);
        }
        sprintf(ss, " Inchide ");
        outtextxy(50 - textwidth((char*) " Inchide ") / 2, inaltimeFereastra / 35 + textheight((char*) " Inchide ") / 2 - 3 + 100, ss);

        setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
        bar(100 - 5, inaltimeFereastra / 35, 100, inaltimeFereastra / 35 + 130);
        bar(0, inaltimeFereastra / 35 + 125, 100, inaltimeFereastra / 35 + 130);
    }

    isHover(8);
    if(butonGrid == 0) {
        sprintf(ss, " Ascuns ");
        coordonateButoaneHover[8] = {1300, inaltime, 1300 + textwidth((char*) " Ascuns "), inaltime + textheight((char*) " Ascuns ")};
    }
    else if(butonGrid == 2) {
        sprintf(ss, " Dinamic ");
        coordonateButoaneHover[8] = {1300, inaltime, 1300 + textwidth((char*) " Dinamic "), inaltime + textheight((char*) " Dinamic ")};
    }
    else if(butonGrid == 1) {
        sprintf(ss, " Fixat ");
        coordonateButoaneHover[8] = {1300, inaltime, 1300 + textwidth((char*) " Fixat "), inaltime + textheight((char*) " Fixat ")};
    }
    outtextxy(1300, inaltime, ss);

    isHover(9);
    if(local) {
        sprintf(ss, " Local ");
        coordonateButoaneHover[9] = {1230, inaltime, 1230 + textwidth((char*) " Local "), inaltime + textheight((char*) " Local ")};
    }
    else {
        sprintf(ss, " Global ");
        coordonateButoaneHover[9] = {1230, inaltime, 1230 + textwidth((char*) " Global "), inaltime + textheight((char*) " Global ")};
    }
    outtextxy(1230, inaltime, ss);

    isHover(34);
    if(fereastraStanga == 0) {
        sprintf(ss, " Ascuns ");
        coordonateButoaneHover[34] = {70, inaltime, 70 + textwidth((char*) " Ascuns "), inaltime + textheight((char*) " Ascuns ")};
    }
    else if(fereastraStanga == 1) {
        sprintf(ss, " Puncte ");
        coordonateButoaneHover[34] = {70, inaltime, 70 + textwidth((char*) " Puncte "), inaltime + textheight((char*) " Puncte ")};
    }
    else if(fereastraStanga == 2) {
        sprintf(ss, " Fete ");
        coordonateButoaneHover[34] = {70, inaltime, 70 + textwidth((char*) " Fete "), inaltime + textheight((char*) " Fete ")};
    }
    else if(fereastraStanga == 3) {
        sprintf(ss, " Obiecte ");
        coordonateButoaneHover[34] = {70, inaltime, 70 + textwidth((char*) " Obiecte "), inaltime + textheight((char*) " Obiecte ")};
    }
    outtextxy(70, inaltime, ss);

    isHover(35);
    sprintf(ss, " Adauga ");
    outtextxy(165, inaltime, ss);
    coordonateButoaneHover[35] = {165, inaltime, 165 + textwidth((char*) " Adauga "), inaltimeFereastra / 35};

    if(fereastraAdauga) {
        setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
        setbkcolor(COLOR(50, 50, 50));

        bar(140, inaltimeFereastra / 35, 240, inaltimeFereastra / 35 + 155);

        isHover(36);
        coordonateButoaneHover[36] = {140, inaltimeFereastra / 35, 240, inaltimeFereastra / 35 + 25};
        if(butonHover == 36) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[36][0], coordonateButoaneHover[36][1], coordonateButoaneHover[36][2], coordonateButoaneHover[36][3]);
        }
        sprintf(ss, " Empty ");
        outtextxy(190 - textwidth((char*) " Empty ") / 2, inaltimeFereastra / 35 + textheight((char*) " Empty ") / 2 - 3, ss);

        isHover(37);
        coordonateButoaneHover[37] = {140, inaltimeFereastra / 35 + 25, 240, inaltimeFereastra / 35 + 50};
        if(butonHover == 37) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[37][0], coordonateButoaneHover[37][1], coordonateButoaneHover[37][2], coordonateButoaneHover[37][3]);
        }
        sprintf(ss, " Cub ");
        outtextxy(190 - textwidth((char*) " Cub ") / 2, inaltimeFereastra / 35 + textheight((char*) " Cub ") / 2 - 3 + 25, ss);
        
        isHover(38);
        coordonateButoaneHover[38] = {140, inaltimeFereastra / 35 + 50, 240, inaltimeFereastra / 35 + 75};
        if(butonHover == 38) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[38][0], coordonateButoaneHover[38][1], coordonateButoaneHover[38][2], coordonateButoaneHover[38][3]);
        }
        sprintf(ss, " Cilindru ");
        outtextxy(190 - textwidth((char*) " Cilindru ") / 2, inaltimeFereastra / 35 + textheight((char*) " Cilindru ") / 2 - 3 + 50, ss);
        
        isHover(39);
        coordonateButoaneHover[39] = {140, inaltimeFereastra / 35 + 75, 240, inaltimeFereastra / 35 + 100};
        if(butonHover == 39) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[39][0], coordonateButoaneHover[39][1], coordonateButoaneHover[39][2], coordonateButoaneHover[39][3]);
        }
        sprintf(ss, " Con ");
        outtextxy(190 - textwidth((char*) " Con ") / 2, inaltimeFereastra / 35 + textheight((char*) " Con ") / 2 - 3 + 75, ss);

        isHover(40);
        coordonateButoaneHover[40] = {140, inaltimeFereastra / 35 + 100, 240, inaltimeFereastra / 35 + 125};
        if(butonHover == 40) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[40][0], coordonateButoaneHover[40][1], coordonateButoaneHover[40][2], coordonateButoaneHover[40][3]);
        }
        sprintf(ss, " Sfera ");
        outtextxy(190 - textwidth((char*) " Sfera ") / 2, inaltimeFereastra / 35 + textheight((char*) " Sfera ") / 2 - 3 + 100, ss);

        isHover(41);
        coordonateButoaneHover[41] = {140, inaltimeFereastra / 35 + 125, 240, inaltimeFereastra / 35 + 155};
        if(butonHover == 41) {
            setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
            bar(coordonateButoaneHover[41][0], coordonateButoaneHover[41][1], coordonateButoaneHover[41][2], coordonateButoaneHover[41][3]);
        }
        sprintf(ss, " Masca ");
        outtextxy(190 - textwidth((char*) " Masca ") / 2, inaltimeFereastra / 35 + textheight((char*) " Masca ") / 2 - 3 + 125, ss);

        setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
        bar(235, inaltimeFereastra / 35, 240, inaltimeFereastra / 35 + 155);
        bar(140, inaltimeFereastra / 35, 145, inaltimeFereastra / 35 + 155);
        bar(140, inaltimeFereastra / 35 + 150, 240, inaltimeFereastra / 35 + 155);

    }

    setbkcolor(BLACK);
}

void AddDecimals(char text[10], const string &s) {
    int j = 0;

    while(s[j] != '.') {
        text[j] = s[j];
        j++;
    }

    text[j] = '.';
    text[j + 1] = s[j + 1];
    text[j + 2] = s[j + 2];
    text[j + 3] = '\0';
}

void DeseneazaCasutaInput(const Obiect &obj, const char* titleText, const int &i, const int &mijlocLatime, const int &mijlocInaltime, const int &lungimeInputBox, const int &inaltimeInputBox, const int &limitaInaltime) {
    setbkcolor(COLOR(50, 50, 50));

    char ss[10];
    sprintf(ss, titleText);
    outtextxy(mijlocLatime - lungimeInputBox / 2 - textwidth((char*) titleText), limitaInaltime + 30, ss);

    setbkcolor(COLOR(70, 70, 70));
    setcolor(COLOR(20, 20, 20));

    rectangle(mijlocLatime - lungimeInputBox / 2, mijlocInaltime - inaltimeInputBox / 2, mijlocLatime + lungimeInputBox / 2, mijlocInaltime + inaltimeInputBox / 2);
    coordonateInputBox[i] = {mijlocLatime - lungimeInputBox / 2 + 1, mijlocInaltime - inaltimeInputBox / 2 + 1, mijlocLatime + lungimeInputBox / 2 - 1, mijlocInaltime + inaltimeInputBox / 2 - 1};

    setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
    bar(mijlocLatime - lungimeInputBox / 2 + 1, mijlocInaltime - inaltimeInputBox / 2 + 1, mijlocLatime + lungimeInputBox / 2 - 1, mijlocInaltime + inaltimeInputBox / 2 - 1);
    setcolor(WHITE);

    char text[10] = "";
    string s;

    if(varfSelectat != -1 && i < 9 && !unestePuncte && !eliminaPuncte && selectareInput != i) {
        //display the coordinates of a vertice
        if(i % 3 == 0)
            if(obj.varfuri[varfSelectat].x > -0.01 && obj.varfuri[varfSelectat].x < 0.01)
                s = "0.00";
            else
                s = to_string(obj.varfuri[varfSelectat].x * 10);
        else if(i % 3 == 1)
            if(obj.varfuri[varfSelectat].y > -0.01 && obj.varfuri[varfSelectat].y < 0.01)
                s = "0.00";
            else
                s = to_string(-obj.varfuri[varfSelectat].y * 10);
        else
            if(obj.varfuri[varfSelectat].z > -0.01 && obj.varfuri[varfSelectat].z < 0.01)
                s = "0.00";
            else
                s = to_string(obj.varfuri[varfSelectat].z * 10);
        
        AddDecimals(text, s);
        
        sprintf(ss, text);
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 11 && i <= 13 && colorarePuncteSelectate) {
        //display the RGB color of the selected vertices
        if(i == 11)
            s = to_string(culoarePuncteSelectate[0]); // R
        else if(i == 12)
            s = to_string(culoarePuncteSelectate[1]); // G
        else
            s = to_string(culoarePuncteSelectate[2]); // B
        
        sprintf(ss, s.c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 22 && i <= 24) {
        //display the RGB color of all vertices
        if(i == 22)
            s = to_string(culoarePuncte[0]); // R
        else if(i == 23)
            s = to_string(culoarePuncte[1]); // G
        else
            s = to_string(culoarePuncte[2]); // B
        
        sprintf(ss, s.c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 26 && i <= 28) {
        //display the RGB color of all edges
        if(i == 26)
            s = to_string(culoareMuchii[0]); // R
        else if(i == 27)
            s = to_string(culoareMuchii[1]); // G
        else
            s = to_string(culoareMuchii[2]); // B
        
        sprintf(ss, s.c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 30 && i <= 32 && fataSelectata != -1) {
        //display the RGB color of a selected face
        if(i == 30)
            s = to_string(obj.culoareFete[fataSelectata][0]); // R
        else if(i == 31)
            s = to_string(obj.culoareFete[fataSelectata][1]); // G
        else
            s = to_string(obj.culoareFete[fataSelectata][2]); // B
        
        sprintf(ss, s.c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 37 && i <= 39) {
        //display the coordinates of the selected object
        if(i == 37)
            if(obj.centru.x  > -0.01 && obj.centru.x < 0.01)
                s = "0.00";
            else
                s = to_string(obj.centru.x * 10.0);
        else if(i == 38)
            if(obj.centru.y  > -0.01 && obj.centru.y < 0.01)
                s = "0.00";
            else
                s = to_string(-obj.centru.y * 10);
        else if(obj.centru.z  > -0.01 && obj.centru.z < 0.01)
                s = "0.00";
            else
                s = to_string(obj.centru.z * 10.0);
        
        AddDecimals(text, s);

        sprintf(ss, text);
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 41 && i <= 43) {
        //Display the rotation of the selected object
        if(i == 41) {
            if(obj.rotatieX > -0.01 && obj.rotatieX < 0.01)
                s = "0.00";
            else if(!max360) {
                s = to_string(obj.rotatieX * 180 / 3.14);
            }
            else {
                double unghi;
                double fractie = modf(obj.rotatieX * 180 / 3.14, &unghi);
                unghi = static_cast<int>(unghi) % 360;
                if(unghi < 0)
                    unghi += 360;
                s = to_string(unghi + fractie);
            }
        }
        else if(i == 42) {
            if(obj.rotatieY > -0.01 && obj.rotatieY < 0.01)
                s = "0.00";
            else if(!max360)
                s = to_string(obj.rotatieY * 180 / 3.14);
            else {
                double unghi;
                double fractie = modf(obj.rotatieY * 180 / 3.14, &unghi);
                unghi = static_cast<int>(unghi) % 360;
                if(unghi < 0)
                    unghi += 360;
                s = to_string(unghi + fractie);
            }
        }
        else {
            if(obj.rotatieZ > -0.01 && obj.rotatieZ < 0.01)
                s = "0.00";
            else if(!max360)
                s = to_string(obj.rotatieZ * 180 / 3.14);
            else {
                double unghi;
                double fractie = modf(obj.rotatieZ * 180 / 3.14, &unghi);
                unghi = static_cast<int>(unghi) % 360;
                if(unghi < 0)
                    unghi += 360;
                s = to_string(unghi + fractie);
            }
        }
        
        AddDecimals(text, s);

        sprintf(ss, text);
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 45 && i <= 47) {
        //Display the size of the selected object
        if(i == 45) {
            if(obj.marimeX  > -0.01 && obj.marimeX < 0.01)
                s = "0.00";
            else
                s = to_string(obj.marimeX);
        }
        else if(i == 46) {
            if(obj.marimeY  > -0.01 && obj.marimeY < 0.01)
                s = "0.00";
            else
                s = to_string(obj.marimeY);
        }
        else {
            if(obj.marimeZ  > -0.01 && obj.marimeZ < 0.01)
                s = "0.00";
            else
                s = to_string(obj.marimeZ);
        }

        AddDecimals(text, s);

        sprintf(ss, text);
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
    else if(i >= 48 && i <= 50) {
        //Display the move/rotation/size coeficient
        if(i == 48)
            s = to_string(coeficientDeplasare); //move
        else if(i == 49)
            s = to_string(unghiRotatie * 180 / 3.14); //rotation
        else
            s = to_string(coeficientMarire); //size
        
        AddDecimals(text, s);

        sprintf(ss, text);
        outtextxy(mijlocLatime - textwidth(ss) / 2, mijlocInaltime - textheight(ss) / 2, ss);
    }
}

void DrawCheckBox(const char* text, const bool &active, int &mijlocInaltime, int &limitaInaltime, const int &mijlocLatime, const int &paddingLatime, const int &paddingInaltime, const int &index, const int &paddingInaltimeCheckMark, const vector<int> &boxCoordinates) {
    char ss[200];

    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) text);
    outtextxy(mijlocLatime - paddingLatime, limitaInaltime + paddingInaltime, ss);

    setcolor(BLACK);
    rectangle(boxCoordinates[0], boxCoordinates[1], boxCoordinates[2], boxCoordinates[3]);

    setfillstyle(SOLID_FILL, COLOR(70, 70, 70));
    coordonateInputBox[index] = {boxCoordinates[0] + 1, boxCoordinates[1] + 1, boxCoordinates[2] - 1, boxCoordinates[3] - 1};
    bar(coordonateInputBox[index][0], coordonateInputBox[index][1], coordonateInputBox[index][2], coordonateInputBox[index][3]);
    
    if(active) {
        setcolor(WHITE);
        for(int j = 1; j < 6; j++)
            circle(boxCoordinates[0] + 10, mijlocInaltime - paddingInaltimeCheckMark, j);
    }
}

void DrawInputBoxes(const char* text, const Obiect &obj, const int &index, int &mijlocInaltime, int &limitaInaltime, const int &mijlocLatime, const int &lungimeInputBox, const int &inaltimeInputBox) {
    char ss[200];

    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) text);
    outtextxy(mijlocLatime - textwidth((char*) text) / 2, limitaInaltime, ss);

    DeseneazaCasutaInput(obj, (char*) "X:  ", index, mijlocLatime, mijlocInaltime, lungimeInputBox, inaltimeInputBox, limitaInaltime);
    mijlocInaltime += 35;
    limitaInaltime += 35;
    DeseneazaCasutaInput(obj, (char*) "Y:  ", index + 1, mijlocLatime, mijlocInaltime, lungimeInputBox, inaltimeInputBox, limitaInaltime);
    mijlocInaltime += 35;
    limitaInaltime += 35;
    DeseneazaCasutaInput(obj, (char*) "Z:  ", index + 2, mijlocLatime, mijlocInaltime, lungimeInputBox, inaltimeInputBox, limitaInaltime);
}

void DrawRGBBoxes(const char* text, const Obiect &obj, const int &index, int &mijlocInaltime, int &limitaInaltime, const int &mijlocLatime, const int &lungimeInputBox, const int &inaltimeInputBox, const int &paddingInaltime) {
    char ss[200];

    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) text);
    outtextxy(mijlocLatime - textwidth((char*) text) / 2, limitaInaltime + paddingInaltime, ss);

    mijlocInaltime += 35;
    limitaInaltime += 35;

    DeseneazaCasutaInput(obj, "R:  ", index, mijlocLatime - 67, mijlocInaltime, lungimeInputBox - 50, inaltimeInputBox, limitaInaltime);
    DeseneazaCasutaInput(obj, "G:  ", index + 1, mijlocLatime + 13, mijlocInaltime, lungimeInputBox - 50, inaltimeInputBox, limitaInaltime);
    DeseneazaCasutaInput(obj, "B:  ", index + 2, mijlocLatime + 93, mijlocInaltime, lungimeInputBox - 50, inaltimeInputBox, limitaInaltime);
}

void DrawClickableButton(char* text, const int &mijlocInaltime, const int &limitaInaltime, const int &mijlocLatime, const int &index) {
    char ss[200];

    coordonateInputBox[index] = {mijlocLatime - textwidth(text) / 2 - 5, mijlocInaltime - textheight(text) / 2 - 5, mijlocLatime + textwidth(text) / 2 + 5, mijlocInaltime + textheight(text) / 2 + 5};

    setcolor(COLOR(90, 90, 90));
    rectangle(coordonateInputBox[index][0] - 1, coordonateInputBox[index][1] - 1, coordonateInputBox[index][2] + 1, coordonateInputBox[index][3] + 1);

    setfillstyle(SOLID_FILL, COLOR(65, 65, 65));
    bar(coordonateInputBox[index][0], coordonateInputBox[index][1], coordonateInputBox[index][2], coordonateInputBox[index][3]);

    setcolor(WHITE);
    setbkcolor(COLOR(65, 65, 65));
    sprintf(ss, text);
    outtextxy(mijlocLatime - textwidth(text) / 2, limitaInaltime + 30, ss);
}

void DeseneazaBaraLateralaDreaptaPuncte(const Obiect &obj) {
    int lungimeInputBox = 100, inaltimeInputBox = 25;
    char ss[200];

    setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
    int limitaStanga = lungimeFereastra - 250, limitaInaltime = 40;
    bar(limitaStanga, inaltimeFereastra / 35, lungimeFereastra, inaltimeFereastra);

    int mijlocLatime = limitaStanga + (lungimeFereastra - limitaStanga) / 2;
    int mijlocInaltime = limitaInaltime + 3 * inaltimeInputBox / 2;

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, inaltimeFereastra / 35, limitaStanga + 7, inaltimeFereastra);

    DrawCheckBox("PUNCTE:  ", deseneazaPuncte, mijlocInaltime, limitaInaltime, mijlocLatime, 40, 0, 21, 30, {mijlocLatime + 30, mijlocInaltime - 40, mijlocLatime + 50, mijlocInaltime - 20});

    mijlocInaltime += 15;
    limitaInaltime += 15;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime - 15, lungimeFereastra, mijlocInaltime - 20);

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawInputBoxes("POZITIE", obj, 0, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox);

    mijlocInaltime += 20;
    limitaInaltime += 20;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime + 15, lungimeFereastra, mijlocInaltime + 10);

    mijlocInaltime += 30;
    limitaInaltime += 30;
    DrawRGBBoxes("CULOARE PUNCTE", obj, 22, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox, 35);

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawCheckBox("AXE:  ", axePunct, mijlocInaltime, limitaInaltime, mijlocLatime, 40, 30, 9, 0, {mijlocLatime + 5, mijlocInaltime - 10, mijlocLatime + 25, mijlocInaltime + 10});

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawCheckBox("CULOARE PCT SELECT:  ", colorarePuncteSelectate, mijlocInaltime, limitaInaltime, mijlocLatime, 95, 30, 10, 0, {mijlocLatime + 70, mijlocInaltime - 10, mijlocLatime + 90, mijlocInaltime + 10});

    if(colorarePuncteSelectate) {
        mijlocInaltime += 35;
        limitaInaltime += 35;
        DrawRGBBoxes("CULOARE", obj, 11, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox, 30);
    }

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawCheckBox("SELECTARE MULTIPLA:  ", selectarePuncte, mijlocInaltime, limitaInaltime, mijlocLatime, 96, 30, 14, 0, {mijlocLatime + 70, mijlocInaltime - 10, mijlocLatime + 90, mijlocInaltime + 10});

    mijlocInaltime += 15;
    limitaInaltime += 15;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime + 15, lungimeFereastra, mijlocInaltime + 10);

    mijlocInaltime += 35;
    limitaInaltime += 35;
    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) "UNIRE PUNCTE");
    outtextxy(mijlocLatime - textwidth((char*) "UNIRE PUNCTE") / 2, limitaInaltime + 30, ss);

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawCheckBox("UNESTE:  ", unestePuncte, mijlocInaltime, limitaInaltime, mijlocLatime, 40, 30, 17, 0, {mijlocLatime + 30, mijlocInaltime - 10, mijlocLatime + 50, mijlocInaltime + 10});

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawClickableButton((char*) "PRIMUL -> FIECARE", mijlocInaltime, limitaInaltime, mijlocLatime, 15);

    mijlocInaltime += 45;
    limitaInaltime += 45;
    DrawClickableButton((char*) "CONSECUTIVE", mijlocInaltime, limitaInaltime, mijlocLatime, 16);

    mijlocInaltime += 20;
    limitaInaltime += 20;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime + 15, lungimeFereastra, mijlocInaltime + 10);

    mijlocInaltime += 40;
    limitaInaltime += 40;
    DrawCheckBox("ADAUGA PUNCTE:  ", adaugaPunct, mijlocInaltime, limitaInaltime, mijlocLatime, 80, 30, 18, 0, {mijlocLatime + 50, mijlocInaltime - 10, mijlocLatime + 70, mijlocInaltime + 10});

    mijlocInaltime += 40;
    limitaInaltime += 40;
    DrawCheckBox("ELIMINA PUNCTE:  ", eliminaPuncte, mijlocInaltime, limitaInaltime, mijlocLatime, 80, 30, 19, 0, {mijlocLatime + 50, mijlocInaltime - 10, mijlocLatime + 70, mijlocInaltime + 10});
}

void DeseneazaBaraLateralaDreaptaMuchii(const Obiect &obj) {
    int lungimeInputBox = 100, inaltimeInputBox = 25;

    setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
    int limitaStanga = lungimeFereastra - 250, limitaInaltime = 40;
    bar(limitaStanga, inaltimeFereastra / 35, lungimeFereastra, inaltimeFereastra);

    int mijlocLatime = limitaStanga + (lungimeFereastra - limitaStanga) / 2;
    int mijlocInaltime = limitaInaltime + 3 * inaltimeInputBox / 2;

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, inaltimeFereastra / 35, limitaStanga + 7, inaltimeFereastra);

    DrawCheckBox("MUCHII:  ", deseneazaMuchii, mijlocInaltime, limitaInaltime, mijlocLatime, 40, 0, 25, 30, {mijlocLatime + 30, mijlocInaltime - 40, mijlocLatime + 50, mijlocInaltime - 20});

    DrawRGBBoxes("CULOARE MUCHII", obj, 26, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox, 35);

    mijlocInaltime += 30;
    limitaInaltime += 30;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime + 5, lungimeFereastra, mijlocInaltime);

    mijlocInaltime += 55;
    limitaInaltime += 55;
    DrawCheckBox("FETE:  ", deseneazaFete, mijlocInaltime, limitaInaltime, mijlocLatime, 30, 0, 29, 30, {mijlocLatime + 20, mijlocInaltime - 40, mijlocLatime + 40, mijlocInaltime - 20});

    DrawRGBBoxes( "CULOARE FATA", obj, 30, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox, 35);

    mijlocInaltime += 45;
    limitaInaltime += 45;
    DrawClickableButton((char*) " COPIE ", mijlocInaltime, limitaInaltime, mijlocLatime, 33);

    mijlocInaltime += 45;
    limitaInaltime += 45;
    DrawClickableButton((char*) " LIPIRE ", mijlocInaltime, limitaInaltime, mijlocLatime, 34);

    mijlocInaltime += 45;
    limitaInaltime += 45;
    DrawClickableButton((char*) "CREARE FATA", mijlocInaltime, limitaInaltime, mijlocLatime, 20);

    mijlocInaltime += 30;
    limitaInaltime += 30;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime + 5, lungimeFereastra, mijlocInaltime);

    mijlocInaltime += 60;
    limitaInaltime += 60;
    DrawCheckBox("XRAY:  ", xRay, mijlocInaltime, limitaInaltime, mijlocLatime, 30, 0, 35, 30, {mijlocLatime + 20, mijlocInaltime - 40, mijlocLatime + 40, mijlocInaltime - 20});
}

void DeseneazaBaraLateralaDreaptaObiect(const Obiect &obj) {
    int lungimeInputBox = 100, inaltimeInputBox = 25;
    char ss[200];

    setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
    int limitaStanga = lungimeFereastra - 250, limitaInaltime = 40;
    bar(limitaStanga, inaltimeFereastra / 35, lungimeFereastra, inaltimeFereastra);

    int mijlocLatime = limitaStanga + (lungimeFereastra - limitaStanga) / 2;
    int mijlocInaltime = limitaInaltime + 3 * inaltimeInputBox / 2;

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, inaltimeFereastra / 35, limitaStanga + 7, inaltimeFereastra);

    DrawCheckBox("ACTIV:  ", obj.activ, mijlocInaltime, limitaInaltime, mijlocLatime, 30, 0, 36, 30, {mijlocLatime + 30, mijlocInaltime - 40, mijlocLatime + 50, mijlocInaltime - 20});

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime, lungimeFereastra, mijlocInaltime - 5);

    mijlocInaltime += 50;
    limitaInaltime += 50;
    DrawInputBoxes("POZITIE", obj, 37, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox);

    mijlocInaltime += 40;
    limitaInaltime += 40;
    DeseneazaCasutaInput(obj, (char*) "COEFICIENT:  ", 48, mijlocLatime + 50, mijlocInaltime, lungimeInputBox - 30, inaltimeInputBox, limitaInaltime);

    mijlocInaltime += 35;
    limitaInaltime += 35;
    DrawCheckBox("AXE:  ", axeMiscareObiect, mijlocInaltime, limitaInaltime, mijlocLatime, 30, 35, 40, -5, {mijlocLatime + 20, mijlocInaltime - 5, mijlocLatime + 40, mijlocInaltime + 15});

    mijlocInaltime += 20;
    limitaInaltime += 20;
    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime + 15, lungimeFereastra, mijlocInaltime + 10);

    mijlocInaltime += 65;
    limitaInaltime += 65;
    DrawInputBoxes("ROTATIE", obj, 41, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox);

    mijlocInaltime += 40;
    limitaInaltime += 40;
    DeseneazaCasutaInput(obj, (char*) "COEFICIENT:  ", 49, mijlocLatime + 50, mijlocInaltime, lungimeInputBox - 30, inaltimeInputBox, limitaInaltime);

    mijlocInaltime += 70;
    limitaInaltime += 70;
    DrawCheckBox("MAX 360:  ", max360, mijlocInaltime, limitaInaltime, mijlocLatime, 45, 0, 44, 30, {mijlocLatime + 30, mijlocInaltime - 40, mijlocLatime + 50, mijlocInaltime - 20});

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaStanga, mijlocInaltime, lungimeFereastra, mijlocInaltime - 5);

    mijlocInaltime += 50;
    limitaInaltime += 50;
    DrawInputBoxes("MARIME", obj, 45, mijlocInaltime, limitaInaltime, mijlocLatime, lungimeInputBox, inaltimeInputBox);

    mijlocInaltime += 40;
    limitaInaltime += 40;
    DeseneazaCasutaInput(obj, (char*) "COEFICIENT:  ", 50, mijlocLatime + 50, mijlocInaltime, lungimeInputBox - 30, inaltimeInputBox, limitaInaltime);
}

void DeseneazaBaraLateralaDreapta(const Obiect &obj) {
    if(fereastraDreapta == 1)
        DeseneazaBaraLateralaDreaptaPuncte(obj);
    else if(fereastraDreapta == 2)
        DeseneazaBaraLateralaDreaptaMuchii(obj);
    else if(fereastraDreapta == 3)
        DeseneazaBaraLateralaDreaptaObiect(obj);
}

void isHoverBaraStanga(const int &i) {
    if(i == butonHover) {
        setfillstyle(SOLID_FILL, COLOR(80, 80, 80));
        setbkcolor(COLOR(80, 80, 80));
    }
}

void DeseneazaBaraLateralaStangaPuncte(const Obiect &obj) {
    char ss[20];
    int limitaDreapta = 140, limitaInaltime = 30;
    int mijlocLatime = 70, len = min(24, static_cast<int>(obj.varfuri.size()));

    setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
    bar(0, inaltimeFereastra / 35, limitaDreapta, inaltimeFereastra);

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaDreapta, inaltimeFereastra / 35, limitaDreapta + 7, inaltimeFereastra);

    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) "TOTAL: ");
    if(obiectSelectat != -1) {
        strcat(ss, to_string(static_cast<int>(obj.varfuri.size())).c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);
    }
    else {
        strcat(ss, "0");
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);

        return;
    }

    bool culoare = true;
    for(int i = 1; i <= len; i++) {
        limitaInaltime += 30;

        if(culoare) {
            setfillstyle(SOLID_FILL, COLOR(60, 60, 60));
            setbkcolor(COLOR(60, 60, 60));
        }
        else {
            setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
            setbkcolor(COLOR(50, 50, 50));
        }

        isHoverBaraStanga(9 + i);

        if(i - 1 + indexStart == varfSelectat || find(puncteSelectate.begin(), puncteSelectate.end(), i - 1 + indexStart) != puncteSelectate.end()) {
            setfillstyle(SOLID_FILL, COLOR(80, 80, 80));
            setbkcolor(COLOR(80, 80, 80));
        }

        coordonateButoaneHover[9 + i] = {0, limitaInaltime - textheight(ss) + 9, limitaDreapta, limitaInaltime + textheight(ss) + 7};
        bar(coordonateButoaneHover[9 + i][0], coordonateButoaneHover[9 + i][1], coordonateButoaneHover[9 + i][2], coordonateButoaneHover[9 + i][3]);

        sprintf(ss, (char*) "Punct ");
        strcat(ss, to_string(i + indexStart).c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);

        culoare = !culoare;
    }
}

void DeseneazaBaraLateralaStangaFete(const Obiect &obj) {
    char ss[20];
    int limitaDreapta = 140, limitaInaltime = 30;
    int mijlocLatime = 70, len = min(24, static_cast<int>(obj.fete.size()));

    setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
    bar(0, inaltimeFereastra / 35, limitaDreapta, inaltimeFereastra);

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaDreapta, inaltimeFereastra / 35, limitaDreapta + 7, inaltimeFereastra);

    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) "TOTAL: ");
    if(obiectSelectat != -1) {
        strcat(ss, to_string(static_cast<int>(obj.fete.size())).c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);
    }
    else {
        strcat(ss, "0");
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);

        return;
    }

    bool culoare = true;
    for(int i = 1; i <= len; i++) {
        limitaInaltime += 30;

        if(culoare) {
            setfillstyle(SOLID_FILL, COLOR(60, 60, 60));
            setbkcolor(COLOR(60, 60, 60));
        }
        else {
            setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
            setbkcolor(COLOR(50, 50, 50));
        }

        isHoverBaraStanga(9 + i);

        if(obj.indexFata[i - 1 + indexStart] == fataSelectata) {
            setfillstyle(SOLID_FILL, COLOR(80, 80, 80));
            setbkcolor(COLOR(80, 80, 80));
        }

        coordonateButoaneHover[9 + i] = {0, limitaInaltime - textheight(ss) + 9, limitaDreapta, limitaInaltime + textheight(ss) + 7};
        bar(coordonateButoaneHover[9 + i][0], coordonateButoaneHover[9 + i][1], coordonateButoaneHover[9 + i][2], coordonateButoaneHover[9 + i][3]);

        sprintf(ss, (char*) "Fata ");
        strcat(ss, to_string(i + indexStart).c_str());
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);

        culoare = !culoare;
    }
}

void DeseneazaBaraLateralaStangaObiecte() {
    char ss[20];
    int limitaDreapta = 140, limitaInaltime = 30;
    int mijlocLatime = 70, len = min(24, static_cast<int>(obiecte.size()));

    setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
    bar(0, inaltimeFereastra / 35, limitaDreapta, inaltimeFereastra);

    setfillstyle(SOLID_FILL, COLOR(40, 40, 40));
    bar(limitaDreapta, inaltimeFereastra / 35, limitaDreapta + 7, inaltimeFereastra);

    setcolor(WHITE);
    setbkcolor(COLOR(50, 50, 50));
    sprintf(ss, (char*) "TOTAL: ");
    strcat(ss, to_string(static_cast<int>(obiecte.size())).c_str());
    outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);

    bool culoare = true;
    for(int i = 1; i <= len; i++) {
        limitaInaltime += 30;

        if(culoare) {
            setfillstyle(SOLID_FILL, COLOR(60, 60, 60));
            setbkcolor(COLOR(60, 60, 60));
        }
        else {
            setfillstyle(SOLID_FILL, COLOR(50, 50, 50));
            setbkcolor(COLOR(50, 50, 50));
        }

        isHoverBaraStanga(9 + i);

        if(find(obiecteSelectate.begin(), obiecteSelectate.end(), i + indexStart - 1) != obiecteSelectate.end()) {
            setfillstyle(SOLID_FILL, COLOR(80, 80, 80));
            setbkcolor(COLOR(80, 80, 80));
        }

        coordonateButoaneHover[9 + i] = {0, limitaInaltime - textheight(ss) + 9, limitaDreapta, limitaInaltime + textheight(ss) + 7};
        bar(coordonateButoaneHover[9 + i][0], coordonateButoaneHover[9 + i][1], coordonateButoaneHover[9 + i][2], coordonateButoaneHover[9 + i][3]);

        sprintf(ss, (char*) "Obiect ");
        strcat(ss, to_string(i + indexStart).c_str());
        if(!obiecte[i - 1 + indexStart].activ)
            setcolor(DARKGRAY);
        outtextxy(mijlocLatime - textwidth(ss) / 2, limitaInaltime, ss);
        if(!obiecte[i - 1 + indexStart].activ)
            setcolor(WHITE);
        
        culoare = !culoare;
    }
}

void DeseneazaBaraLateralaStanga(const Obiect &obj) {
    if(fereastraStanga == 1)
        DeseneazaBaraLateralaStangaPuncte(obj);
    else if(fereastraStanga == 2) 
        DeseneazaBaraLateralaStangaFete(obj);
    else if(fereastraStanga == 3)
        DeseneazaBaraLateralaStangaObiecte();
}

void DeseneazaObiect(Obiect &obj) {
    if(!obj.activ || static_cast<int>(obj.varfuri.size()) == 0)
        return;

    if(!xRay)
        SorteazaFetele(obj);

    vector<Punct2D> proiectii2D(static_cast<int>(obj.varfuri.size()));

    for (int i = 0; i < obj.varfuri.size(); i++)
        proiectii2D[i] = Transforma2D(obj.varfuri[i]);

    vector<bool> vectorFrecventa(static_cast<int>(obj.varfuri.size()), false);
    vector<bool> vectorFrecventaMuchii(static_cast<int>(obj.muchii.size()), false);

    vector<int> pct;
    for(int i = 0; i < obj.varfuri.size(); i++) {
        obj.varfuri[i].x -= obj.centru.x;
        obj.varfuri[i].y -= obj.centru.y;
        obj.varfuri[i].z -= obj.centru.z;
    }

    for(int i = 0; i < obj.varfuri.size(); i++)
        if(obj.varfuri[i].x < 0)
            pct.push_back(i);
    
    for(int i = 0; i < obj.varfuri.size(); i++) {
        obj.varfuri[i].x += obj.centru.x;
        obj.varfuri[i].y += obj.centru.y;
        obj.varfuri[i].z += obj.centru.z;
    }

    for(int i = 0; i < obj.fete.size(); i++) {
        if(i == fataSelectata && nrObiect == obiectSelectat)
            if(obj.culoareFete[i][0] <= 10 && obj.culoareFete[i][1] <= 10 && obj.culoareFete[i][2] <= 10)
                setfillstyle(XHATCH_FILL, WHITE);
            else
                setfillstyle(XHATCH_FILL, COLOR(obj.culoareFete[i][0], obj.culoareFete[i][1], obj.culoareFete[i][2]));
        else
            if(deseneazaFete)
                setfillstyle(SOLID_FILL, COLOR(obj.culoareFete[i][0], obj.culoareFete[i][1], obj.culoareFete[i][2]));
            else
                setfillstyle(SOLID_FILL, BLACK);

        vector<int> puncte(2 * static_cast<int>(obj.fete[i].size()));

        if(!xRay)
            for(int j = 0; j < obj.fete[i].size(); j++) {
                puncte[2 * j] = proiectii2D[obj.fete[i][j]].x;
                puncte[2 * j + 1] = proiectii2D[obj.fete[i][j]].y;
            }
        
        if(deseneazaMuchii)
            setcolor(COLOR(culoareMuchii[0], culoareMuchii[1], culoareMuchii[2]));
        else
            if(deseneazaFete)
                setcolor(COLOR(obj.culoareFete[i][0],obj.culoareFete[i][1], obj.culoareFete[i][2]));
            else
                setcolor(BLACK);

        if(!xRay)
            fillpoly(static_cast<int>(obj.fete[i].size()), puncte.data());
        else {
            for(int j = 0; j < obj.fete[i].size(); j++) {
                line(proiectii2D[obj.fete[i][j]].x, proiectii2D[obj.fete[i][j]].y, proiectii2D[obj.fete[i][(j + 1) % obj.fete[i].size()]].x, proiectii2D[obj.fete[i][(j + 1) % obj.fete[i].size()]].y);
            }
        }
        
        if(deseneazaPuncte) {
            for(int j = 0; j < obj.fete[i].size(); j++) {
                if(selectarePuncte && colorarePuncteSelectate && find(puncteSelectate.begin(), puncteSelectate.end(), obj.fete[i][j]) != puncteSelectate.end() && nrObiect == obiectSelectat)
                    setcolor(COLOR(culoarePuncteSelectate[0], culoarePuncteSelectate[1], culoarePuncteSelectate[2]));
                else if(varfSelectat == obj.fete[i][j] && colorarePuncteSelectate && !unestePuncte  && nrObiect == obiectSelectat)
                    setcolor(COLOR(culoarePuncteSelectate[0], culoarePuncteSelectate[1], culoarePuncteSelectate[2]));
                else
                    setcolor(COLOR(culoarePuncte[0], culoarePuncte[1], culoarePuncte[2]));
                
                /* if(find(pct.begin(), pct.end(), obj.fete[i][j]) != pct.end())
                    setcolor(RED);
                else
                    setcolor(WHITE); */
                
                for(int k = 1; k <= (double) razaPunct - 100 / zoom + 1; k++)
                    circle(proiectii2D[obj.fete[i][j]].x, proiectii2D[obj.fete[i][j]].y, k);

                vectorFrecventa[obj.fete[i][j]] = true;
            }
        }
   }

    if(deseneazaPuncte) {
        for(int i = 0; i < vectorFrecventa.size(); i++)
            if(!vectorFrecventa[i]) {
                if(selectarePuncte && nrObiect == obiectSelectat && colorarePuncteSelectate && find(puncteSelectate.begin(), puncteSelectate.end(), i) != puncteSelectate.end())
                    setcolor(COLOR(culoarePuncteSelectate[0], culoarePuncteSelectate[1], culoarePuncteSelectate[2]));
                else if(varfSelectat == i && colorarePuncteSelectate && !unestePuncte && nrObiect == obiectSelectat)
                    setcolor(COLOR(culoarePuncteSelectate[0], culoarePuncteSelectate[1], culoarePuncteSelectate[2]));
                else
                    setcolor(COLOR(culoarePuncte[0], culoarePuncte[1], culoarePuncte[2]));
                
                /* if(find(pct.begin(), pct.end(), i) != pct.end())
                    setcolor(RED);
                else
                    setcolor(WHITE); */
                
                for(int j = 1; j <= razaPunct; j++)
                    circle(proiectii2D[i].x, proiectii2D[i].y, j);
            }
    }

    if(deseneazaMuchii) {
        setcolor(COLOR(culoareMuchii[0], culoareMuchii[1], culoareMuchii[2]));

        for(const pair<int, int> &muchie : obj.muchii) {
            Punct2D punctulA = Transforma2D(obj.varfuri[muchie.first]);
            Punct2D punctulB = Transforma2D(obj.varfuri[muchie.second]);

            line(proiectii2D[muchie.first].x, proiectii2D[muchie.first].y, proiectii2D[muchie.second].x, proiectii2D[muchie.second].y);
        }
    }

    setcolor(WHITE);
}

void DeseneazaAxePunct(const Obiect &obj) {
    Punct2D centruObiect = Transforma2D(obj.centru);
    Punct2D centruPtAxe = Transforma2D(obj.axeObiectStabile[0]);

    int modificax = 450, modificay = 320;
    if(fereastraDreapta == 0)
        modificax = 700;

    /* if(axeObiectSelectat == 2) {
        circle(centruPtAxe.x + modificax, centruPtAxe.y - modificay, 45);
        setfillstyle(SOLID_FILL, COLOR(37, 150, 190));
        floodfill(centruPtAxe.x + modificax, centruPtAxe.y - modificay, WHITE);
    } */

    setcolor(YELLOW);
    Punct2D axaOx;

    if((!axeMiscareObiect && axeObiectSelectat == 1) || (axeMiscareObiect && local)) {
        axaOx = Transforma2D(obj.axaOX);
        line(centruObiect.x, centruObiect.y, axaOx.x, axaOx.y);
    }

    if(axeObiectSelectat == 2) {
        double saveZoom = zoom;
        zoom = 100;
        axaOx = Transforma2D(obj.axeObiectStabile[1]);
        zoom = saveZoom;

        line(centruPtAxe.x + modificax, centruPtAxe.y - modificay, axaOx.x + modificax, axaOx.y - modificay);    
    }

    if(axeMiscareObiect && !local) {
        axaOx = Transforma2D({obj.centru.x + 0.5, obj.centru.y, obj.centru.z});
        line(centruObiect.x, centruObiect.y, axaOx.x, axaOx.y);
    }

    setcolor(RED);
    Punct2D axaOy;

    if((!axeMiscareObiect && axeObiectSelectat == 1) || (axeMiscareObiect && local)) {
        axaOy = Transforma2D(obj.axaOY);
        line(centruObiect.x, centruObiect.y, axaOy.x, axaOy.y);
    }

    if(axeObiectSelectat == 2) {
        double saveZoom = zoom;
        zoom = 100;
        axaOy = Transforma2D(obj.axeObiectStabile[2]);
        zoom = saveZoom;

        line(centruPtAxe.x + modificax, centruPtAxe.y - modificay, axaOy.x + modificax, axaOy.y - modificay);    
    }

    if(axeMiscareObiect && !local) {
        axaOy = Transforma2D({obj.centru.x, obj.centru.y - 0.5, obj.centru.z});
        line(centruObiect.x, centruObiect.y, axaOy.x, axaOy.y);
    }

    setcolor(GREEN);
    Punct2D axaOz;

    if((!axeMiscareObiect && axeObiectSelectat == 1) || (axeMiscareObiect && local)) {
        axaOz = Transforma2D(obj.axaOZ);
        line(centruObiect.x, centruObiect.y, axaOz.x, axaOz.y);
    }

    if(axeObiectSelectat == 2) {
        double saveZoom = zoom;
        zoom = 100;
        axaOz = Transforma2D(obj.axeObiectStabile[3]);
        zoom = saveZoom;

        line(centruPtAxe.x + modificax, centruPtAxe.y - modificay, axaOz.x + modificax, axaOz.y - modificay);    
    }

    if(axeMiscareObiect && !local) {
        axaOz = Transforma2D({obj.centru.x + 0.25, obj.centru.y - 0.25, obj.centru.z});
        line(centruObiect.x, centruObiect.y, axaOz.x, axaOz.y);
    }

    setcolor(WHITE);

    if(varfSelectat != -1 && axePunct && !unestePuncte && !eliminaPuncte) {
        Punct2D varfSelectat2D = Transforma2D(obj.varfuri[varfSelectat]);
        Punct2D axaOx2;

        setcolor(YELLOW);
        if(local)
            axaOx2 = Transforma2D(obj.axePunctSelectat[0]);
        else
            axaOx2 = Transforma2D({obj.varfuri[varfSelectat].x + 0.5, obj.varfuri[varfSelectat].y, obj.varfuri[varfSelectat].z});
        line(varfSelectat2D.x, varfSelectat2D.y, axaOx2.x, axaOx2.y);

        setcolor(RED);
        if(local)
            axaOy = Transforma2D(obj.axePunctSelectat[1]);
        else
            axaOy = Transforma2D({obj.varfuri[varfSelectat].x, obj.varfuri[varfSelectat].y - 0.5, obj.varfuri[varfSelectat].z});
        line(varfSelectat2D.x, varfSelectat2D.y, axaOy.x, axaOy.y);

        setcolor(GREEN);
        if(local)
            axaOz = Transforma2D(obj.axePunctSelectat[2]);
        else 
            axaOz = Transforma2D({obj.varfuri[varfSelectat].x + 0.25, obj.varfuri[varfSelectat].y - 0.25, obj.varfuri[varfSelectat].z});
        line(varfSelectat2D.x, varfSelectat2D.y, axaOz.x, axaOz.y);

        setcolor(WHITE);
    }

    if(unestePuncte && varfSelectat != -1)
        line(pozitieMouseUnirePuncte.x, pozitieMouseUnirePuncte.y, Transforma2D(obj.varfuri[varfSelectat]).x, Transforma2D(obj.varfuri[varfSelectat]).y);
}

void Deseneaza(Obiect &obj) {
    long long int verticesCount = 0;

    nrObiect = 0;

    if(fereastraDreapta == 0)
        cleardevice();
    else {
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, inaltimeFereastra / 35, lungimeFereastra - 250, inaltimeFereastra);
    }

    if(butonGrid) {
        vector<Punct2D> proiectii2DGrid;

        verticesCount += static_cast<long long int>(grid.varfuri.size());

        for(const Punct3D &i : grid.varfuri)
            proiectii2DGrid.push_back(Transforma2D(i)); 
        
        setcolor(DARKGRAY);
        for(int i = 0; i < grid.muchii.size(); i++) {
            if(find(col.begin(), col.end(), grid.muchii[i].first) != col.end() || find(col.begin(), col.end(), grid.muchii[i].second) != col.end())
                setcolor(BLUE);
            else
                setcolor(WHITE);
            
            line(proiectii2DGrid[grid.muchii[i].first].x, proiectii2DGrid[grid.muchii[i].first].y, proiectii2DGrid[grid.muchii[i].second].x, proiectii2DGrid[grid.muchii[i].second].y);
        }
    }

    for(Obiect &obj2 : obiecte) {
        DeseneazaObiect(obj2);
        nrObiect++;

        if(obj2.activ)
            verticesCount += static_cast<long long int>(obj2.varfuri.size());
    }
    
    if(obiectSelectat != -1 && obiecte[obiectSelectat].activ)
        DeseneazaAxePunct(obiecte[obiectSelectat]);

    if(obiectSelectat != -1) {
        DeseneazaBaraLateralaDreapta(obiecte[obiectSelectat]);
        DeseneazaBaraLateralaStanga(obiecte[obiectSelectat]);
    }
    else {
        DeseneazaBaraLateralaDreapta(obj);
        DeseneazaBaraLateralaStanga(obj);
    }

    DeseneazaBaraComenzi(); 

    if(modificaPagina) {
        pagina = 1 - pagina;

        setactivepage(pagina); 
        setvisualpage(1 - pagina);
    }

    int performanceCount = 0;
    if(verticesCount < 150)
        performanceCount = 4;
    else if(verticesCount < 250)
        performanceCount = 3;
    else if(verticesCount < 350)
        performanceCount = 2;
    else if(verticesCount < 500)
        performanceCount = 1;

    performanceCount -= deseneazaPuncte;
    performanceCount -= axePunct;

    if(performanceCount > 0)
        delay(performanceCount);
}
