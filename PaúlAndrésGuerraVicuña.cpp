#include <iostream>
#include <vector>
#include <algorithm> 
#include <iomanip>  
#include <cmath>
using namespace std;

// Constantes para validacion
const int MAX_PASOS = 50000;
const int MAX_MINUTOS = 1440;
const float MAX_CALORIAS = 5000.0f;

// Funcion para validar entero positivo dentro de rango
int validarEntero(int min, int max) {
    int valor;
    while (true) {
        cin >> valor;
        if (valor >= min && valor <= max) return valor;
        cout << "Entrada invalida. Ingrese valor entre " << min << " y " << max << ": ";
    }
}

// Funcion para validar flotante positivo dentro de rango
float validarFlotante(float min, float max) {
    float valor;
    while (true) {
        cin >> valor;
        if (valor >= min && valor <= max) return valor;
        cout << "Entrada invalida. Ingrese valor entre " << min << " y " << max << ": ";
    }
}

// Funcion para ingresar datos iniciales
void ingresarDatos(vector<int>& pasos, vector<int>& minutos, vector<float>& calorias, int& numDias) {
    cout << "Ingrese el numero de dias iniciales: ";
    numDias = validarEntero(1, 31); // Maximo un mes
    pasos.resize(numDias);
    minutos.resize(numDias);
    calorias.resize(numDias);
    for (int i = 0; i < numDias; i++) {
        cout << endl << "Dia " << (i + 1) << endl;
        cout << "Pasos (0-" << MAX_PASOS << "): ";
        pasos[i] = validarEntero(0, MAX_PASOS);
        cout << "Minutos de actividad (0-" << MAX_MINUTOS << "): ";
        minutos[i] = validarEntero(0, MAX_MINUTOS);
        cout << "Calorias quemadas (0.0-" << MAX_CALORIAS << "): ";
        calorias[i] = validarFlotante(0.0f, MAX_CALORIAS);
    }
    cout << "Datos ingresados." << endl;
}

// Funcion para insertar un nuevo dia en posicion especifica
void insertarRegistro(vector<int>& pasos, vector<int>& minutos, vector<float>& calorias, int& numDias) {
    int pos;
    cout << "Posicion para insertar (0-" << numDias << "): ";
    pos = validarEntero(0, numDias);
    int p = validarEntero(0, MAX_PASOS);
    int m = validarEntero(0, MAX_MINUTOS);
    float c = validarFlotante(0.0f, MAX_CALORIAS);
    pasos.insert(pasos.begin() + pos, p);
    minutos.insert(minutos.begin() + pos, m);
    calorias.insert(calorias.begin() + pos, c);
    numDias++;
    cout << "Registro insertado." << endl;
}

// Funcion para modificar un dia especifico
void modificarRegistro(vector<int>& pasos, vector<int>& minutos, vector<float>& calorias, int numDias) {
    int dia;
    cout << "Dia a modificar (1-" << numDias << "): ";
    dia = validarEntero(1, numDias) - 1;
    cout << "Nuevos pasos: ";
    pasos[dia] = validarEntero(0, MAX_PASOS);
    cout << "Nuevos minutos: ";
    minutos[dia] = validarEntero(0, MAX_MINUTOS);
    cout << "Nuevas calorias: ";
    calorias[dia] = validarFlotante(0.0f, MAX_CALORIAS);
    cout << "Registro modificado." << endl;
}

