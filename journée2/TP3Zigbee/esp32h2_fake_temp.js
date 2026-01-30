const {temperature} = require('zigbee-herdsman-converters/lib/modernExtend');

const definition = {
  zigbeeModel: ['ESP32H2_FAKE_TEMP_V1'],
  model: 'ESP32H2_FAKE_TEMP',
  vendor: 'NewtonCIEL',
  description: 'ESP32-H2 fake temperature sensor (endpoint 10)',

  // IMPORTANT: ton capteur est sur endpoint 10
  endpoint: (device) => ({default: 10}),

  extend: [
    temperature(),
  ],

  meta: {},
};

module.exports = definition;
