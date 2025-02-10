function decodeUplink(input){
  var data = {}
  if (input.bytes.length === 4) {
  var humidity = (input.bytes[0] << 8) | input.bytes[1];
  var temperature = (input.bytes[2] << 8) | input.bytes[3];
  data.humidity = humidity / 100.0;
  data.temperature = (temperature / 100.0) - 100.0;
  }
return {  
  data: data,
  warnings: [],
  errors: []
};
}