// Funcion para buscar un valor en un arreglo 
void buscarRegistro(const vector<int>& pasos, const vector<int>& minutos, const vector<float>& calorias, int numDias) {
    int opcion, valor;
    cout << "Buscar en: 1-Pasos, 2-Minutos, 3-Calorias: ";
    opcion = validarEntero(1, 3);
    cout << "Valor a buscar: ";
    cin >> valor;
    bool encontrado = false;
    for (int i = 0; i < numDias; i++) {
        bool match = false;
        if (opcion == 1 && pasos[i] == valor) match = true;
        else if (opcion == 2 && minutos[i] == valor) match = true;
        else if (opcion == 3 && static_cast<int>(calorias[i]) == valor) match = true; 
        if (match) {
            cout << "Encontrado en dia " << (i + 1) << ": Pasos=" << pasos[i] << ", Minutos=" << minutos[i] << ", Calorias=" << calorias[i] << endl;
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No encontrado." << endl;
}

// Funcion auxiliar para ordenar arreglos paralelos
void ordenarArreglos(vector<int>& pasos, vector<int>& minutos, vector<float>& calorias, int numDias, bool ascendente) {
    vector<pair<int, pair<int, float>>> temp(numDias);
    for (int i = 0; i < numDias; i++) {
        temp[i] = {pasos[i], {minutos[i], calorias[i]}};
    }
    if (ascendente) {
        sort(temp.begin(), temp.end());
    } else {
        sort(temp.rbegin(), temp.rend());
    }
    for (int i = 0; i < numDias; i++) {
        pasos[i] = temp[i].first;
        minutos[i] = temp[i].second.first;
        calorias[i] = temp[i].second.second;
    }
    cout << "Arreglos ordenados." << endl;
}

// Funcion para ordenar
void ordenarRegistros(vector<int>& pasos, vector<int>& minutos, vector<float>& calorias, int numDias) {
    int dir;
    cout << "1-Ascendente, 2-Descendente (por pasos): ";
    dir = validarEntero(1, 2);
    ordenarArreglos(pasos, minutos, calorias, numDias, dir == 1);
}

// Funcion para eliminar un registro
void eliminarRegistro(vector<int>& pasos, vector<int>& minutos, vector<float>& calorias, int& numDias) {
    int opcion;
    cout << "Eliminar: 1-Por posicion, 2-Por condicion (pasos < 1000): ";
    opcion = validarEntero(1, 2);
    if (opcion == 1) {
        int pos;
        cout << "Posicion (1-" << numDias << "): ";
        pos = validarEntero(1, numDias) - 1;
        pasos.erase(pasos.begin() + pos);
        minutos.erase(minutos.begin() + pos);
        calorias.erase(calorias.begin() + pos);
    } else {
        for (auto it = pasos.begin(); it != pasos.end(); ) {
            if (*it < 1000) {
                auto idx = distance(pasos.begin(), it);
                minutos.erase(minutos.begin() + idx);
                calorias.erase(calorias.begin() + idx);
                it = pasos.erase(it);
            } else {
                ++it;
            }
        }
    }
    numDias = pasos.size();
    cout << "Registros eliminados." << endl;
}

// Analisis Estadistico 
// Funcion para calcular media de vector<int>
float calcularMedia(const vector<int>& vec, int n) {
    if (n == 0) return 0.0f;
    int sum = 0;
    for (int v : vec) sum += v;
    return static_cast<float>(sum) / n;
}

// Funcion para calcular media de vector<float>
float calcularMedia(const vector<float>& vec, int n) {
    if (n == 0) return 0.0f;
    float sum = 0.0f;
    for (float v : vec) sum += v;
    return sum / n;
}

// Funcion para calcular mediana 
float calcularMediana(vector<int> vec, int n) {
    if (n == 0) return 0.0f;
    sort(vec.begin(), vec.end());
    if (n % 2 == 0) return (vec[n/2 - 1] + vec[n/2]) / 2.0f;
    return vec[n/2];
}

float calcularMediana(vector<float> vec, int n) {
    if (n == 0) return 0.0f;
    sort(vec.begin(), vec.end());
    if (n % 2 == 0) return (vec[n/2 - 1] + vec[n/2]) / 2.0f;
    return vec[n/2];
}

// Funcion para calcular moda 
int calcularModa(const vector<int>& vec, int n) {
    if (n == 0) return 0;
    vector<int> temp = vec;
    sort(temp.begin(), temp.end());
    int moda = temp[0], maxCount = 1, count = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i-1]) {
            count++;
        } else {
            if (count > maxCount) {
                maxCount = count;
                moda = temp[i-1];
            }
            count = 1;
        }
    }
    if (count > maxCount) moda = temp.back();
    return moda;
}

float calcularModa(const vector<float>& vec, int n) {
  
    if (n == 0) return 0.0f;
    vector<float> temp = vec;
    sort(temp.begin(), temp.end());
    float moda = temp[0];
    int maxCount = 1, count = 1;
    for (int i = 1; i < n; i++) {
        if (abs(temp[i] - temp[i-1]) < 0.01f) { 
            count++;
        } else {
            if (count > maxCount) {
                maxCount = count;
                moda = temp[i-1];
            }
            count = 1;
        }
    }
    if (count > maxCount) moda = temp.back();
    return moda;
}

