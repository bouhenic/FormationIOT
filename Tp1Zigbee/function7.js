// Création d'un tableau pour stocker les messages de sortie
let messages = [];

// Ajouter chaque propriété comme un message distinct dans le tableau
messages.push({ payload: msg.payload.battery }); // Sortie 1
messages.push({ payload: msg.payload.irrigation_end_time }); // Sortie 2
messages.push({ payload: msg.payload.irrigation_start_time }); // Sortie 3
messages.push({ payload: msg.payload.irrigation_target }); // Sortie 4
messages.push({ payload: msg.payload.last_irrigation_duration }); // Sortie 5
messages.push({ payload: msg.payload.mode }); // Sortie 6
messages.push({ payload: msg.payload.state }); // Sortie 7
messages.push({ payload: msg.payload.water_consumed }); // Sortie 8

// Renvoyer le tableau de messages
return [[messages[0]], [messages[1]], [messages[2]], 
[messages[3]], [messages[4]], [messages[5]], [messages[6]], [messages[7]], [messages[8]], [messages[9]]];
