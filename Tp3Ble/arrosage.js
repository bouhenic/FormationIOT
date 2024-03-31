// Initialise les variables
let etatArrosage;
const seuilBas = 30;
const seuilHaut = 60;
let mode = flow.get('mode');

// Vérifie si le payload contient une valeur numérique
let humidite = parseFloat(msg.payload);
if (isNaN(humidite)) {
    // Gère le cas où humidite n'est pas un nombre
    // Par exemple, définir etatArrosage à une valeur indiquant une erreur ou ignorer la mise à jour
    etatArrosage = "Erreur: valeur d'humidité non valide";
} else {
    // Le payload est un nombre, continue avec la logique existante
    if (mode === false) {
        if (humidite < seuilBas) {
            // Si l'humidité est inférieure à 30% et le mode automatique est activé, déclenche l'arrosage
            etatArrosage = 1;
        } else if (humidite > seuilHaut) {
            // Si l'humidité est supérieure à 60% et le mode automatique est activé, stoppe l'arrosage
            etatArrosage = 0;
        } else {
            // Si l'humidité est entre 30% et 60% et le mode automatique est activé, ne change rien
            etatArrosage = flow.get("state") || "État inconnu"; // Utilise l'état actuel de l'arrosage ou un message par défaut si non disponible
        }
    } else {
        // Si le mode automatique n'est pas activé, pourrait définir etatArrosage à une valeur spécifique ou le laisser indéfini
        etatArrosage=flow.get('state');
    }
}

// Prépare le message de sortie avec l'état de l'arrosage
let msgSortie = { payload: etatArrosage };

// Retourne le message de sortie
return msgSortie;
