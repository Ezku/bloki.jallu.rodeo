module Telegraf = {
  type bot;
  type token;
  type context;
  type middleware = context => unit;
  external bot : token => bot = "telegraf" [@@bs.module] [@@bs.new];
  external hears : string => middleware => bot = "hears" [@@bs.send.pipe : bot];
  external startPolling : unit = "startPolling" [@@bs.send.pipe : bot];
};

external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN" [@@bs.val];

Telegraf.(bot apiToken |> hears "#lol" (fun _context => Js.log "#lol") |> startPolling);