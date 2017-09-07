const webpack = require('webpack');
const {
  createConfig,

  // Feature blocks
  babel,
  uglify,
  addPlugins,

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
  babel(),
  replaceModulePlugin(/\/iconv-loader$/, 'node-noop'),
  entryPoint('./lib/es6/src/index.js'),
  setOutput('./build/app.js'),
  defineConstants({
    'process.env.NODE_ENV': process.env.NODE_ENV
  }),
  dotenvLoader(),
  env('development', []),
  env('production', [
    uglify({
      uglifyOptions: {
        mangle: false,
        compress: {
          dead_code: true,
          evaluate: true,
          unused: true,
          toplevel: true
        },
        output: {
          comments: false,
          beautify: true
        }
      }
    }),
    addPlugins([
      new webpack.LoaderOptionsPlugin({ minimize: true })
    ])
  ])
]);
