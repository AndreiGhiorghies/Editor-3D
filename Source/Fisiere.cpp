#include "../Headers/Fisiere.h"
#include "../Headers/Structuri.h"
#include "../Headers/Utils.h"
#include "../Headers/Transformari.h"

#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>

//----------------------------------------------- OBJECT LOADER -----------------------------------------------------------------

void normalizeCoordinates(vector<Punct3D> &points, const double minRange = -2.0f, const double maxRange = 2.0f) {
    if(static_cast<int>(points.size()) == 0)
        return;
    
    double minX = points[0].x, maxX = points[0].x;
    double minY = points[0].y, maxY = points[0].y;
    double minZ = points[0].z, maxZ = points[0].z;

    for (const auto& point : points) {
        minX = min(minX, point.x);
        maxX = max(maxX, point.x);
        minY = min(minY, point.y);
        maxY = max(maxY, point.y);
        minZ = min(minZ, point.z);
        maxZ = max(maxZ, point.z);
    }

    double rangeX = maxX - minX;
    double rangeY = maxY - minY;
    double rangeZ = maxZ - minZ;

    double maxRangeOriginal = max({rangeX, rangeY, rangeZ});

    double scale = (maxRange - minRange) / maxRangeOriginal;

    for (auto& point : points) {
        point.x = minRange + (point.x - minX) * scale;
        point.y = minRange + (point.y - minY) * scale;
        point.z = minRange + (point.z - minZ) * scale;
    }
}

string GetAdresaFisier() {

    OPENFILENAMEA ofn;
    char filePath[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = ".obj\0*.obj\0.txt\0*.txt\0Toate Fisierele\0*.*\0";
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileNameA(&ofn))
        return string(filePath);
    else
        return "";
}

int CitesteObiect(const string &adresaFisier) {
    ifstream f(adresaFisier);
    int nrObiecte;

    f >> nrObiecte;

    for(int nr = 0; nr < nrObiecte; nr++) {
        Obiect obj;
        int nrVarfuri, nrMuchii, nrFete;

        f >> nrVarfuri >> nrMuchii >> nrFete;

        for(int i = 0; i < nrVarfuri; i++) {
            double x, y, z;
            f >> x >> y >> z;

            obj.varfuri.push_back({x, y, z});
        }

        for(int i = 0; i < nrMuchii; i++) {
            int a, b;
            f >> a >> b;

            obj.muchii.push_back({a, b});
        }

        for(int i = 0; i < nrFete; i++) {
            int dim, x;
            f >> dim;

            obj.fete.push_back({});
            for(int j = 0; j < dim; j++) {
                f >> x;
                obj.fete[i].push_back(x);
            }

            obj.indexFata.push_back(i);
        }

        f >> obj.rotatieX >> obj.rotatieY >> obj.rotatieZ;
        f >> obj.marimeX >> obj.marimeY >> obj.marimeZ;
        f >> obj.deplasareX >> obj.deplasareY >> obj.deplasareZ;

        char axa;
        f >> axa;

        while(axa != '#') {
            double unghi;

            f >> unghi >> axa;

            obj.rotatiiAnterioare.push({axa, unghi});
        }

        if(obj.rotatiiAnterioare.size() > 0)
            obj.rotatiiAnterioare.pop();

        obj.activ = true;

        obiecte.push_back(obj);
    }

    obiectSelectat = static_cast<int>(obiecte.size()) - 1;
    obiecteSelectate.push_back(obiectSelectat);

    f.close();

    return nrObiecte;
}

Obiect IncarcaObiect(const string &adresa) {
    int nrObiecte = CitesteObiect(adresa);

    varfSelectat = -1;
    fataSelectata = -1;
    selectareInput = -1;
    puncteSelectate.clear();

    for(int i = (int) obiecte.size() - nrObiecte; i < obiecte.size(); i++) {
        if(obiecte[i].varfuri.size() > 30)
            normalizeCoordinates(obiecte[i].varfuri);
        else
            normalizeCoordinates(obiecte[i].varfuri, -1, 1);
        
        obiecte[i].axePunctSelectat = vector<Punct3D>(3, {0, 0, 0});
        obiecte[i].centru = GetMijlocObiect(obiecte[i]);
        obiecte[i].centruPentruAxe = obiecte[i].centru;
        
        obiecte[i].axeObiectStabile = {{0, 0, 0}, {0.30, 0, 0}, {0, -0.30, 0}, {0, 0, 0.30}};

        EditareRotatie(obiecte[i], true);

        obiecte[i].axaOX = {obiecte[i].centru.x + 0.5, obiecte[i].centru.y, obiecte[i].centru.z};
        obiecte[i].axaOY = {obiecte[i].centru.x, obiecte[i].centru.y - 0.5, obiecte[i].centru.z};
        obiecte[i].axaOZ = {obiecte[i].centru.x, obiecte[i].centru.y, obiecte[i].centru.z + 0.5};

        EditareRotatie(obiecte[i], false);

        int k = 100;
        for(int j = 0; j < obiecte[i].fete.size(); j++) {
            obiecte[i].culoareFete.push_back({k, k, k});
            k += 7;
            if(k > 200)
                k = 100;
        }

        sort(obiecte[i].fete.begin(), obiecte[i].fete.end(), [&](const vector<int> &a, const vector<int> &b) {
            double sumaZa = 0, sumaZb = 0;

            for (const int &j : a)
                sumaZa += obiecte[i].varfuri[j].z;

            for (const int &j : b)
                sumaZb += obiecte[i].varfuri[j].z;

            return sumaZa / static_cast<double>(a.size()) > sumaZb / static_cast<double>(b.size());
        });
    }

    return obiecte[obiectSelectat];
}

