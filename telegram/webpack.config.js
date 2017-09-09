const webpack = require('webpack');
const {
  createConfig,
  match,

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
const bucklescriptLoader = require('./webpack/bucklescriptLoader');
const vendorChunkPlugin = require('./webpack/vendorChunkPlugin');
const manifestPlugin = require('./webpack/manifestPlugin');

module.exports = createConfig([
  target('node'),
  babel(),
  replaceModulePlugin(/\/iconv-loader$/, 'node-noop'),
  entryPoint('./src/index.re'),
  setOutput('./build/app.[name].js'),
  match("*.re", { exclude: path.resolve('node_modules'), include: path.resolve('src') }, [
    bucklescriptLoader()
  ]),
  defineConstants({
    'process.env.NODE_ENV': process.env.NODE_ENV
  }),
  dotenvLoader(),
  env('development', [
    vendorChunkPlugin("node_modules"),
    manifestPlugin("app")
  ]),
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
