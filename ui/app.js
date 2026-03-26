const STORAGE_KEY = "erp_pcp_demo_data_v1";
const state = {
  produtos: [],
  ordens: [],
  logs: []
};

const getEl = (id) => document.getElementById(id);
const produtoForm = getEl("produtoForm");
const ordemForm = getEl("ordemForm");
const produtosBody = getEl("produtosBody");
const ordensBody = getEl("ordensBody");
const logList = getEl("logList");
const dashboardResumo = getEl("dashboardResumo");
const kpiProdutos = getEl("kpiProdutos");
const kpiOrdens = getEl("kpiOrdens");
const kpiCritico = getEl("kpiCritico");
const btnConsultarQuimica = getEl("btnConsultarQuimica");
const consultaQuimica = getEl("consultaQuimica");
const loginForm = getEl("loginForm");
const consultaProdutoForm = getEl("consultaProdutoForm");
const consultaProdutoTermo = getEl("consultaProdutoTermo");
const consultaProdutoResultado = getEl("consultaProdutoResultado");
const reposicaoForm = getEl("reposicaoForm");
let consultaProdutoSelecionadoId = null;

const saveState = () => localStorage.setItem(STORAGE_KEY, JSON.stringify(state));
const loadState = () => {
  const raw = localStorage.getItem(STORAGE_KEY);
  if (!raw) return;
  try {
    const parsed = JSON.parse(raw);
    state.produtos = Array.isArray(parsed.produtos) ? parsed.produtos : [];
    state.ordens = Array.isArray(parsed.ordens) ? parsed.ordens : [];
    state.logs = Array.isArray(parsed.logs) ? parsed.logs : [];
  } catch (_) {}
};

const addLog = (message, type = "info") => {
  const date = new Date().toLocaleString("pt-BR");
  state.logs.unshift({ at: date, message, type });
  state.logs = state.logs.slice(0, 200);
  saveState();
  renderLogs();
};

const renderLogs = () => {
  if (!logList) return;
  logList.innerHTML = "";
  if (!state.logs.length) {
    logList.innerHTML = `<li class="empty">Sem logs ainda.</li>`;
    return;
  }
  state.logs.forEach((entry) => {
    const li = document.createElement("li");
    li.className = entry.type;
    li.textContent = `[${entry.at}] ${entry.message}`;
    logList.appendChild(li);
  });
};

const updateKPIs = () => {
  if (kpiProdutos) kpiProdutos.textContent = state.produtos.length;
  if (kpiOrdens) kpiOrdens.textContent = state.ordens.length;
  if (kpiCritico) {
    kpiCritico.textContent = state.produtos.filter((p) => p.estoqueAtual < p.estoqueMinimo).length;
  }
};

const renderProdutos = () => {
  if (!produtosBody) return;
  produtosBody.innerHTML = "";
  if (!state.produtos.length) {
    produtosBody.innerHTML = `<tr><td class="empty" colspan="8">Nenhum produto cadastrado.</td></tr>`;
    return;
  }
  state.produtos.forEach((p) => {
    const critico = p.estoqueAtual < p.estoqueMinimo;
    const tr = document.createElement("tr");
    tr.innerHTML = `<td>${p.id}</td><td>${p.codigo}</td><td>${p.descricao}</td><td>${p.molecularFormula || "-"}</td><td>${p.molecularWeight || "-"}</td><td>${p.estoqueAtual}</td><td>${p.estoqueMinimo}</td><td class="${critico ? "status-critico" : "status-ok"}">${critico ? "Crítico" : "OK"}</td>`;
    produtosBody.appendChild(tr);
  });
};

const getProdutoByTermo = (termoRaw) => {
  const termo = String(termoRaw || "").trim();
  if (!termo) return null;
  if (/^\d+$/.test(termo)) {
    const id = Number(termo);
    return state.produtos.find((p) => p.id === id) || null;
  }
  const termoLower = termo.toLowerCase();
  return state.produtos.find((p) => p.codigo.toLowerCase() === termoLower) || null;
};

