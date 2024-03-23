function decodeUplink(input){
return {
data: Decode(input.fport,input.bytes,input.variables)
};
}

function Decode(fPort,bytes){
var decoded = {};
var text = String.fromCharCode.apply(null,bytes);
decoded.text=text;
return decoded;
}
