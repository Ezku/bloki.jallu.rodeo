const { IgnorePlugin } = require("webpack");

module.exports = function ignorePlugin(pattern) {
  return (context, { addPlugin }) => addPlugin(new IgnorePlugin(pattern));
};
