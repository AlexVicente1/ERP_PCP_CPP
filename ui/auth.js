const Auth = (() => {
  const SESSION_KEY = "erp_pcp_auth_session_v1";
  const DEMO_USER = "admin";
  const DEMO_PASS = "pcp123";

  const isLoggedIn = () => sessionStorage.getItem(SESSION_KEY) === "1";
  const login = (username, password) => {
    if (username === DEMO_USER && password === DEMO_PASS) {
      sessionStorage.setItem(SESSION_KEY, "1");
      return true;
    }
    return false;
  };
  const logout = () => sessionStorage.removeItem(SESSION_KEY);

  const protectPage = () => {
    const page = document.body?.dataset?.page || "";
    const isLoginPage = page === "login";
    if (!isLoginPage && !isLoggedIn()) {
      window.location.href = "./login.html";
    }
    if (isLoginPage && isLoggedIn()) {
      window.location.href = "./index.html";
    }
  };

  return { isLoggedIn, login, logout, protectPage };
})();

Auth.protectPage();
