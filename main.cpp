#include <iostream>
#include <string>

#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"


int main() {
    int room_capacities[1] = {20};
    ReservationSystem sistema = {1, room_capacities};
    ReservationRequest reserva1 = {"matematica", "terca", 9, 11, 20};
    ReservationRequest reserva2 = {"portugues", "terca", 10, 13, 15};


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
