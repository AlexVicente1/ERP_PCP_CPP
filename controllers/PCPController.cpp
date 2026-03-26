#include "PCPController.h"

#include <iostream>

#include "../models/Produto.h"
#include "../utils/Logger.h"

namespace erp::pcp::controllers {

PCPController::PCPController(services::PCPService& pcpService) : pcpService_(pcpService) {}

void PCPController::runDemo() {
    utils::Logger::info("Initializing PCP module demo flow...");

    pcpService_.cadastrarProduto(models::Produto(1, "PA-001", "Produto Acabado A", 10, 20));
    pcpService_.cadastrarProduto(models::Produto(2, "MP-010", "Materia-Prima B", 80, 30));

    const auto produtos = pcpService_.listarProdutos();
    std::cout << "Total de produtos cadastrados: " << produtos.size() << '\n';

    const auto planejar = pcpService_.produtosParaPlanejamento();
    std::cout << "Produtos para planejamento: " << planejar.size() << '\n';

    utils::Logger::info("PCP module demo completed.");
}

}  // namespace erp::pcp::controllers
