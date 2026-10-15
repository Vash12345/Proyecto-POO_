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
        system("clear"); // Nota: Si usas Windows, puedes cambiarlo por system("cls")
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
        cout << "\n2- Atacar al enemigo (Normal)";
        cout << "\n3- Ataque Especial (Gasta 20 ENG)";
        cout << "\n4- Curar";
        cout << "\n5- Salir\n\nOpcion: ";
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

    // SOBRECARGA DE MÉTODOS (1/2): Versión normal de atacar
    void atacarA(Criatura* objetivo) {
        if (energia >= 10) {
            cout << "\n>> " << nombre << " ataca a " << objetivo->getNombre() << " causando " << ataque << " de dano!\n";
            objetivo->recibirDanio(ataque);
            setEnergia(energia - 10);
        } else {
            cout << "\n>> " << nombre << " no tiene suficiente energia para atacar. ¡Necesita descansar!\n";
        }
    }
    
    // SOBRECARGA DE MÉTODOS (2/2): Versión especial de atacar que suma daño extra
    void atacarA(Criatura* objetivo, int danioExtra) {
        if (energia >= 20) {
            int danioTotal = ataque + danioExtra;
            cout << "\n>> " << nombre << " realiza un ATAQUE ESPECIAL contra " << objetivo->getNombre() << " causando " << danioTotal << " de dano!\n";
            objetivo->recibirDanio(danioTotal);
            setEnergia(energia - 20);
        } else {
            cout << "\n>> " << nombre << " no tiene suficiente energia para el ataque especial. ¡Necesita descansar!\n";
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

    cout << "=== DEMOSTRACION DE CONTADOR STATIC ===\n";
    cout << "Criaturas actuales: " << Criatura::getContadorCriaturas() << "\n\n";
    
    // Crear criaturas de prueba para demostrar el contador
    Criatura* prueba1 = new Criatura();
    Criatura* prueba2 = new Criatura("Slime", 50, 5, 50);
    
    cout << "\nCriaturas tras crear pruebas: " << Criatura::getContadorCriaturas() << "\n\n";
    
    // Destruir las pruebas
    delete prueba1;
    delete prueba2;
    
    cout << "\nCriaturas tras destruir pruebas: " << Criatura::getContadorCriaturas() << "\n";
    cout << "=======================================\n\n";

    cout << "=== SIMULADOR DE CRIATURAS ===\n";
    
    // INSTANCIACIÓN DINÁMICA
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
                
            case 2: // Atacar normal
                if (monstruo->estaViva()) {
                    tamagochi->atacarA(monstruo);
                    
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
                
            case 3: // Ataque Especial (Uso del método sobrecargado)
                if (monstruo->estaViva()) {
                    tamagochi->atacarA(monstruo, 15); // Se llama a la segunda versión con daño extra
                    
                    if (monstruo->estaViva()) {
                        cout << "¡El enemigo contraataca!\n";
                        monstruo->atacarA(tamagochi);
                    } else {
                        cout << "¡Has derrotado a " << monstruo->getNombre() << "!\n";
                    }
                } else {
                    cout << "El enemigo ya esta derrotado.\n";
                }
                break;
                
            case 4: // Curar
                int cantidad_cura;
                cout << "Cuanta vida deseas curar?: ";
                cin >> cantidad_cura;
                tamagochi->curar(cantidad_cura);
                break;
            
            case 5: // Salir
                cout << "Saliendo del juego...\n";
                delete tamagochi; 
                delete monstruo;
                return 0;

            default:
                cout << "Opcion no valida. Intenta de nuevo.\n";
                break;
        }

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
    
    // LIBERACIÓN DE MEMORIA
    delete tamagochi;
    delete monstruo;

    return 0;
}