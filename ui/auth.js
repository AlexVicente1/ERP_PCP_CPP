const Auth = (() => {
  const SESSION_KEY = "erp_pcp_auth_session_v1";
  const SESSION_USER_KEY = "erp_pcp_auth_user_v1";
  const DEMO_PASS = "pcp123";
  const DEMO_USERS = new Set([
    "admin",
    "engineer",
    "user01",
    "user02",
    "user03",
    "user04",
    "user05",
    "user06",
    "user07",
    "user08",
    "user09"
  ]);

  const isLoggedIn = () => sessionStorage.getItem(SESSION_KEY) === "1";
  const currentUser = () => sessionStorage.getItem(SESSION_USER_KEY) || "";
  const login = (username, password) => {
    const normalizedUser = String(username || "").trim().toLowerCase();
    if (DEMO_USERS.has(normalizedUser) && password === DEMO_PASS) {
      sessionStorage.setItem(SESSION_KEY, "1");
      sessionStorage.setItem(SESSION_USER_KEY, normalizedUser);
      return true;
    }
    return false;
  };
  const logout = () => {
    sessionStorage.removeItem(SESSION_KEY);
    sessionStorage.removeItem(SESSION_USER_KEY);
  };

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

  return { isLoggedIn, currentUser, login, logout, protectPage };
})();

Auth.protectPage();
