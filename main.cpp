#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Criatura {
// CONTROL DE ACCESO: Atributos protegidos con private
private:
    string nombre;
    int vida, energia, ataque;
    int vidaMax;
    int energiaMax;

public:
    // CONSTRUCTOR por defecto
    Criatura() {
        nombre = "Sin nombre";
        vidaMax = 200;
        energiaMax = 200;
        setVida(100);
        setEnergia(100);
        ataque = 10;
        cout << "[Creada] Se ha creado correctamente a " << nombre << "\n";
    }

    // CONSTRUCTOR parametrizado usando setters
    Criatura(string n, int v, int a, int e = 100) {
        nombre = n;
        vidaMax = 200;
        energiaMax = 200;
        setVida(v);
        setEnergia(e);
        ataque = a;
        cout << "[Creada] Se ha creado correctamente a " << nombre << "\n";
    }

    // DESTRUCTOR: Mismo nombre de la clase con tilde, se llama al eliminar el objeto
    ~Criatura() {
        cout << "\n[Destruida] Se ha eliminado correctamente a " << nombre << "\n";
    }

    // SETTER DE VIDA: Valida que no baje de 0 ni pase del maximo
    void setVida(int v) {
        if (v < 0) {
            vida = 0;
        } else if (v > vidaMax) {
            vida = vidaMax;
        } else {
            vida = v;
        }
    }

    // SETTER DE ENERGIA: Valida que no baje de 0 ni pase del maximo
    void setEnergia(int e) {
        if (e < 0) {
            energia = 0;
        } else if (e > energiaMax) {
            energia = energiaMax;
        } else {
            energia = e;
        }
    }

    // GETTERS: Metodos de solo lectura
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }
    string getNombre() const { return nombre; }
    
    // METODO SETTER PARA EL NOMBRE
    void setNombre(string n) {
        nombre = n;
    }

    void pantalla(int& opc) {
        system("clear");
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
        cout << "\nSelecciona tu opcion: ";
        cout << "\n1- Descansar";
        cout << "\n2- Atacar (Recibir dano)";
        cout << "\n3- Curar";
        cout << "\n4- Salir\n\nOpcion: ";
        cin >> opc;
    }

    // Uso de setters en lugar de modificar atributos directos
    void descansar() {
        cout << "Descansando... recuperas 50 de energia.\n";
        setEnergia(energia + 50);
    }

    // Uso de setters en lugar de modificar atributos directos
    void curar(int cura) {
        if (vida >= vidaMax) {
            cout << "La vida ya esta llena.\n";
        } else { 
            cout << "Te has curado " << cura << " de vida.\n";
            setVida(vida + cura);
        }
    }
    
    // Uso de setters en lugar de modificar atributos directos
    void recibirDanio(int danio) {
        setVida(vida - danio);
    }
    
    bool estaViva() {
        return vida > 0;
    }
};

int main() {
    int espera, opc;
    string nombreMascota;

    // INSTANCIACION DINAMICA: Usando new (Criterio de rubrica)
    Criatura* tamagochi = new Criatura();
    
    cout << "Que nombre le quieres poner a tu Tamagochi?: ";
    cin >> nombreMascota;
    tamagochi->setNombre(nombreMascota);

    cout << "Tu tamagochi se llama: " << tamagochi->getNombre() << "\n\nPresiona Enter (introduce un numero) para continuar: ";
    cin >> espera;
        
    while (tamagochi->estaViva()) {
        tamagochi->pantalla(opc);

        switch (opc) {
            case 1:
                tamagochi->descansar();
                break;
                
            case 2:
                tamagochi->recibirDanio(20); 
                if (tamagochi->estaViva()) {
                    cout << tamagochi->getNombre() << " ha recibido 20 de dano." << "\n";
                    cout << "Sigue vivo y su vida es: " << tamagochi->getVida() << "\n";
                } else {
                    cout << tamagochi->getNombre() << " ha muerto por el dano recibido.\n";
                }
                break;
                
            case 3: {
                int cantidad_cura;
                cout << "Cuanta vida deseas curar?: ";
                cin >> cantidad_cura;
                tamagochi->curar(cantidad_cura);
                break;
            }
            
            case 4:
                cout << "Saliendo del juego...\n";
                // LIBERACION DE MEMORIA: Todo new debe tener su delete
                delete tamagochi; 
                return 0;

            default:
                cout << "Opcion no valida. Intenta de nuevo.\n";
                break;
        }

        if (tamagochi->estaViva()) {
            cout << "\nPresiona un numero y Enter para continuar...";
            cin >> espera;
        }
    }
    
    // Si muere por daño y sale del while, debemos liberar la memoria
    delete tamagochi;

    return 0;
}