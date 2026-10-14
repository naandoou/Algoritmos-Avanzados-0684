#include <iostream>
#include <vector>
using namespace std;

// N proyectos
// 3 equipos
// misma distribucion de carga
// M pares de proyectos incompatibles

bool validarcompatible(int idproyecto, vector<int> proyectos, int incompatibilidades[][2], int M) {
    for (int i = 0; i < proyectos.size(); i++) {
        // probamos cada proyecto
        for (int j = 0; j < M; j++) {
            // revisamos cada para de incompatibilidades
            if ((idproyecto == incompatibilidades[j][0] and proyectos[i] == incompatibilidades[j][1])
                or (idproyecto == incompatibilidades[j][1] and proyectos[i] == incompatibilidades[j][0])) {
                return false;
            }
        }
    }
    // en caso no encontró ninguna incompatibilidad, retorna true
    return true;
}

bool asignadortareas(int idproyecto ,int *horas, int incompatibilidades[][2], int N, int M,
    int ha, int hb, int hc, vector<int> &proya, vector<int> &proyb, vector<int> &proyc, int &horasporequipo) {

    if (idproyecto > N) {
        // cuando ya se evaluaron todos los proyectos en un escenario
        if (ha == hb and hb == hc) {
            // si las horas asignadas a cada equipo son iguales
            horasporequipo = ha; // da igual a cual lo igualamos
            return true;
        }
        return false; // en caso no, retornamos false
    }

    // recorremos todos los equipos para ir asignando proyectos
    for (int j = 0; j < 3; j++) {
        // asignamos por equipo
        if (j == 0 and validarcompatible(idproyecto, proya, incompatibilidades, M)) {
            // asignamos a A
            proya.push_back(idproyecto);
            if (asignadortareas(idproyecto + 1, horas, incompatibilidades, N, M,
                ha + horas[idproyecto - 1], hb, hc, proya, proyb, proyc, horasporequipo)) return true;
            proya.pop_back(); // aca esta el back
        }
        if (j == 1 and validarcompatible(idproyecto, proyb, incompatibilidades, M)) {
            // asignamos a B
            proyb.push_back(idproyecto);
            if (asignadortareas(idproyecto + 1, horas, incompatibilidades, N, M,
                ha, hb + horas[idproyecto - 1], hc, proya, proyb, proyc, horasporequipo)) return true;
            proyb.pop_back(); // aca esta el back
        }
        if (j == 2 and validarcompatible(idproyecto, proyc, incompatibilidades, M)) {
            // asignamos a C
            proyc.push_back(idproyecto);
            if (asignadortareas(idproyecto + 1, horas, incompatibilidades, N, M,
                ha, hb, hc + horas[idproyecto - 1], proya, proyb, proyc, horasporequipo)) return true;
            proyc.pop_back(); // aca esta el back
        }
    }
    // si la asignacion a ningun equipo es valida, la opcion actual no sirve xd
    return false;
}

int main() {
    // datos caso 1
    const int N = 6;
    const int M = 2;
    int horas[N] = {3, 5, 4, 4, 3, 2};
    int incompatiblidades[M][2] = {{1, 2}, {3, 4}};

    // datos caso 2
    // const int N = 6;
    // const int M = 2;
    // int horas[N] = {3, 5, 4, 4, 3, 2};
    // int incompatiblidades[M][2] = {{1, 3}, {2, 6}};


    // guardamos los ids de los proyectos asignados
    vector<int> proya;
    vector<int> proyb;
    vector<int> proyc;
    int horasporequipo = -1; // si nunca encuentra una asignacion valida, se mantendra con -1
    bool existeasignacion = asignadortareas(1, horas, incompatiblidades, N, M, 0, 0, 0, proya, proyb, proyc, horasporequipo);
    if (existeasignacion) {
        cout << "Equipo A:";
        for (int pa: proya) cout << " " << pa;
        cout << endl;
        cout << "Equipo B:";
        for (int pb: proyb) cout << " " << pb;
        cout << endl;
        cout << "Equipo C:";
        for (int pc: proyc) cout << " " << pc;
        cout << endl;
        cout << "Carga por equipo: " << horasporequipo;
    }
    else cout << "IMPOSIBLE";
    return 0;
}
