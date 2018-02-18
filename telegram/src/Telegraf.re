type bot;

type token;

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
};

type middleware = Context.t => unit;

[@bs.module] [@bs.new] external bot : token => bot = "telegraf";

[@bs.send.pipe : bot] external command : (string, middleware) => bot = "command";

[@bs.send.pipe : bot] external hears : (Js.Re.t, middleware) => bot = "hears";

[@bs.send.pipe : bot] external startPolling : bot = "startPolling";

[@bs.send.pipe : bot] external stop : bot = "stop";

[@bs.send.pipe : Context.t] external reply : string => unit = "reply";
