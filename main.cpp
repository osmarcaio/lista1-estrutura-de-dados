#include <iostream>
#include <string>

#include "ReservationSystem.hpp"
#include "ReservationRequest.hpp"


void testar(bool condicao, const std::string nome_teste) {
    if (condicao) {
        std::cout << "[PASSOU] " << nome_teste << std::endl;
    } else {
        std::cout << "[FALHOU] " << nome_teste << std::endl;
    }
}

int main() {
    

    std::cout << "===== TESTE 1: sistema criado =====" << std::endl;

    int room_capacities[3] = {20, 30, 50};
    ReservationSystem sistema(3, room_capacities);
    std::cout << "Sistema criado com 3 salas.\n" << std::endl;


    
    std::cout << "===== TESTE 2: reservas com sucesso =====" << std::endl;

    ReservationRequest r1("matematica", "segunda", 7, 9, 18);
    ReservationRequest r2("fisica", "segunda", 9, 11, 18);      // encosta no fim da outra
    ReservationRequest r3("quimica", "segunda", 7, 9, 25);      // mesma faixa da r1
    ReservationRequest r4("algoritmos", "terca", 10, 12, 45); 

    testar(sistema.reserve(r1), "Reserva 1 (matematica)");
    testar(sistema.reserve(r2), "Reserva 2 (fisica sem conflito 9-11)");
    testar(sistema.reserve(r3), "Reserva 3 (quimica em outra sala)");
    testar(sistema.reserve(r4), "Reserva 4 (algoritmos em sala grande)");

    std::cout << std::endl;



    std::cout << "===== TESTE 3: falha por capacidade =====" << std::endl;

    ReservationRequest r5("biologia", "quarta", 8, 10, 60);
    testar(sistema.reserve(r5), "Reserva 5 (biologia, 60 alunos)");

    std::cout << std::endl;



    std::cout << "===== TESTE 4: ocupando todas as salas no mesmo horario =====" << std::endl;

    ReservationRequest r6("historia", "terca", 14, 16, 15); // sala 20
    ReservationRequest r7("geografia", "terca", 14, 16, 25); // sala 30
    ReservationRequest r8("filosofia", "terca", 14, 16, 40); // sala 50
    ReservationRequest r9("sociologia", "terca", 14, 16, 10); // deveria falhar: todas ocupadas

    testar(sistema.reserve(r6), "Reserva 6 (historia)");
    testar(sistema.reserve(r7), "Reserva 7 (geografia)");
    testar(sistema.reserve(r8), "Reserva 8 (filosofia)");
    testar(sistema.reserve(r9), "Reserva 9 (sociologia, sem sala disponivel)");

    std::cout << std::endl;



    std::cout << "===== TESTE 5: cancelamentos =====" << std::endl;

    testar(sistema.cancel("fisica"), "Cancelar reserva existente: fisica");
    testar(sistema.cancel("fisica"), "Cancelar de novo a mesma reserva");
    testar(sistema.cancel("nao_existe"), "Cancelar disciplina inexistente");

    std::cout << std::endl;



    std::cout << "===== TESTE 6: reservar apos cancelamento =====" << std::endl;

    ReservationRequest r10("programacao", "segunda", 9, 11, 18);
    testar(sistema.reserve(r10) == true, "Reserva 10 (programacao apos cancelar fisica)");

    std::cout << std::endl;



    std::cout << "===== TESTE 7: printSchedule =====" << std::endl;


    sistema.printSchedule();

    return 0;
}