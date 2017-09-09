module.exports = function bucklescriptLoader(options = { module: "es6" }) {
  return (context, { merge }) =>
    merge({
      resolve: {
        extensions: [".re", ".ml"]
      },
      module: {
        rules: [
          Object.assign(
            {
              test: /\.(re|ml)$/,
              use: {
                loader: "bs-loader",
                options: options
              }
            },
            context.match
          )
        ]
      }
    });
};
