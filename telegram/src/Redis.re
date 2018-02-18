module Client = {
  type t;
  module Options = {
    type url;
    type t = {. "url": url};
  };
  [@bs.module "redis"] external make : Options.t => t = "createClient";
};

let connect = url => Client.make({"url": url});

[@bs.send.pipe : Client.t] external disconnect : unit = "quit";
