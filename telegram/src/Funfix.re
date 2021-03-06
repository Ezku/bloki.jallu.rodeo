module Scheduler = {
  type t;
};

module Try = {
  type t('a);
  [@bs.module "funfix"] [@bs.scope "Try"] external success : 'a => t('a) = "success";
  [@bs.module "funfix"] [@bs.scope "Try"] external failure : Js.Exn.t => t('a) = "failure";
};

module IO = {
  type t('a);
  [@bs.module "funfix"] [@bs.scope "IO"]
  external async : ((Scheduler.t, Try.t('a) => unit) => 'b) => t('a) = "async";
  let fromCallback = f =>
    async((_, resolve) =>
      f((a: 'a) => resolve(Try.success(a)), (e: Js.Exn.t) => resolve(Try.failure(e)))
    );
};
