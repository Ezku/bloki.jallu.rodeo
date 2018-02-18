module Client = {
  type t;
  module Options = {
    type url;
    type t = {. "url": url};
  };
  [@bs.module "redis"] external make : Options.t => t = "createClient";
  type key = string;
  type data = string;
  /* https://redis.io/commands/rpush */
  [@bs.send.pipe : t] external rpush : (key, data) => unit = "rpush";
};

module type CollectionType = {type t; let key: string;};

module List = (Collection: CollectionType) => {
  open Collection;
  let toString = (data: t) => Js.Json.stringifyAny(data) |> Js.Option.getWithDefault("");
  let push = (data: t) => Client.rpush(key, toString(data));
};

let connect = url => Client.make({"url": url});

[@bs.send.pipe : Client.t] external disconnect : unit = "quit";
