#include "ReservationRequest.hpp"
#include "ReservationSystem.hpp"

#include <string>



ReservationSystem::ReservationSystem(int room_count, int* room_capacities) {
    this->room_count = room_count;
    this->room_capacities = room_capacities;

    this->lista_de_salas = new Sala[room_count];
    for (int i = 0; i < room_count; i++) {
            lista_de_salas[i].capacity = {room_capacities[i]};
    }
    // for (int i = 0; i < room_count; i++) {
    //     Reserva** reservas_da_semana[5];
    //     for (int j = 0; j < 5; j++) { 
    //         Reserva* dia_da_semana[14];
    //         for (int k = 0; k < 14; k++) { 
    //             dia_da_semana[k] = nullptr;
    //         reservas_da_semana[j] = dia_da_semana;
    //         }
    //     }
        
    //     Sala sala = {room_capacities[i], reservas_da_semana};
    //     lista_de_salas[i] = sala;
    // }
}

ReservationSystem::~ReservationSystem() {
    delete[] this->lista_de_salas;
}

bool ReservationSystem::reserve(ReservationRequest request) {

    Reserva* reserva = new Reserva{request.getCourseName(), request.getWeekday(), request.getStartHour(), request.getEndHour(), request.getStudentCount()};
    int indice_weekday = converter_weekday(request.getWeekday());

    for (int i = 0; i < this->room_count; i++) {
        Sala& sala_atual = this->lista_de_salas[i];
        if (sala_atual.capacity >= request.getStudentCount()) {
            
            bool sucesso = true;
            
            for (int j = (reserva->start_hour)-7; j < (reserva->end_hour)-7; j++) {

                if (sala_atual.reservas_da_semana[indice_weekday][j] != nullptr) {
                    sucesso = false;
                    break;
                }
            }
            if (sucesso) {
                for (int j = reserva->start_hour-7; j < reserva->end_hour-7; j++) {
                    sala_atual.reservas_da_semana[indice_weekday][j] = reserva;
                }
                
                return true;
            }
        }
    }
    return false;
}


int ReservationSystem::converter_weekday(std::string weekday) {
    if (weekday == "Segunda") {return 0;}
    else if (weekday == "Terça") {return 1;}
    else if (weekday == "Quarta") {return 2;}
    else if (weekday == "Quinta") {return 3;}
    else {return 4;}

}
