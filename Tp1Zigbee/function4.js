// Vérifier si l'état du message reçu est "ON"
if (msg.payload.state == "ON") {
    // Renvoie true si l'état est "ON"
    return { payload: true };
} else {
    // Renvoie false dans tous les autres cas (y compris "OFF")
    return { payload: false};
}
