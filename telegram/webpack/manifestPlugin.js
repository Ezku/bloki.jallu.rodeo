const { CommonsChunkPlugin } = require("webpack").optimize;

module.exports = function manifestPlugin(manifestName = "manifest") {
  return (context, { addPlugin }) =>
    addPlugin(
      new CommonsChunkPlugin({
        filename: `${manifestName}.js`,
        name: manifestName,
        minChunks: Infinity
      })
    );
};
