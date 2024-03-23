function decodeUplink{
return {
data: Decode(input.fport,input.bytes,input.variables)
};
}

function Decode(fPort,bytes){
var decoded = {};
var text = String.fromCharCode.apply(null,bbytes);
decoded.text=text;
return decoded;
}
