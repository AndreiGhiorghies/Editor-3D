#include "../Headers/Utils.h"

void operator-=(Punct3D &obj1, Punct3D &obj2) {
    obj1.x -= obj2.x;
    obj1.y -= obj2.y;
    obj1.z -= obj2.z;
}

void operator+=(Punct3D &obj1, Punct3D &obj2) {
    obj1.x += obj2.x;
    obj1.y += obj2.y;
    obj1.z += obj2.z;
}

Punct2D Transforma2D(const Punct3D &punct) {
    double x = lungimeFereastra / 2 + (punct.x * POV) / (punct.z + POV) * zoom;
    double y = inaltimeFereastra / 2 + (punct.y * POV) / (punct.z + POV) * zoom;

    return {x, y};
}

Punct3D GetMijlocObiect(const Obiect &obj) {
    double x = 0, y = 0, z = 0;

    for(int i = 0; i < obj.varfuri.size(); i++) {
        x += obj.varfuri[i].x;
        y += obj.varfuri[i].y;
        z += obj.varfuri[i].z;
    }
    
    return {x / (double) obj.varfuri.size(), y / (double) obj.varfuri.size(), z / (double) obj.varfuri.size()};
}

void CentreazaObiect(Obiect &obj) {
    for(int i = 0; i < obj.varfuri.size(); i++)
        obj.varfuri[i] -= obj.centru;
    
    obj.axaOX -= obj.centru;
    obj.axaOY -= obj.centru;
    obj.axaOZ -= obj.centru;

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i] -= obj.centru;

    obiectCentrat = true;
}

void RefacePozitia(Obiect &obj) {
    if(!obiectCentrat)
        return;

    for(int i = 0; i < obj.varfuri.size(); i++)
        obj.varfuri[i] += obj.centru;
    
    obj.axaOX += obj.centru;
    obj.axaOY += obj.centru;
    obj.axaOZ += obj.centru;

    if(varfSelectat != -1)
        for(int i = 0; i < 3; i++)
            obj.axePunctSelectat[i] += obj.centru;

    obiectCentrat = false;
}
