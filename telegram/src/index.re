module Telegraf = {
  type bot;
  external bot : string => bot = "telegraf" [@@bs.module] [@@bs.new];
};

external apiToken : string = "process.env.TELEGRAM_API_TOKEN" [@@bs.val];

let bot = Telegraf.bot apiToken;

Js.log apiToken;