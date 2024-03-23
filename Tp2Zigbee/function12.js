// Récupère l'ampoule sélectionnée depuis le contexte de stockage ou initialise à null si non définie
let selectedBulb = flow.get("selectedBulb") || null;
let spot;

// Gère la sélection de l'ampoule
if (msg.payload.action == "arrow_left_click") {
    // Sélectionne l'ampoule de gauche
    flow.set("selectedBulb", "left");
    return [null, null]; // Ne transmet aucun message car c'est une action de sélection
} else if (msg.payload.action == "arrow_right_click") {
    // Sélectionne l'ampoule de droite
    flow.set("selectedBulb", "right");
    return [null, null]; // Ne transmet aucun message car c'est une action de sélection
}

// Si une action est déclenchée, prépare le message en fonction de l'action
if (selectedBulb) {
    if (msg.payload.action == "toggle") {
        spot = { "payload": { "state": "toggle" } };
    } else if (msg.payload.action == "brightness_up_click") {
        spot = { "payload": { "brightness_step": 40 } };
    } else if (msg.payload.action == "brightness_down_click") {
        spot = { "payload": { "brightness_step": -40 } };
    }
}

// Détermine sur quelle sortie envoyer le message en fonction de l'ampoule sélectionnée
let output = [null, null]; // Initialise les deux sorties à null
if (spot) {
    if (selectedBulb == "left") {
        output[0] = spot; // Envoie le message à l'ampoule de gauche
    } else if (selectedBulb == "right") {
        output[1] = spot; // Envoie le message à l'ampoule de droite
    }
}

return output;
