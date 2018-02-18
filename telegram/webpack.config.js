const webpack = require("webpack");
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
} = require("webpack-blocks");
const nodeExternals = require("webpack-node-externals");

const path = require("path");

const target = require("./webpack/target");
const dotenvLoader = require("./webpack/dotenv");
const replaceModulePlugin = require("./webpack/replaceModulePlugin");
const bucklescriptLoader = require("./webpack/bucklescriptLoader");
const externals = require("./webpack/externals");

module.exports = createConfig([
  target("node"),
  babel(),
  replaceModulePlugin(/\/iconv-loader$/, "node-noop"),
  entryPoint("./src/index.re"),
  setOutput("./build/app.js"),
  match("*.re", { exclude: path.resolve("node_modules"), include: path.resolve("src") }, [
    bucklescriptLoader()
  ]),
  defineConstants({
    "process.env.NODE_ENV": process.env.NODE_ENV
  }),
  dotenvLoader(),
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
  env("production", [addPlugins([new webpack.LoaderOptionsPlugin({ minimize: true })])])
]);
