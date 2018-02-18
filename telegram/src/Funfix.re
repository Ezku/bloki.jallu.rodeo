module Scheduler = {
  type t;
};

module Try = {
  type error = Js.Json.t;
  type t('a) =
    | Success('a)
    | Failure(error);
  [@bs.module "funfix"] [@bs.scope "Try"] external success : 'a => t('a) = "success";
  [@bs.module "funfix"] [@bs.scope "Try"] external failure : error => t('a) = "failure";
};

module IO = {
  type t('a);
  [@bs.module "funfix"] [@bs.scope "IO"]
  external async : ((Scheduler.t, Try.t('a) => unit) => 'b) => t('a) = "async";
  let fromCallback = f =>
    async((_, resolve) =>
      f((a: 'a) => resolve(Try.success(a)), (e: Try.error) => resolve(Try.failure(e)))
    );
};
