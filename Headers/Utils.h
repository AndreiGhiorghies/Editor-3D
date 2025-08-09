#pragma once

#include "../Headers/Structuri.h"

template <typename T>
void clearStack(stack<T> &s) {
    while(!s.empty()) {
        s.pop();
    }
}

void operator-=(Punct3D &obj1, Punct3D &obj2);
void operator+=(Punct3D &obj1, Punct3D &obj2);

Punct2D Transforma2D(const Punct3D &punct);

Punct3D GetMijlocObiect(const Obiect &obj);
void CentreazaObiect(Obiect &obj);
void RefacePozitia(Obiect &obj);
