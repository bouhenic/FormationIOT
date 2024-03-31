let state = null;
state=msg.payload;
// Exemple pour stocker une valeur dans le contexte du flux
flow.set('state', state);

// Exemple pour récupérer une valeur du contexte du flux
let valeur = flow.get('state');
if (valeur == true) { msg.payload = "ON"; }
else msg.payload="OFF";
return msg;
