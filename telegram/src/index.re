module Telegraf = {
  type bot;
  type token;
  type context;
  type middleware = context => unit;
  external bot : token => bot = "telegraf" [@@bs.module] [@@bs.new];
  external command : string => middleware => bot = "command" [@@bs.send.pipe : bot];
  external hears : Js.Re.t => middleware => bot = "hears" [@@bs.send.pipe : bot];
  external startPolling : unit = "startPolling" [@@bs.send.pipe : bot];
  external reply : string => unit = "reply" [@@bs.send.pipe : context];
};

external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN" [@@bs.val];

Telegraf.(
  bot apiToken |> command "start" @@ reply "#lol" |> hears [%re "/#lol/"] @@ reply "#lol" |> startPolling
);