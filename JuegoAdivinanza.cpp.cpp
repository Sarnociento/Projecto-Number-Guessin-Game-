#include <iostream>
#include <cstdlib> // Necesaria para rand() y srand()
#include <ctime>   // Necesaria para time()
#include <chrono>  // Necesaria para el temporizador

void imprimirInstrucciones() 
{
    std::cout << "Welcome to the Number Guessing Game!" << '\n';
    std::cout << "I'm thinking of a number between 1 and 100." << '\n';
    std::cout << "You have X chances to guess the correct number depending on difficulty." << '\n';
    std::cout << '\n';
}

int conseguirValorDificultad() 
{
    std::cout << "Please select the difficulty level: " << '\n';
    std::cout << "1. Easy (10 chances)" << '\n';
    std::cout << "2. Medium (5 chances)" << '\n';
    std::cout << "3. Hard (3 chances)" << '\n';
    std::cout << '\n';
    std::cout << "Enter your choice: ";

    int dificultad{};
    std::cin >> dificultad;
    std::cout << '\n';

    switch (dificultad) 
    {
    case 1:
        std::cout << "Genial! Has seleccionado el nivel de dificultad F�cil." << std::endl;
        return 10; // 10 intentos para f�cil
    case 2:
        std::cout << "Genial! Has seleccionado el nivel de dificultad Medio." << std::endl;
        return 5; // 5 intentos para medio
    case 3:
        std::cout << "Genial! Has seleccionado el nivel de dificultad Dif�cil." << std::endl;
        return 3; // 3 intentos para dif�cil
    default:
        std::cout << "Elecci�n no v�lida. Se usar� la dificultad Medio por defecto." << std::endl;
        return 5; // Valor por defecto si se ingresa un n�mero no v�lido
    }
}

int main() 
{
    srand(static_cast<unsigned int>(time(NULL)));
    bool jugarDeNuevo = true;
    int mejoresPuntajes[3] = { INT_MAX, INT_MAX, INT_MAX }; // Mejores puntajes para cada dificultad

    while (jugarDeNuevo) 
    {
        imprimirInstrucciones();
        int intentosMaximos = conseguirValorDificultad();

        int numeroAleatorio = rand() % 100 + 1; // Se establece l�mite entre 0 - 99 y +1 para el 100
        int inputUsuario;
        bool haAdivinado = false;
        int intentos = 0;

        auto tiempoInicio = std::chrono::steady_clock::now(); // Iniciar temporizador

        while (intentos < intentosMaximos) 
        {
            std::cout << "Introduce tu adivinanza (entre 1 y 100): ";
            std::cin >> inputUsuario;

            // Comprobamos que el input est� dentro del rango v�lido
            if (inputUsuario < 1 || inputUsuario > 100) 
            {
                std::cout << "Coloca un valor v�lido entre 1 y 100" << '\n';
                continue; // Si no es v�lido, vuelve a pedir la entrada
            }

            intentos++;

            if (inputUsuario == numeroAleatorio) {
                std::cout << "�Felicitaciones! Adivinaste el n�mero en " << intentos << " intentos." << '\n';

                haAdivinado = true;
                break; // Sale del programa si acierta
            }

            // Proporcionar pistas
            if (intentos % 3 == 0) 
            {
                if (inputUsuario < numeroAleatorio) 
                {
                    std::cout << "Pista: �El n�mero es mayor que " << inputUsuario << "!" << '\n';
                }
                else {
                    std::cout << "Pista: �El n�mero es menor que " << inputUsuario << "!" << '\n';
                }
            }

            // Aqu� corregimos la l�gica de comparaci�n
            if (inputUsuario < numeroAleatorio) 
            {
                std::cout << "Incorrecto! El n�mero es mayor que " << inputUsuario << '\n';
            }
            else {
                std::cout << "Incorrecto! El n�mero es menor que " << inputUsuario << '\n';
            }
            std::cout << '\n';
        }

        auto tiempoFin = std::chrono::steady_clock::now(); // Fin del temporizador
        std::chrono::duration<double> tiempoElapsado = tiempoFin - tiempoInicio;

        if (!haAdivinado) 
        {
            std::cout << "Lo siento, has agotado tus intentos. El n�mero era: " << numeroAleatorio << '\n';
        }

        std::cout << "Tiempo total: " << tiempoElapsado.count() << " segundos." << '\n';

        // Actualizar el mejor puntaje
        if (haAdivinado && intentos < mejoresPuntajes[(int)(10 - intentosMaximos)]) 
        {
            mejoresPuntajes[(int)(10 - intentosMaximos)] = intentos;
            std::cout << "�Nuevo mejor puntaje para esta dificultad!" << '\n';
        }

        char respuesta;
        std::cout << "�Quieres jugar de nuevo? (s/n): ";
        std::cin >> respuesta;
        jugarDeNuevo = (respuesta == 's' || respuesta == 'S');

        std::cout << '\n';
    }

    return 0;
}