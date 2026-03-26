const PubChemApi = (() => {
  const baseUrl = "https://pubchem.ncbi.nlm.nih.gov/rest/pug/compound/name";

  const fetchByName = async (compoundName) => {
    const cleanName = String(compoundName || "").trim();
    if (!cleanName) {
      throw new Error("Informe um nome químico válido.");
    }

    const url = `${baseUrl}/${encodeURIComponent(
      cleanName
    )}/property/MolecularFormula,MolecularWeight/JSON`;
    const response = await fetch(url);
    if (!response.ok) {
      throw new Error("Composto não encontrado na base PubChem.");
    }

    const data = await response.json();
    const prop = data?.PropertyTable?.Properties?.[0];
    if (!prop) {
      throw new Error("Resposta inválida do PubChem.");
    }

    return {
      name: cleanName,
      molecularFormula: prop.MolecularFormula || "",
      molecularWeight: prop.MolecularWeight || ""
    };
  };

  return { fetchByName };
})();
