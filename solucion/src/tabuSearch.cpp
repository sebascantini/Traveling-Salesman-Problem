#include "tabuSearch.h"

vector<vector<int>> memoria;
int mem_i;

vector<pair<vector<int>, int>> obtenerSubVecindad(vector<vector<int>> &incidencias, pair<vector<int>, int> &ciclo, int vecinos)
{
    vector<pair<vector<int>, int>> ciclos_vecinos;
    int costo_viejo = ciclo.second;

    for (int i = 0; i < incidencias.size(); i++)
    {
        for (int j = i + 1; j < incidencias.size(); j++)
        {
            ciclo.second = costo_viejo - incidencias[ciclo.first[i] - 1][ciclo.first[(i + 1) % incidencias.size()] - 1] - incidencias[ciclo.first[j] - 1][ciclo.first[(j + 1) % incidencias.size()] - 1] + incidencias[ciclo.first[i] - 1][ciclo.first[j] - 1] + incidencias[ciclo.first[(i + 1) % incidencias.size()] - 1][ciclo.first[(j + 1) % incidencias.size()] - 1];
            swap(ciclo.first, i, j);
            ciclos_vecinos.push_back(ciclo);
            swap(ciclo.first, i, j);
        }
    }

    int cant = ciclos_vecinos.size() * vecinos / 100;

    unsigned seed = RAND_INT;//chrono::system_clock::now().time_since_epoch().count();
    shuffle(ciclos_vecinos.begin(), ciclos_vecinos.end(), default_random_engine(seed));

    return vector<pair<vector<int>, int>>(ciclos_vecinos.begin(), ciclos_vecinos.begin() + cant);
}

pair<vector<int>, int> obtenerMejor(vector<pair<vector<int>, int>> vecindario)
{
    pair<vector<int>, int> mejor_ciclo;
    mejor_ciclo.second = INT_MAX;
    pair<vector<int>, int> mejor_ciclo_total; // este segundo ciclo lo tenemos por si todos los ciclos del vecindario estan en memoria
    mejor_ciclo_total.second = INT_MAX;

    for(int i = 0; i < vecindario.size(); ++i){
        bool presente = false;
        for(int j = 0; j < memoria.size(); ++j)
            presente |= memoria[j] == vecindario[i].first;
        if(vecindario[i].second < mejor_ciclo.second && !presente){
            mejor_ciclo = vecindario[i];
        }
        if(vecindario[i].second < mejor_ciclo_total.second)
            mejor_ciclo_total = vecindario[i];
    }

    if(mejor_ciclo.second == INT_MAX)
        return mejor_ciclo_total;

    return mejor_ciclo;
}

void guardar(pair<vector<int>, int> &ciclo)
{
    memoria[mem_i] = ciclo.first; // guardar en memoria
    mem_i = (mem_i + 1) % memoria.size();
    return;
}

pair<vector<int>, int> tabuSearch(vector<vector<int>> &incidencias, int l, int k, int vecinos)
{
    pair<vector<int>, int> ciclo = hagm(incidencias);
    pair<vector<int>, int> mejor = ciclo;
    memoria = vector<vector<int>>((int)incidencias.size()*k/100);
    mem_i = 0;
    int it = 0;

    for(int it = 0; it < l; ++it){
        //precalculamos vecinos
        vector<pair<vector<int>, int>> vecindario = obtenerSubVecindad(incidencias, ciclo, vecinos);
        ciclo = obtenerMejor(vecindario);
        guardar(ciclo);
        if (ciclo.second < mejor.second)
            mejor = ciclo;
    }

    return mejor;
}