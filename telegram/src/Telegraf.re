module Update = {
  type t = {
    .
    "update_id": int,
    "message": Telegram.Message.t,
    "reply_to_message": Js.nullable(Telegram.Message.t)
  };
};

module Context = {
  type t = {
    .
    "updateType": string,
    "update": Update.t
  };
  type middleware = t => unit;
};

module Bot = {
  type t;
  type token;
  [@bs.module] [@bs.new] external make : token => t = "telegraf";
  [@bs.send.pipe : t] external command : (string, Context.middleware) => t = "command";
  [@bs.send.pipe : t] external hears : (Js.Re.t, Context.middleware) => t = "hears";
  [@bs.send.pipe : t] external startPolling : t = "startPolling";
  [@bs.send.pipe : t] external stop : t = "stop";
  [@bs.send.pipe : Context.t] external reply : string => unit = "reply";
};
