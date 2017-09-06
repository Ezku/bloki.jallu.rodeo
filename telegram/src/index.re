module Telegraf = {
  type bot;
  type token;
  external bot : token => bot = "telegraf" [@@bs.module] [@@bs.new];
};

external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN" [@@bs.val];

let bot = Telegraf.bot apiToken;

Js.log apiToken;