module Telegram = {
  type message = Js.t {. message_id : string, date : string};
};

module Telegraf = {
  type bot;
  type token;
  type context = Js.t {. updateType : string, message : Telegram.message};
  type middleware = context => unit;
  external bot : token => bot = "telegraf" [@@bs.module] [@@bs.new];
  external command : string => middleware => bot = "command" [@@bs.send.pipe : bot];
  external hears : Js.Re.t => middleware => bot = "hears" [@@bs.send.pipe : bot];
  external startPolling : bot = "startPolling" [@@bs.send.pipe : bot];
  external stop : bot = "stop" [@@bs.send.pipe : bot];
  external reply : string => unit = "reply" [@@bs.send.pipe : context];
};

external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN" [@@bs.val];

let hashtag = [%re "/#[^ ,.]+/"];

Telegraf.(
  bot apiToken |>
  hears hashtag @@ (
    fun context => {
      Js.log @@ "received: " ^ context##updateType ^ " at " ^ context##message##date;
      context |> reply @@ "#lol got " ^ context##updateType ^ " at " ^ context##message##date
    }
  ) |> startPolling
);