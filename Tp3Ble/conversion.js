// Récupère la valeur du payload supposée être la valeur lue par le CAN
let valeurCAN = msg.payload;

// Convertit la valeur CAN en pourcentage avec l'inversion
let pourcentage = (1 - valeurCAN / 4095) * 100;

// Arrondit le résultat à deux décimales, si nécessaire
pourcentage = Math.round(pourcentage * 100) / 100;

// Met à jour le payload avec le pourcentage calculé
msg.payload = pourcentage;

// Retourne le message modifié
return msg;
