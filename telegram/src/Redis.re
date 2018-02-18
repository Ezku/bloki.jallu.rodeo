module Native = {
  module Options = {
    type url;
    type t = {. "url": url};
  };
  module Client = {
    type t;
    [@bs.module "redis"] external make : Options.t => t = "createClient";
    type key = string;
    type data = string;
    /* https://redis.io/commands/rpush */
    [@bs.send.pipe : t] external rpush : (key, data) => unit = "rpush";
  };
  module Event = {
    [@bs.deriving jsConverter]
    type t = [ | `ready | `error];
    type jsEventName = string;
    let make: t => jsEventName = tToJs;
    [@bs.send.pipe : Client.t] external on : (jsEventName, Js.Json.t => unit) => Client.t = "on";
  };
  module Events = {
    let ready = listener => Event.(on(make(`ready), (_) => listener()));
    let error = listener => Event.(on(make(`error), e => listener(e)));
  };
  module Ops = {
    let connect = url => Client.make({"url": url});
    [@bs.send.pipe : Client.t] external disconnect : unit = "quit";
  };
  include Ops;
};

module type CollectionType = {type t; let key: string; let toString: t => string;};

module List = (Collection: CollectionType) => {
  open Collection;
  let push = (data: t) => Native.Client.rpush(key, toString(data));
};

module Safe = {
  open Funfix;
  let connect = (url: Native.Options.url) : IO.t(Native.Client.t) =>
    IO.fromCallback((resolve, reject) =>
      Native.(connect(url) |> Events.ready(resolve) |> Events.error(reject))
    );
};

include Safe;