const renderConsultaProduto = (produto) => {
  if (!consultaProdutoResultado) return;
  if (!produto) {
    consultaProdutoResultado.className = "consulta-result muted";
    consultaProdutoResultado.textContent = "Produto não encontrado.";
    return;
  }
  const status = produto.estoqueAtual < produto.estoqueMinimo ? "Crítico" : "OK";
  consultaProdutoResultado.className = "consulta-result";
  consultaProdutoResultado.innerHTML =
    `<strong>${produto.codigo} - ${produto.descricao}</strong><br>` +
    `Estoque atual: <strong>${produto.estoqueAtual}</strong> | ` +
    `Estoque mínimo: <strong>${produto.estoqueMinimo}</strong> | ` +
    `Status: <strong>${status}</strong>`;
};

const renderOrdens = () => {
  if (!ordensBody) return;
  ordensBody.innerHTML = "";
  if (!state.ordens.length) {
    ordensBody.innerHTML = `<tr><td class="empty" colspan="3">Nenhuma ordem criada.</td></tr>`;
    return;
  }
  state.ordens.forEach((o) => {
    const tr = document.createElement("tr");
    tr.innerHTML = `<td>${o.numero}</td><td>${o.produtoId}</td><td>${o.quantidade}</td>`;
    ordensBody.appendChild(tr);
  });
};

const renderResumo = () => {
  if (!dashboardResumo) return;
  dashboardResumo.innerHTML = "";
  const criticos = state.produtos.filter((p) => p.estoqueAtual < p.estoqueMinimo);
  if (!criticos.length) {
    dashboardResumo.innerHTML = `<li class="status-ok">Nenhum item em estoque crítico.</li>`;
    return;
  }
  criticos.forEach((p) => {
    const li = document.createElement("li");
    li.className = "status-critico";
    li.textContent = `${p.codigo} abaixo do mínimo (${p.estoqueAtual}/${p.estoqueMinimo})`;
    dashboardResumo.appendChild(li);
  });
};

const exportarJson = () => {
  const blob = new Blob([JSON.stringify(state, null, 2)], { type: "application/json" });
  const a = document.createElement("a");
  a.href = URL.createObjectURL(blob);
  a.download = "simulacao_planejamento.json";
  a.click();
  URL.revokeObjectURL(a.href);
  addLog("Dados exportados para JSON.");
};

const importarJson = (file) => {
  if (!file) return;
  const reader = new FileReader();
  reader.onload = () => {
    try {
      const parsed = JSON.parse(String(reader.result));
      state.produtos = Array.isArray(parsed.produtos) ? parsed.produtos : [];
      state.ordens = Array.isArray(parsed.ordens) ? parsed.ordens : [];
      state.logs = Array.isArray(parsed.logs) ? parsed.logs : [];
      addLog("Arquivo JSON importado com sucesso.");
      renderAll();
    } catch (_) {
      addLog("Falha ao importar JSON inválido.", "error");
    }
  };
  reader.readAsText(file);
};

const resetarDemo = () => {
  if (!confirm("Deseja realmente apagar os dados da simulação?")) return;
  state.produtos = [];
  state.ordens = [];
  state.logs = [];
  saveState();
  renderAll();
};

