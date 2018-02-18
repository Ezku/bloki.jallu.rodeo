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
  [@bs.send.pipe : t] external push : (key, data) => unit = "rpush";
};

let connect = url => Client.make({"url": url});

[@bs.send.pipe : Client.t] external disconnect : unit = "quit";