// Analisis especifico propuesto
// Para pasos: contar dias con meta alcanzada (>10000)
int analisisPasos(const vector<int>& pasos, int n) {
    int count = 0;
    for (int p : pasos) if (p > 10000) count++;
    return count;
}

// Para minutos: porcentaje de dias activos (>=30 min)
float analisisMinutos(const vector<int>& minutos, int n) {
    if (n == 0) return 0.0f;
    int count = 0;
    for (int m : minutos) if (m >= 30) count++;
    return (static_cast<float>(count) / n) * 100.0f;
}

// Para calorias: total quemadas
float analisisCalorias(const vector<float>& calorias, int n) {
    float total = 0.0f;
    for (float c : calorias) total += c;
    return total;
}

// Funcion para mostrar analisis
void mostrarAnalisis(const vector<int>& pasos, const vector<int>& minutos, const vector<float>& calorias, int numDias) {
    cout << endl << " Analisis Pasos " << endl;
    cout << "Media: " << fixed << setprecision(2) << calcularMedia(pasos, numDias) << endl;
    cout << "Mediana: " << calcularMediana(pasos, numDias) << endl;
    cout << "Moda: " << calcularModa(pasos, numDias) << endl;
    cout << "Dias con meta (>10000 pasos): " << analisisPasos(pasos, numDias) << endl;

    cout << endl << " Analisis Minutos " << endl;
    cout << "Media: " << fixed << setprecision(2) << calcularMedia(minutos, numDias) << endl;
    cout << "Mediana: " << calcularMediana(minutos, numDias) << endl;
    cout << "Moda: " << calcularModa(minutos, numDias) << endl;
    cout << "Porcentaje dias activos (>=30 min): " << fixed << setprecision(2) << analisisMinutos(minutos, numDias) << "%" << endl;

    cout << endl << " Analisis Calorias " << endl;
    cout << "Media: " << fixed << setprecision(2) << calcularMedia(calorias, numDias) << endl;
    cout << "Mediana: " << calcularMediana(calorias, numDias) << endl;
    cout << "Moda: " << calcularModa(calorias, numDias) << endl;
    cout << "Total quemadas: " << fixed << setprecision(2) << analisisCalorias(calorias, numDias) << endl;
}

// Funcion para mostrar menu
void mostrarMenu() {
    cout << endl << " Menu " << endl;
    cout << "1. Ingresar datos iniciales" << endl;
    cout << "2. Insertar registro" << endl;
    cout << "3. Modificar registro" << endl;
    cout << "4. Buscar registro" << endl;
    cout << "5. Ordenar registros" << endl;
    cout << "6. Eliminar registro" << endl;
    cout << "7. Analisis estadistico (Media, Mediana, Moda)" << endl;
    cout << "8. Salir" << endl;
    cout << "Opcion: ";
}

int main() {
    vector<int> pasos, minutos;
    vector<float> calorias;
    int numDias = 0;
    bool datosIngresados = false;
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                ingresarDatos(pasos, minutos, calorias, numDias);
                datosIngresados = true;
                break;
            case 2:
                if (datosIngresados) insertarRegistro(pasos, minutos, calorias, numDias);
                else cout << "Ingrese datos iniciales primero." << endl;
                break;
            case 3:
                if (datosIngresados) modificarRegistro(pasos, minutos, calorias, numDias);
                else cout << "Ingrese datos iniciales primero." << endl;
                break;
            case 4:
                if (datosIngresados) buscarRegistro(pasos, minutos, calorias, numDias);
                else cout << "Ingrese datos iniciales primero." << endl;
                break;
            case 5:
                if (datosIngresados) ordenarRegistros(pasos, minutos, calorias, numDias);
                else cout << "Ingrese datos iniciales primero." << endl;
                break;
            case 6:
                if (datosIngresados) eliminarRegistro(pasos, minutos, calorias, numDias);
                else cout << "Ingrese datos iniciales primero." << endl;
                break;
            case 7:
                if (datosIngresados) mostrarAnalisis(pasos, minutos, calorias, numDias);
                else cout << "Ingrese datos iniciales primero." << endl;
                break;
            case 8:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion invalida." << endl;
        }
    } while (opcion != 8);

    return 0;
}