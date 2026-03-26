const CACHE_NAME = "erp-pcp-ui-v1";
const APP_SHELL = [
  "./",
  "./login.html",
  "./index.html",
  "./produtos.html",
  "./ordens.html",
  "./logs.html",
  "./styles.css",
  "./app.js",
  "./auth.js",
  "./pubchemApi.js"
];

self.addEventListener("install", (event) => {
  event.waitUntil(caches.open(CACHE_NAME).then((cache) => cache.addAll(APP_SHELL)));
});

self.addEventListener("fetch", (event) => {
  event.respondWith(
    caches.match(event.request).then((cached) => {
      return (
        cached ||
        fetch(event.request).catch(() => {
          if (event.request.mode === "navigate") {
            return caches.match("./login.html");
          }
          return new Response("Offline", { status: 503, statusText: "Offline" });
        })
      );
    })
  );
});
