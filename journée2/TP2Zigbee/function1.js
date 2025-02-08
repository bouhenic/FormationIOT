// Récupère les valeurs actuelles depuis le contexte
let selectedBulb = flow.get("selectedBulb") || null;
let brightness = flow.get("brightness") || 100;
let color = flow.get("color") || "#FFFFFF";
let spot = null;

// Debug : Affiche les valeurs actuelles
node.warn(`SelectedBulb: ${selectedBulb}, Brightness: ${brightness}, Color: ${color}`);

// Mise à jour de la sélection de lampe
if (msg.payload.action === "arrow_left_click") {
    selectedBulb = "left";
    flow.set("selectedBulb", selectedBulb);
    return [null, null, { payload: "Ampoule" }];
}

if (msg.payload.action === "arrow_right_click") {
    selectedBulb = "right";
    flow.set("selectedBulb", selectedBulb);
    return [null, null, { payload: "LED_strip" }];
}

// Vérifie si une lampe est sélectionnée
if (!selectedBulb) {
    return [null, null, { payload: "Aucune lampe sélectionnée" }];
}

// Gestion des modifications de luminosité ou de couleur
if (typeof msg.payload === "number") {
    // Mise à jour de la luminosité
    brightness = Math.round(msg.payload * 10); // Remap en 0-100 si nécessaire
    flow.set("brightness", brightness); // Sauvegarde dans le contexte
    node.warn(`Brightness updated: ${brightness}`);

    // Prépare le message pour transmettre immédiatement le changement
    if (selectedBulb === "left") {
        // Pour l'ampoule : uniquement `brightness`
        spot = { payload: { brightness: brightness } };
    } else if (selectedBulb === "right") {
        // Pour le LED strip : inclut `brightness` et `color`
        spot = { payload: { brightness: brightness, color: color } };
    }
}

if (typeof msg.payload === "string" && selectedBulb === "right") {
    // Mise à jour de la couleur via le color picker
    color = msg.payload.startsWith("#") ? msg.payload : `#${msg.payload}`; // Ajoute `#` si manquant
    flow.set("color", color); // Sauvegarde dans le contexte
    node.warn(`Color updated: ${color}`);

    // Prépare le message pour transmettre immédiatement le changement
    spot = { payload: { brightness: brightness, color: color } };
}

// Commandes on/off avec les valeurs actuelles
if (msg.payload.action === "on") {
    if (selectedBulb === "left") {
        // Pour l'ampoule : uniquement `state`
        spot = { payload: { state: "on" } };
    } else if (selectedBulb === "right") {
        // Pour le LED strip : inclut luminosité et couleur
        spot = { payload: { state: "on", brightness: brightness, color: color } };
    }
}

if (msg.payload.action === "off") {
    if (selectedBulb === "left") {
        // Pour l'ampoule : uniquement `state`
        spot = { payload: { state: "off" } };
    } else if (selectedBulb === "right") {
        // Pour le LED strip : inclut luminosité et couleur
        spot = { payload: { state: "off", brightness: brightness, color: color } };
    }
}

// Détermine la sortie
let output = [null, null, null];
if (spot) {
    output[selectedBulb === "left" ? 0 : 1] = spot;
}

// Toujours envoyer uniquement le nom de la lampe sélectionnée sur la troisième sortie
output[2] = { payload: selectedBulb === "left" ? "Ampoule" : "LED_strip" };
return output;
