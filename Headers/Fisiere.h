#pragma once

#include "../Headers/Structuri.h"
#include <string>

string GetAdresaFisier();

Obiect IncarcaObiect(const string &adresa);
Obiect IncarcaObiect_Obj(const string &adresa);
Obiect IncarcaObiectDefault(const char *data);

string SalveazaFisier();
void SalveazaObiect_Obj(const Obiect &obj2, const string &adresa);
void SalveazaObiect(const Obiect &obj, const string &adresa);



