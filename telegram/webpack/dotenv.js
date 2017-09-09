const Dotenv = require("dotenv-webpack");

module.exports = function dotenvLoader() {
  return (context, { addPlugin }) => addPlugin(new Dotenv());
};
