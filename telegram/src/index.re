[@bs.val] external apiToken : Telegraf.token = "process.env.TELEGRAM_API_TOKEN";

[@bs.val] external redisUrl : Redis.Client.Options.url = "process.env.REDIS_URL";

let hashtag = [%re "/#[^ ,.]+/"];

Redis.(connect(redisUrl) |> disconnect);

Telegraf.(
  bot(apiToken)
  |> hears(hashtag, context =>
       context |> reply @@ "Heard: " ++ Telegram.Message.format(context##update##message)
     )
  |> startPolling
);
