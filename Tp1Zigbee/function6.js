let lastInput2 = flow.get("lastInput2") || ""; // Récupérer la dernière entrée stockée

if (msg.payload === "button_pressed") { // Identifier si le message provient du bouton
    // Utiliser la valeur stockée comme irrigation_target
    let irrigationTarget = lastInput2;
    // Créer et retourner un objet avec la propriété irrigation_target définie
    return { payload: { "irrigation_target": irrigationTarget } };
} else { // Sinon, stocker la dernière entrée de texte
    flow.set("lastInput2", msg.payload);
    return null; // Ne pas envoyer de message maintenant
}
