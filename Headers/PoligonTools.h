#pragma once

#include "../Headers/Structuri.h"

bool estePunctApropiat(const Punct2D &punct, const Punct2D &mouse);
void UnestePuncte(Obiect &obj);
void EliminaPunct(Obiect &obj);
void AdaugaPunct(Obiect &obj);
void CrearePoligon(Obiect &obj);
bool VerificaMousePeAxa(Obiect &obj, const int &mouseX, const int &mouseY);