module.exports = function target(t) {
  return (context, { merge }) =>
    merge({
      target: t
    });
};
