// Récupère la valeur d'humidité du payload
let humidite = msg.payload;

// Définit les seuils pour l'humidité
const seuilBas = 40;
const seuilHaut = 80;

// Récupère la valeur du mode du contexte du flux pour déterminer si l'arrosage est géré automatiquement
let mode = flow.get('mode');

// Initialise une variable pour stocker l'état de l'arrosage
let etatArrosage;

// Vérifie si le mode automatique est activé
if (mode === false) {
    if (humidite < seuilBas) {
        // Si l'humidité est inférieure à 40% et le mode automatique est activé, déclenche l'arrosage
        etatArrosage = 1;
        flow.set("etatArrosage", etatArrosage)
    } else if (humidite > seuilHaut) {
        // Si l'humidité est supérieure à 80% et le mode automatique est activé, stoppe l'arrosage
        etatArrosage = 0;
        flow.set("etatArrosage", etatArrosage)
    } else {
        // Si l'humidité est entre 40% et 80% et le mode automatique est activé, ne change rien
        etatArrosage = flow.get("etatArrosage");
    }
} else {
    // Si le mode automatique n'est pas activé (mode manuel)
    etatArrosage=flow.get("etatPompe")
}

// Prépare le message de sortie avec l'état de l'arrosage
let msgSortie = { payload: etatArrosage };

// Retourne le message de sortie
return msgSortie;
