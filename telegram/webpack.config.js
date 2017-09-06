const {
  createConfig,

  // Shorthand setters
  defineConstants,
  entryPoint,
  env,
  setOutput
} = require('webpack-blocks');

const path = require('path');

const dotenvLoader = require('./webpack/dotenv');

module.exports = createConfig([
  entryPoint('./lib/js/src/index.js'),
  setOutput('./build/app.js'),
  defineConstants({
    'process.env.NODE_ENV': process.env.NODE_ENV
  }),
  dotenvLoader(),
  env('development', []),
  env('production', [])
]);
