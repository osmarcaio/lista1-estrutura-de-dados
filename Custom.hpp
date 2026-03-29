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

    Reserva* reservas_da_semana[5][14] = {};
};
