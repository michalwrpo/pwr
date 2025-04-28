document.addEventListener("DOMContentLoaded", function () {
    const nav = document.querySelector("nav");
    const htmlMenu = document.getElementById("htmlmenu");

    if (htmlMenu) {
        htmlMenu.remove(); // usuwa stare <details> jeśli JS działa
    }

    // Tworzenie hamburgera
    const hamburger = document.createElement("div");
    hamburger.classList.add("hamburger");
    hamburger.innerHTML = "☰";

    // Tworzenie nowego kontenera na małe linki
    const smallMenu = document.createElement("div");
    smallMenu.classList.add("small-menu");
    smallMenu.style.display = "none"; // domyślnie ukryte

    // Lista linków
    const links = [
        {href: "about.html", text: "About Me"},
        {href: "projects.html", text: "Projects"}
    ];

    links.forEach(function (linkInfo) {
        const div = document.createElement("div");
        div.classList.add("navdivsmall");

        const a = document.createElement("a");
        a.href = linkInfo.href;
        a.classList.add("navlink");
        a.textContent = linkInfo.text;

        div.appendChild(a);
        smallMenu.appendChild(div);
    });

    // Dodawanie do nawigacji
    nav.appendChild(hamburger);
    nav.appendChild(smallMenu);

    // Kliknięcie hamburgera rozwija/zamyka menu
    hamburger.addEventListener("click", function () {
        if (smallMenu.style.display === "none") {
            smallMenu.style.display = "block";
        } else {
            smallMenu.style.display = "none";
        }
    });
});

const gallery = document.getElementById("gallery");

// Przykładowe URL-e obrazków
const imageUrls = [
    "labyrinth.png",
    "chinese-checkers.png",
    "hangman.png",
    "learnasm.png"
];

// Funkcja zwracająca obietnicę załadowania pojedynczego obrazu
function loadImage(url) {
    return new Promise(function (resolve, reject) {
        const img = new Image();
        img.src = url;
        img.alt = url;
        img.onload = () => resolve(img);
        img.onerror = () => reject(
            img.alt
            // new Error(`Nie udało się załadować obrazka: ${url}`)
        );
    });
}

// Ładowanie wszystkich obrazów równolegle
Promise.allSettled(imageUrls.map(loadImage))
    .then(results => {
        results.forEach(result => {
            if (result.status === "fulfilled") {
                gallery.appendChild(result.value);
            } else {
                gallery.innerHTML += result.reason;
                console.error("Nie udało się załadować obrazka:", result.reason);
            }
        });
    });


// Promise.all(imageUrls.map(loadImage)).then(function (images) {
//     images.forEach(function (img) {
//         gallery.appendChild(img);
//     });
// }).catch(function (error) {
//     console.error("Wystąpił błąd przy ładowaniu galerii:", error);
//     gallery.innerHTML = `
//     <p>Nie udało się załadować zdjęć. Spróbuj ponownie później.</p>
//     `;
// });
