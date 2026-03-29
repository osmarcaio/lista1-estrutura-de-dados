#include <iostream>

struct Reserva {
    std::string course_name;
    std::string weekday;
    int start_hour;
    int end_hour;
    int student_count;
};

struct Sala {
    int capacity;
    Reserva* reservas_segunda[14] = {nullptr};
    Reserva* reservas_terca[14] = {nullptr};
    Reserva* reservas_quarta[14] = {nullptr};
    Reserva* reservas_quinta[14] = {nullptr};
    Reserva* reservas_sexta[14] = {nullptr};

    Reserva** reservas_da_semana[5] = {reservas_segunda, reservas_terca, reservas_quarta, reservas_quinta, reservas_sexta};
};
