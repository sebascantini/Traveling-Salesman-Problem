#include "goloso.h"
#include "agm.h"
#include "busquedaLocal.h"
#include "tabuSearch.h"

// ./tp2 file mode

int main(int argc, char** argv){
    string filename, algorithm;

    filename = argv[1];
    algorithm = argv[2];

    ifstream file;
    file.open(filename);

    if(!file.is_open()){
        cout << "File could not be opened" << endl;
        return 0;
    }

    int vertices, aristas;
    file >> vertices;
    file >> aristas;
    vector<vector<int> > incidencias (vertices, vector<int>(vertices, INT_MAX));
    
    for(int k = 0; k < aristas; ++k){
        int i,j,costo;
        file >> i;
        file >> j;
        file >> costo;
  
        incidencias[i-1][j-1] = costo;
        incidencias[j-1][i-1] = costo;
    }

    // for(int i = 0; i < incidencias.size(); ++i){
    //     for(int j = 0; j < incidencias.size(); ++j)
    //         cout << incidencias[i][j] << " ";
    //     cout << endl;
    // }

    pair<vector<int>, int> ans;

    if(algorithm == "hg")           // heuristica goloso
        ans = goloso(incidencias);
    else if(algorithm == "hagm")    // heuristica (agm)
        ans = hagm(incidencias);
    else if(algorithm == "bl")      // busqueda local
        ans = busquedaLocal(incidencias, atoi(argv[3]));
    else if(algorithm == "ts")      // tabu search
        ans = tabuSearch(incidencias, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    file.close();
    imprimir(ans.second, ans.first);

    return 0;
}



