Obiect IncarcaObiect_Obj(const string &adresa) {
    Obiect obj;

    ifstream f(adresa);

    string linie;
    int nr = 0;

    while(getline(f, linie)) {
        istringstream linieStream(linie);
        string tip;

        linieStream >> tip;

        if(tip == "v") {
            double x, y, z;

            linieStream >> x >> y >> z;

            obj.varfuri.push_back({x, y, z});
        }
        else if(tip == "f") {
            obj.fete.push_back({});
            int n = static_cast<int>(obj.fete.size()) - 1;
            string indice;

            while(linieStream >> indice) {
                int indiceVarf = stoi(indice) - 1;
                obj.fete[n].push_back(indiceVarf);
            }

            obj.indexFata.push_back(nr++);
        }
    }

    if(obj.varfuri.size() > 30)
        normalizeCoordinates(obj.varfuri);
    else
        normalizeCoordinates(obj.varfuri, -1, 1);

    obj.rotatieX = 0;
    obj.rotatieY = 0;
    obj.rotatieZ = 0;
    obj.marimeX = 1;
    obj.marimeY = 1;
    obj.marimeZ = 1;
    obj.deplasareX = 0;
    obj.deplasareY = 0;
    obj.deplasareZ = 0;

    f.close();

    varfSelectat = -1;
    fataSelectata = -1;
    puncteSelectate.clear();
    obj.axePunctSelectat = vector<Punct3D>(3, {0, 0, 0});
    selectareInput = -1;
    obj.centru = GetMijlocObiect(obj);
    obj.centruPentruAxe = obj.centru;

    obj.axaOX = {obj.centru.x + 0.5, obj.centru.y, obj.centru.z};
    obj.axaOY = {obj.centru.x, obj.centru.y - 0.5, obj.centru.z};
    obj.axaOZ = {obj.centru.x, obj.centru.y, obj.centru.z + 0.5};

    int k = 100;
    for(int i = 0; i < obj.fete.size(); i++) {
        obj.culoareFete.push_back({k, k, k});
        k += 7;
        if(k > 200)
            k = 100;
    }

    sort(obj.fete.begin(), obj.fete.end(), [&](const vector<int> &a, const vector<int> &b) {
        double sumaZa = 0, sumaZb = 0;

        for (const int &j : a)
            sumaZa += obj.varfuri[j].z;

        for (const int &j : b)
            sumaZb += obj.varfuri[j].z;

        return sumaZa / a.size() > sumaZb / b.size();
    });


    obj.axeObiectStabile = {{0, 0, 0}, {0.30, 0, 0}, {0, -0.30, 0}, {0, 0, 0.30}};


    return obj;
}

