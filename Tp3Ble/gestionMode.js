let mode = null;
mode=msg.payload;
// Exemple pour stocker une valeur dans le contexte du flux
flow.set('mode', mode);

// Exemple pour récupérer une valeur du contexte du flux
let valeur = flow.get('mode');
if (valeur == false) { msg.payload = "AUTOMATIQUE"; }
else msg.payload="MANUEL";
return msg;
