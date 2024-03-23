let humidityMsg = {payload: msg.payload.uplink_message.decoded_payload.humidity};
let temperatureMsg = {payload: msg.payload.uplink_message.decoded_payload.temperature};

return [humidityMsg, temperatureMsg];
