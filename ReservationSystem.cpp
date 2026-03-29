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
    if (weekday == "segunda") {return 0;}
    else if (weekday == "terca") {return 1;}
    else if (weekday == "quarta") {return 2;}
    else if (weekday == "quinta") {return 3;}
    else {return 4;} // Sem tratamento de erro mesmo

}

bool ReservationSystem::cancel(std::string course_name) {
    for (int sala = 0; sala < this->room_count; sala++) {
        for (int dia_da_semana = 0; dia_da_semana < 5; dia_da_semana++) {
            for (int hora = 0; hora < 14; hora++) {
                Reserva* essa_reserva = this->lista_de_salas[sala].reservas_da_semana[dia_da_semana][hora];

                if (essa_reserva == nullptr) {
                    continue;
                }

                if (essa_reserva->course_name == course_name) {

                    int campos_para_cancelar = (essa_reserva->end_hour - essa_reserva->start_hour);
                    for (int i = 0; i < campos_para_cancelar; i++) {
                        this->lista_de_salas[sala].reservas_da_semana[dia_da_semana][hora+i] = nullptr;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void ReservationSystem::printSchedule() {
    std::cout << "\n# SALAS & RESERVAS" << std::endl;
    for (int i = 0; i < this->room_count; i++) {
        Sala& sala_atual = this->lista_de_salas[i];

        std::cout << "  Sala " << i << " - [Capacidade: " << sala_atual.capacity << "]" << std::endl;
        for (int idx_semana = 0; idx_semana < 5; idx_semana++) {

            Reserva* ultima_reserva = nullptr;
            for (int idx_hora = 0; idx_hora < 14; idx_hora++) {
                Reserva* reserva_atual = sala_atual.reservas_da_semana[idx_semana][idx_hora];
                if (reserva_atual == nullptr | reserva_atual == ultima_reserva) {
                    continue;
                };

                std::cout 
                    << "    "
                    << reserva_atual->weekday 
                    << " "
                    << reserva_atual->start_hour 
                    << ":00-" 
                    << reserva_atual->end_hour << ":00 --> "
                    << reserva_atual->course_name 
                    << " ["
                    << reserva_atual->student_count
                    << " estudantes] "
                    << std::endl;
                ultima_reserva = reserva_atual;
            }
        }
        std::cout << std::endl;
    }
}