const bindEvents = () => {
  if (loginForm) {
    const loginLog = getEl("loginLog");
    loginForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const user = getEl("loginUser").value.trim();
      const pass = getEl("loginPass").value;
      if (Auth.login(user, pass)) {
        window.location.href = "./index.html";
      } else if (loginLog) {
        loginLog.innerHTML = `<li class="error">Usuário ou senha inválidos.</li>`;
      }
    });
  }

  const btnLogout = getEl("btnLogout");
  if (btnLogout) {
    btnLogout.addEventListener("click", () => {
      Auth.logout();
      window.location.href = "./login.html";
    });
  }

  if (btnConsultarQuimica && consultaQuimica) {
    btnConsultarQuimica.addEventListener("click", async () => {
      try {
        const query = consultaQuimica.value.trim();
        if (!query) return addLog("Informe um composto para consulta prévia.", "error");
        const result = await PubChemApi.fetchByName(query);
        const codigo = getEl("produtoCodigo");
        const descricao = getEl("produtoDescricao");
        const formula = getEl("produtoFormula");
        const peso = getEl("produtoPeso");
        if (codigo && !codigo.value.trim()) codigo.value = query.toUpperCase().replace(/\s+/g, "-");
        if (descricao) descricao.value = result.name;
        if (formula) formula.value = result.molecularFormula;
        if (peso) peso.value = result.molecularWeight;
        addLog(`Consulta PubChem OK: ${result.name} (${result.molecularFormula}).`);
      } catch (error) {
        addLog(error.message || "Erro ao consultar API química.", "error");
      }
    });
  }

  if (produtoForm) {
    produtoForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const produto = {
        id: Number(getEl("produtoId").value),
        codigo: getEl("produtoCodigo").value.trim(),
        descricao: getEl("produtoDescricao").value.trim(),
        estoqueAtual: 0,
        estoqueMinimo: 0,
        molecularFormula: getEl("produtoFormula") ? getEl("produtoFormula").value.trim() : "",
        molecularWeight: getEl("produtoPeso") ? getEl("produtoPeso").value.trim() : ""
      };
      if (state.produtos.some((p) => p.id === produto.id)) return addLog(`Produto ID ${produto.id} ja existe.`, "error");
      state.produtos.push(produto);
      saveState();
      addLog(`Produto ${produto.codigo} cadastrado.`);
      produtoForm.reset();
      renderAll();
    });
  }

  if (consultaProdutoForm && consultaProdutoTermo) {
    consultaProdutoForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const produto = getProdutoByTermo(consultaProdutoTermo.value);
      consultaProdutoSelecionadoId = produto ? produto.id : null;
      renderConsultaProduto(produto);
      if (!produto) return addLog(`Consulta de produto sem resultado para "${consultaProdutoTermo.value.trim()}".`, "error");
      addLog(`Consulta do produto ${produto.codigo}: estoque ${produto.estoqueAtual}, mínimo ${produto.estoqueMinimo}.`);
    });
  }

  if (reposicaoForm) {
    reposicaoForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const produtoId = Number(getEl("reposicaoProdutoId").value);
      const quantidade = Number(getEl("reposicaoQuantidade").value);
      const fornecedor = (getEl("reposicaoFornecedor")?.value || "").trim();
      const produto = state.produtos.find((p) => p.id === produtoId);
      if (!produto) return addLog(`Produto ${produtoId} não encontrado para reposição.`, "error");
      if (quantidade <= 0) return addLog("Informe uma quantidade válida para reposição.", "error");
      produto.estoqueAtual += quantidade;
      saveState();
      addLog(
        `Entrada de estoque registrada para ${produto.codigo}: +${quantidade}` +
        `${fornecedor ? ` (Fornecedor: ${fornecedor})` : ""}.`
      );
      reposicaoForm.reset();
      if (consultaProdutoSelecionadoId === produto.id) renderConsultaProduto(produto);
      renderAll();
    });
  }

  if (ordemForm) {
    ordemForm.addEventListener("submit", (event) => {
      event.preventDefault();
      const numero = Number(getEl("ordemNumero").value);
      const produtoId = Number(getEl("ordemProdutoId").value);
      const quantidade = Number(getEl("ordemQuantidade").value);
      const produto = state.produtos.find((p) => p.id === produtoId);
      if (!produto) return addLog(`Produto ${produtoId} nao encontrado.`, "error");
      if (quantidade <= 0 || quantidade > produto.estoqueAtual) return addLog(`Estoque insuficiente para OP ${numero}.`, "error");
      if (state.ordens.some((o) => o.numero === numero)) return addLog(`OP ${numero} já existe.`, "error");
      produto.estoqueAtual -= quantidade;
      state.ordens.push({ numero, produtoId, quantidade });
      saveState();
      addLog(`OP ${numero} criada com sucesso.`);
      ordemForm.reset();
      renderAll();
    });
  }

  const btnExportar = getEl("btnExportar");
  const btnResetar = getEl("btnResetar");
  const importJson = getEl("importJson");
  if (btnExportar) btnExportar.addEventListener("click", exportarJson);
  if (btnResetar) btnResetar.addEventListener("click", resetarDemo);
  if (importJson) importJson.addEventListener("change", (e) => importarJson(e.target.files[0]));
};

const renderAll = () => {
  updateKPIs();
  renderProdutos();
  renderOrdens();
  renderLogs();
  renderResumo();
  if (consultaProdutoSelecionadoId !== null) {
    const selecionado = state.produtos.find((p) => p.id === consultaProdutoSelecionadoId) || null;
    renderConsultaProduto(selecionado);
  }
};

loadState();
bindEvents();
renderAll();
