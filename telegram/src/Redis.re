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
    /* type t =
         | Ready;
       [@bs.send.pipe : Client.t] external on : (t, unit => unit) => Client.t = "on"; */
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
  /* open Funfix;
     let connect = (url: Native.Options.url) : IO.t(unit) => IO.async((_context, resolve) => {}); */
};

include Safe;
