# ERP PCP CPP

Projeto de estudo em C++ para PCP (Planejamento e Controle da Produção), com foco na indústria química, combinando:

- backend em C++17 com arquitetura em camadas;
- painel web para demonstração de fluxo operacional;
- conceitos de segurança, auditoria e rastreabilidade.

## Visão geral

O sistema cobre um fluxo essencial de ERP/PCP:

- cadastro de produtos químicos e propriedades;
- criação de ordens de produção com validações de estoque;
- indicadores de painel (KPIs);
- registros operacionais para auditoria;
- modelo extensível para qualidade, inventário e produção.

## Arquitetura da solução

O backend segue separação de responsabilidades inspirada em Arquitetura Limpa e nos princípios SOLID:

- `src/domain`: entidades, enumerações, objetos de valor e serviços de domínio;
- `src/application`: casos de uso e objetos de transferência de dados;
- `src/infrastructure`: repositórios, registros, integrações e abstração de banco;
- `src/presentation/cli`: interface de linha de comando;
- `src/security`: autenticação (RBAC) e trilha de auditoria;
- `src/shared`: utilitários e exceções compartilhadas;
- `src/quality`, `src/production`, `src/inventory`: módulos reservados para expansão.

## Módulos implementados

1. Formulação química com histórico de revisão (`ChemicalProduct`, `FormulaRevision`);
2. Rastreabilidade de lotes (`BatchLot`);
3. Integração com API química (`ChemicalApiClient`);
4. Estrutura para relatório FISPQ (`FispqService`);
5. Planejamento PCP/MRP com sugestão de compra (`CreateProductionOrderUseCase`);
6. Conversões de inventário massa-volume (`InventoryService`);
7. Controle de acesso por perfil e auditoria (`AuthService`, `AuditLogger`);
8. Ciclo de vida de ordem (`ProductionOrder`, `BatchStatus`);
9. Motor de decisão de qualidade (`QualityService`, `QualityInspection`);
10. Serviço de indicadores e painel (`DashboardService`).

## Estrutura do repositório

```text
ERP_PCP_CPP/
|- controllers/
|- core/
|- data/
|- models/
|- repository/
|- services/
|- src/
|  |- application/
|  |- domain/
|  |- infrastructure/
|  |- presentation/
|  |- security/
|  `- shared/
|- ui/
|- utils/
`- main.cpp
```

## Requisitos

- compilador C++ com suporte ao padrão C++17 (g++, clang ou MSVC);
- Git;
- navegador moderno para o painel web.

## Compilação e execução (CLI)

No diretório raiz do projeto:

```bash
g++ -std=c++17 main.cpp src/domain/entities/*.cpp src/domain/services/*.cpp src/application/usecases/*.cpp src/infrastructure/repositories/*.cpp src/infrastructure/api/*.cpp src/infrastructure/database/*.cpp src/infrastructure/logging/*.cpp src/security/auth/*.cpp src/security/audit/*.cpp src/presentation/cli/*.cpp -o erp_pcp_enterprise.exe
```

Depois:

```bash
./erp_pcp_enterprise.exe
```

## Painel web (UI)

A interface web está em `ui/` com as páginas:

- `ui/login.html`
- `ui/index.html`
- `ui/produtos.html`
- `ui/ordens.html`
- `ui/logs.html`

Para melhor compatibilidade (PWA/service worker), execute um servidor local simples:

```bash
python -m http.server 5500
```

Depois, abra:

- `http://localhost:5500/ui/login.html`

Credenciais de demonstração:

- `admin` / `pcp123` (administrador);
- `engineer` / `pcp123` (engenharia).

## Segurança

- autenticação por perfis (RBAC) para operações sensíveis;
- logs operacionais e auditoria para rastreabilidade;
- base preparada para endurecimento futuro (tokens, hashing robusto e trilha ampliada).

## Estratégia de persistência

`SQLiteReadyDatabase` fornece uma abstração pronta para evolução para SQLite, sem acoplamento da regra de negócio.

## Próximos passos

- persistência completa em SQLite;
- workflow de aprovação de revisão de fórmula;
- genealogia de lotes e rastreabilidade avançada;
- integração externa de risco/FISPQ;
- API REST para o painel web;
- pipeline CI/CD e testes automatizados.

## Imagens do sistema

### Painel principal

![Painel principal do ERP PCP](docs/images/dashboard-interface.png)

## Licença

Projeto de estudo para fins acadêmicos e demonstração técnica.
