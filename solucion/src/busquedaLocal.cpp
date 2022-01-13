#include "busquedaLocal.h"

pair<vector<int>, int> busquedaLocal(vector<vector<int>> &incidencias, int l)
{
    pair<vector<int>, int> ciclo = hagm(incidencias);
    for (int it = 0; it < l; ++it)
    {
        for (int i = 0; i < ciclo.first.size(); ++i)
        {
            for (int j = i + 1; j < ciclo.first.size(); ++j)
            {
                int costo_nuevo = ciclo.second - incidencias[ciclo.first[i] - 1][ciclo.first[(i + 1) % ciclo.first.size()] - 1] - incidencias[ciclo.first[j] - 1][ciclo.first[(j + 1) % ciclo.first.size()] - 1] + incidencias[ciclo.first[i] - 1][ciclo.first[j] - 1] + incidencias[ciclo.first[(i + 1) % ciclo.first.size()] - 1][ciclo.first[(j + 1) % ciclo.first.size()] - 1];
                if (costo_nuevo < ciclo.second)
                {
                    //actualizar
                    ciclo.second = costo_nuevo;
                    swap(ciclo.first, i, j);
                }
            }
        }
    }
    return ciclo;
}