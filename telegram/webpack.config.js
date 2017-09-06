const {
  createConfig,

  // Shorthand setters
  defineConstants,
  entryPoint,
  env,
  setOutput
} = require('webpack-blocks');

const path = require('path');

module.exports = createConfig([
  entryPoint('./lib/js/src/index.js'),
  setOutput('./build/app.js'),
  defineConstants({
    'process.env.NODE_ENV': process.env.NODE_ENV
  }),
  env('development', []),
  env('production', [])
]);
