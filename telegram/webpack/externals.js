module.exports = function externals(e) {
  return (context, { merge }) =>
    merge({
      externals: e
    });
};
