module Telegram = {
  /* https://core.telegram.org/bots/api#message */
  module Message = {
    type t = {
      .
      "message_id": string,
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
  type context = {
    .
    "updateType": string,
    "message": Telegram.Message.t
  };
  type middleware = context => unit;
  [@bs.module] [@bs.new] external bot : token => bot = "telegraf";
  [@bs.send.pipe : bot] external command : (string, middleware) => bot = "command";
  [@bs.send.pipe : bot] external hears : (Js.Re.t, middleware) => bot = "hears";
  [@bs.send.pipe : bot] external startPolling : bot = "startPolling";
  [@bs.send.pipe : bot] external stop : bot = "stop";
  [@bs.send.pipe : context] external reply : string => unit = "reply";
};

[@bs.val] external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN";

let hashtag = [%re "/#[^ ,.]+/"];

Telegraf.(
  bot(apiToken)
  |> hears(hashtag) @@
  (context => context |> reply @@ "Heard: " ++ Telegram.Message.format(context##message))
  |> startPolling
);
