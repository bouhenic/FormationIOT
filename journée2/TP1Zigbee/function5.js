let lastInput = flow.get("lastInput") || ""; // Récupérer la dernière entrée stockée

if (msg.payload === "button_pressed") { // Identifier si le message provient du bouton
    let payload = lastInput;
    return { payload: payload };
} else { // Sinon, stocker la dernière entrée de texte
    flow.set("lastInput", msg.payload);
    return null; // Ne pas envoyer de message maintenant
}
