let hex = msg.payload;

// Construire le payload avec la valeur hex
msg.payload = { "color": { "hex": hex } };

// Retourner le message modifié
return msg;
