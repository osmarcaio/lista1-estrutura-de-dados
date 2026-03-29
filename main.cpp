#include <iostream>
#include <string>

#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"


int main() {
    int room_capacities[2] = {25, 20};
    ReservationSystem sistema = {2, room_capacities};
    ReservationRequest reserva1 = {"matematica", "Terça", 9, 11, 20};
    ReservationRequest reserva2 = {"portugues", "Terça", 7, 10, 21};


    if (sistema.reserve(reserva1)) {
        std::cout << "Deu bom" << std::endl;
    }
    else {
        std::cout << "Deu ruim" << std::endl;
    }

    if (sistema.reserve(reserva2)) {
        std::cout << "Deu bom" << std::endl;
    }
    else {
        std::cout << "Deu ruim" << std::endl;
    }

    return 0;
}