Obiect IncarcaObiectDefault(const char *data) {
    Obiect obj;
    std::istringstream input(data);

    string linie;
    int nr = 0;

    while(getline(input, linie)) {
        istringstream linieStream(linie);
        string tip;

        linieStream >> tip;

        if(tip == "v") {
            double x, y, z;

            linieStream >> x >> y >> z;

            obj.varfuri.push_back({x, y, z});
        }
        else if(tip == "f") {
            obj.fete.push_back({});
            int n = static_cast<int>(obj.fete.size()) - 1;
            string indice;

            while(linieStream >> indice) {
                int indiceVarf = stoi(indice) - 1;
                obj.fete[n].push_back(indiceVarf);
            }

            obj.indexFata.push_back(nr++);
        }
    }

    if(obj.varfuri.size() > 30)
        normalizeCoordinates(obj.varfuri);
    else
        normalizeCoordinates(obj.varfuri, -1, 1);

    obj.rotatieX = 0;
    obj.rotatieY = 0;
    obj.rotatieZ = 0;
    obj.marimeX = 1;
    obj.marimeY = 1;
    obj.marimeZ = 1;
    obj.deplasareX = 0;
    obj.deplasareY = 0;
    obj.deplasareZ = 0;

    varfSelectat = -1;
    fataSelectata = -1;
    puncteSelectate.clear();
    obj.axePunctSelectat = vector<Punct3D>(3, {0, 0, 0});
    selectareInput = -1;
    obj.centru = GetMijlocObiect(obj);
    obj.centruPentruAxe = obj.centru;

    obj.axaOX = {obj.centru.x + 0.5, obj.centru.y, obj.centru.z};
    obj.axaOY = {obj.centru.x, obj.centru.y - 0.5, obj.centru.z};
    obj.axaOZ = {obj.centru.x, obj.centru.y, obj.centru.z + 0.5};

    int k = 100;
    for(int i = 0; i < obj.fete.size(); i++) {
        obj.culoareFete.push_back({k, k, k});
        k += 7;
        if(k > 200)
            k = 100;
    }

    sort(obj.fete.begin(), obj.fete.end(), [&](const vector<int> &a, const vector<int> &b) {
        double sumaZa = 0, sumaZb = 0;

        for (const int &j : a)
            sumaZa += obj.varfuri[j].z;

        for (const int &j : b)
            sumaZb += obj.varfuri[j].z;

        return sumaZa / a.size() > sumaZb / b.size();
    });


    obj.axeObiectStabile = {{0, 0, 0}, {0.30, 0, 0}, {0, -0.30, 0}, {0, 0, 0.30}};


    return obj;
}

//-------------------------------------------- END OF OBJECT LOADER -------------------------------------------------------------

//------------------------------------------------ OBJECT SAVER -----------------------------------------------------------------

string SalveazaFisier() {
    OPENFILENAMEA ofn;
    char filePath[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = ".txt\0*.txt\0.obj\0*.obj\0Toate Fisierele\0*.*\0";
    ofn.lpstrFile = filePath;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_OVERWRITEPROMPT;
    ofn.lpstrDefExt = "txt";

    if (GetSaveFileNameA(&ofn))
        return string(filePath);
    else
        return "";
}

void SalveazaObiect_Obj(const Obiect &obj2, const string &adresa) {
    ofstream f(adresa);

    int plus = 0;

    for(const auto &obj : obiecteSelectate)
        for(auto i : obiecte[obj].varfuri)
            f << "v " << i.x << ' ' << i.y << ' ' << i.z << endl;

    for(const auto &obj : obiecteSelectate) {
        for(auto i : obiecte[obj].fete) {
            f << "f ";
            for(auto j : i)
                f << j + 1 + plus << ' ';
            f << endl;
        }
        plus += static_cast<int>(obiecte[obj].fete.size()) + 2;
    }

    f.close();
}

void SalveazaObiect(const Obiect &obj, const string &adresa) {
    ofstream f(adresa);

    f << (int) obiecteSelectate.size() << endl;

    for(const auto &i : obiecteSelectate) {
        f << (int) obiecte[i].varfuri.size() << ' ' << (int) obiecte[i].muchii.size() << ' ' << (int) obiecte[i].fete.size() << endl;

        for(int j = 0; j < obiecte[i].varfuri.size(); j++)
            f << obiecte[i].varfuri[j].x << ' ' << obiecte[i].varfuri[j].y << ' ' << obiecte[i].varfuri[j].z << endl;
        
        for(int j = 0; j < obiecte[i].muchii.size(); j++)
            f << obiecte[i].muchii[j].first << ' ' << obiecte[i].muchii[j].second << endl;
        
        for(int j = 0; j < obiecte[i].fete.size(); j++) {
            f << (int) obiecte[i].fete[j].size() << ' ';
            for(int k = 0; k < obiecte[i].fete[j].size(); k++)
                f << obiecte[i].fete[j][k] << ' ';
            f << endl;
        }

        f << obiecte[i].rotatieX << ' ' << obiecte[i].rotatieY << ' ' << obiecte[i].rotatieZ << endl;
        f << obiecte[i].marimeX << ' ' << obiecte[i].marimeY << ' ' << obiecte[i].marimeZ << endl;
        f << obiecte[i].deplasareX << ' ' << obiecte[i].deplasareY << ' ' << obiecte[i].deplasareZ << endl;

        stack<pair<char, double>> st;
        while(!obiecte[i].rotatiiAnterioare.empty()) {
            st.push(obiecte[i].rotatiiAnterioare.top());
            obiecte[i].rotatiiAnterioare.pop();
        }

        while(!st.empty()) {
            f << st.top().first << ' ' << st.top().second << endl;
            obiecte[i].rotatiiAnterioare.push(st.top());
            st.pop();
        }

        f << endl << '#' << endl << endl;
    }

    f.close();
}

//-------------------------------------------- END OF OBJECT SAVER --------------------------------------------------------------
