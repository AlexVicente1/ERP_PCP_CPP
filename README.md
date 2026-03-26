# ERP_PCP_CPP - Chemical Industry ERP (PCP)

Enterprise-grade C++17 project for Production Planning and Control in chemical manufacturing, inspired by industrial ERP workflows.

## Architecture

The solution follows Clean Architecture and SOLID-oriented boundaries:

- `src/domain`: core business model (entities, enums, value objects, domain services)
- `src/application`: orchestration layer (use cases, DTOs)
- `src/infrastructure`: adapters (repositories, logging, API integration, DB abstraction)
- `src/presentation/cli`: user interaction entrypoint
- `src/security`: authentication (RBAC demo) and audit trail
- `src/shared`: reusable cross-cutting utilities and exceptions
- `src/quality`, `src/production`, `src/inventory`: reserved modules for specialized expansions

## Implemented Industrial Modules

1. Chemical formulation with revision history (`ChemicalProduct`, `FormulaRevision`)
2. Lot traceability model (`BatchLot`)
3. Chemical API integration abstraction (`ChemicalApiClient`)
4. FISPQ report template generation (`FispqService`)
5. PCP/MRP order planning with automatic consumption and purchase suggestion (`CreateProductionOrderUseCase`)
6. Chemical inventory conversion mass-volume (`InventoryService`)
7. Industrial security with RBAC and audit (`AuthService`, `AuditLogger`)
8. Production execution lifecycle (`ProductionOrder`, `BatchStatus`)
9. Quality control decision engine (`QualityService`, `QualityInspection`)
10. Dashboard KPIs (`DashboardService`)

## Security Model

Demo users:

- `admin` / `pcp123` -> Administrator
- `engineer` / `pcp123` -> Chemical Engineer

Role authorization is enforced before sensitive operations.

## Database Strategy

`SQLiteReadyDatabase` provides a concrete database abstraction designed for future SQLite wiring without changing business layers.

## Build Example (g++)

From project root:

`g++ -std=c++17 main.cpp src/domain/entities/*.cpp src/domain/services/*.cpp src/application/usecases/*.cpp src/infrastructure/repositories/*.cpp src/infrastructure/api/*.cpp src/infrastructure/database/*.cpp src/infrastructure/logging/*.cpp src/security/auth/*.cpp src/security/audit/*.cpp src/presentation/cli/*.cpp -o erp_pcp_enterprise.exe`

## Next Enterprise Steps

- Persist repositories into SQLite
- Add formula version approval workflow
- Implement lot genealogy reporting
- Integrate external hazard/FISPQ APIs
- Add REST API for web dashboard
