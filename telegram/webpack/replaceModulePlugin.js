const { NormalModuleReplacementPlugin } = require("webpack");

module.exports = function replaceModulePlugin(pattern, moduleName) {
  return (context, { addPlugin }) =>
    addPlugin(new NormalModuleReplacementPlugin(pattern, moduleName));
};
