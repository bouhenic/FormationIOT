// Création d'un tableau pour stocker les messages de sortie
let messages = [];

// Ajouter chaque propriété comme un message distinct dans le tableau
messages.push({ payload: msg.payload.battery }); // Sortie 1
messages.push({ payload: msg.payload.soil_moisture }); // Sortie 2
messages.push({ payload: msg.payload.temperature }); // Sortie 3

// Renvoyer le tableau de messages
return [[messages[0]], [messages[1]], [messages[2]]];
