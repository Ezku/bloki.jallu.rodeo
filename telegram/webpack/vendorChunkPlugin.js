const { CommonsChunkPlugin } = require('webpack').optimize;

module.exports = function vendorChunkPlugin(vendorModuleName) {
  return (context, { addPlugin }) => addPlugin(
    new CommonsChunkPlugin({
      name: vendorModuleName,
      minChunks: function (module) {
        return module.context && module.context.indexOf(vendorModuleName) !== -1;
      }
    })
  );
};
