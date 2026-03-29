#ifndef RESERVATIONSYSTEM_HPP
#define RESERVATIONSYSTEM_HPP

#include "ReservationRequest.hpp"
#include "Custom.hpp"
#include <string>


class ReservationSystem {

private:
    int room_count;
    int* room_capacities;
    Sala* lista_de_salas;


    // Estruturas internas escolhidas pelos alunos
    // para armazenar e gerenciar as reservas, os horários, ...

public:

    ReservationSystem(int room_count, int* room_capacities);
    ~ReservationSystem();

    bool reserve(ReservationRequest request);
    bool cancel(std::string course_name);

    void printSchedule();
    int converter_weekday(std::string weekday);

    // Outros métodos utilitários necessários
    // para auxiliar nas funções requisitadas
};

#endif