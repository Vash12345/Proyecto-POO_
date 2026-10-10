#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Criatura {
private:
    // ATRIBUTOS DE ESTADO (Encapsulamiento)
    string nombre;
    int vida, energia, ataque;
    int vidaMax;
    int energiaMax;
    
    // ATRIBUTO ESTÁTICO (Unidad III): Compartido por todas las instancias de la clase
    static int contadorCriaturas;

public:
    // CONSTRUCTOR por defecto (Sobrecarga de constructores)
    Criatura() {
        nombre = "Sin nombre";
        vidaMax = 200;
        energiaMax = 200;
        setVida(100);
        setEnergia(100);
        ataque = 10;
        contadorCriaturas++;
        cout << "[Creada] Se ha creado a " << nombre << ". Poblacion total: " << contadorCriaturas << "\n";
    }

    // CONSTRUCTOR parametrizado (Sobrecarga de constructores)
    Criatura(string n, int v, int a, int e = 100) {
        nombre = n;
        vidaMax = 200;
        energiaMax = 200;
        setVida(v);
        setEnergia(e);
        ataque = a;
        contadorCriaturas++; 
        cout << "[Creada] Se ha creado a " << nombre << ". Poblacion total: " << contadorCriaturas << "\n";
    }

    // DESTRUCTOR: Se llama automáticamente al liberar la memoria del objeto
    ~Criatura() {
        contadorCriaturas--; 
        cout << "[Memoria Liberada] El objeto " << nombre << " fue destruido. Poblacion restante: " << contadorCriaturas << "\n";
    }

    // GETTER ESTÁTICO: Permite acceder al atributo estático sin instanciar la clase
    static int getContadorCriaturas() {
        return contadorCriaturas;
    }

    // SETTERS: Incluyen validaciones para proteger y controlar el estado interno
    void setVida(int v) {
        if (v < 0) vida = 0;
        else if (v > vidaMax) vida = vidaMax;
        else vida = v;
    }

    void setEnergia(int e) {
        if (e < 0) energia = 0;
        else if (e > energiaMax) energia = energiaMax;
        else energia = e;
    }

    // GETTERS: Métodos de solo lectura
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }
    string getNombre() const { return nombre; }
    int getAtaque() const { return ataque; }
    
    void setNombre(string n) { nombre = n; }

    // MÉTODO DE INTERFAZ: Muestra el estado actual y el menú de acciones
    void pantalla(int& opc, Criatura* enemigo) {
        system("clear");
        cout << "\n=== " << nombre << " ===";
        cout << "\n  HP:" << vida << "/" << vidaMax << " | ENG:" << energia << "/" << energiaMax;
        cout << "\n___________________";
        cout << "\n|                 |";
        cout << "\n|      /|_/|      |";
        cout << "\n|     ( o.o )     |";
        cout << "\n|      > ^ <      |";
        cout << "\n|     ||   ||     |";
        cout << "\n|    (_|___|_)    |";
        cout << "\n|_________________|";
        cout << "\n";
        
        // Muestra el estado del enemigo si aún está vivo
        if (enemigo->estaViva()) {
            cout << "\n[ENEMIGO] " << enemigo->getNombre() << " (HP: " << enemigo->getVida() << " | ATK: " << enemigo->getAtaque() << ")";
        } else {
            cout << "\n[ENEMIGO] Derrotado.";
        }

        cout << "\n\nSelecciona tu opcion: ";
        cout << "\n1- Descansar";
        cout << "\n2- Atacar al enemigo";
        cout << "\n3- Curar";
        cout << "\n4- Salir\n\nOpcion: ";
        cin >> opc;
    }

    // COMPORTAMIENTOS BÁSICOS
    void descansar() {
        cout << nombre << " esta descansando... recuperas 50 de energia.\n";
        setEnergia(energia + 50);
    }

    void curar(int cura) {
        if (vida >= vidaMax) {
            cout << "La vida ya esta llena.\n";
        } else { 
            cout << "Te has curado " << cura << " de vida.\n";
            setVida(vida + cura);
        }
    }
    
    void recibirDanio(int danio) {
        setVida(vida - danio);
    }

    // MÉTODO DE COMBATE INTERACTIVO
    void atacarA(Criatura* objetivo) {
        if (energia >= 10) {
            cout << "\n>> " << nombre << " ataca a " << objetivo->getNombre() << " causando " << ataque << " de dano!\n";
            objetivo->recibirDanio(ataque);
            setEnergia(energia - 10);
        } else {
            cout << "\n>> " << nombre << " no tiene suficiente energia para atacar. ¡Necesita descansar!\n";
        }
    }
    
    // MÉTODO DE ESTADO: Verifica si la criatura sigue viva
    bool estaViva() const {
        return vida > 0;
    }
};

// Inicialización del atributo estático global fuera de la clase
int Criatura::contadorCriaturas = 0;

int main() {
    int espera, opc;
    string nombreMascota;

    cout << "=== SIMULADOR DE CRIATURAS ===\n";
    
    // INSTANCIACIÓN DINÁMICA: Uso de 'new' para asignar memoria en tiempo de ejecución
    Criatura* tamagochi = new Criatura();
    
    cout << "Que nombre le quieres poner a tu mascota?: ";
    cin >> nombreMascota;
    tamagochi->setNombre(nombreMascota);

    // Instanciación del enemigo con parámetros iniciales
    Criatura* monstruo = new Criatura("Dragon Oscuro", 100, 35, 500);

    cout << "\nPresiona un numero y Enter para comenzar: ";
    cin >> espera;
        
    // BUCLE DE JUEGO: Continúa iterando mientras la mascota siga viva
    while (tamagochi->estaViva()) {
        tamagochi->pantalla(opc, monstruo);

        switch (opc) {
            case 1: // Descansar
                tamagochi->descansar();
                break;
                
            case 2: // Atacar
                if (monstruo->estaViva()) {
                    tamagochi->atacarA(monstruo);
                    
                    // Lógica de contraataque si el enemigo sobrevive al golpe
                    if (monstruo->estaViva()) {
                        cout << "¡El enemigo contraataca!\n";
                        monstruo->atacarA(tamagochi);
                    } else {
                        cout << "¡Has derrotado a " << monstruo->getNombre() << "!\n";
                    }
                } else {
                    cout << "El enemigo ya esta derrotado. No hay a quien atacar.\n";
                }
                break;
                
            case 3: // Curar
                int cantidad_cura;
                cout << "Cuanta vida deseas curar?: ";
                cin >> cantidad_cura;
                tamagochi->curar(cantidad_cura);
                break;
            
            case 4: // Salir
                cout << "Saliendo del juego...\n";
                // LIBERACIÓN DE MEMORIA: Uso de 'delete' para evitar fugas de memoria
                delete tamagochi; 
                delete monstruo;
                return 0;

            default:
                cout << "Opcion no valida. Intenta de nuevo.\n";
                break;
        }

        // Pausa para visualizar los resultados del turno o el mensaje de derrota
        if (tamagochi->estaViva()) {
            cout << "\nPresiona un numero y Enter para continuar... ";
            cin >> espera;
        } else {
            cout << "\n=========================================";
            cout << "\n   ¡" << tamagochi->getNombre() << " ha MUERTO en combate!   ";
            cout << "\n=========================================\n";
            cout << "\nPresiona un numero y Enter para salir del juego... ";
            cin >> espera;
        }
    }
    
    // LIBERACIÓN DE MEMORIA: Se ejecuta únicamente si el bucle termina por la muerte del tamagochi
    delete tamagochi;
    delete monstruo;

    return 0;
}