const {
  createConfig,

  // Shorthand setters
  defineConstants,
  entryPoint,
  env,
  setOutput
} = require('webpack-blocks');

const path = require('path');

const target = require('./webpack/target');
const dotenvLoader = require('./webpack/dotenv');
const replaceModulePlugin = require('./webpack/replaceModulePlugin');

module.exports = createConfig([
  target('node'),
  replaceModulePlugin(/\/iconv-loader$/, 'node-noop'),
  entryPoint('./lib/js/src/index.js'),
  setOutput('./build/app.js'),
  defineConstants({
    'process.env.NODE_ENV': process.env.NODE_ENV
  }),
  dotenvLoader(),
  env('development', []),
  env('production', [])
]);
