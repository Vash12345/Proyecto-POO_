#include <iostream>
#include <string>

class Criatura {
private:
    std::string nombre;
    int vida;
    int energia;

public:
    // Constructor por parámetro
    Criatura(std::string p_nombre, int p_vida, int p_energia) {
        nombre = p_nombre;
        vida = p_vida;
        energia = p_energia;
        std::cout << "Criatura " << nombre << " creada." << std::endl;
    }

    // Destructor
    ~Criatura() {
        std::cout << "Criatura " << nombre << " destruida de la memoria." << std::endl;
    }

    // Getters (Obtener)
    std::string getNombre() const { return nombre; }
    int getVida() const { return vida; }
    int getEnergia() const { return energia; }

    // Setters (Modificar)
    void setNombre(const std::string &nuevoNombre) { nombre = nuevoNombre; }
    void setVida(int nuevaVida) { vida = nuevaVida; }
    void setEnergia(int nuevaEnergia) { energia = nuevaEnergia; }

    // Métodos de acciones
    void descansa() {
        energia += 15;
        std::cout << nombre << " esta descansando. Energia actual: " << energia << std::endl;
    }

    void atacar() {
        if (energia >= 10) {
            energia -= 10;
            std::cout << nombre << " realizo un ataque. Energia restante: " << energia << std::endl;
        } else {
            std::cout << nombre << " no tiene suficiente energia para atacar." << std::endl;
        }
    }

    void recibirDano(int cantidadDano) {
        vida -= cantidadDano;
        if (vida < 0) vida = 0;
        std::cout << nombre << " recibio " << cantidadDano << " de danio. Vida restante: " << vida << std::endl;
    }
};

int main() {
    Criatura criatura1("Dragon", 100, 50);

    criatura1.atacar();
    criatura1.recibirDano(20);
    criatura1.descansa();

    return 0;
}