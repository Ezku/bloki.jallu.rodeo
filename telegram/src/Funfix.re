module Scheduler = {
  type t;
};

module Try = {
  type t('a);
};

module IO = {
  type t('a);
  [@bs.module "funfix"] [@bs.scope "IO"]
  external async : ((Scheduler.t, Try.t('a) => unit) => unit) => t('a) = "async";
};
