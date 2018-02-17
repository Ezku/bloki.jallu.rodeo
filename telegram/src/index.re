module Telegram = {
  /* https://core.telegram.org/bots/api#message */
  module Message = {
    type t = {
      .
      "message_id": int,
      "date": string,
      "from": {. "first_name": string},
      "text": string
    };
    let format = m : string => "[" ++ m##date ++ "] <" ++ m##from##first_name ++ "> " ++ m##text;
  };
};

module Telegraf = {
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
};

module Redis = {
  module Client = {
    type t;
  };
  module Options = {
    type t = {. "url": string};
  };
  [@bs.module "redis"] external createClient : Options.t => Client.t = "createClient";
};

[@bs.val] external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN";

let hashtag = [%re "/#[^ ,.]+/"];

Telegraf.(
  bot(apiToken)
  |> hears(hashtag, context =>
       context |> reply @@ "Heard: " ++ Telegram.Message.format(context##update##message)
     )
  |> startPolling
);
