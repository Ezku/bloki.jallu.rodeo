[@bs.val] external apiToken : Telegraf.Bot.token = "process.env.TELEGRAM_API_TOKEN";

[@bs.val] external redisUrl : Redis.Native.Options.url = "process.env.REDIS_URL";

let hashtag = [%re "/#[^ ,.]+/"];

module MessageCollectionType = {
  type t = Telegram.Message.t;
  let key = "messages";
  let toString = (data: t) => Js.Json.stringifyAny(data) |> Js.Option.getWithDefault("");
};

module Messages = Redis.List(MessageCollectionType);

let save = message => {
  open Redis.Native;
  let client = connect(redisUrl);
  client |> Messages.push(message);
  client |> disconnect;
};

Telegraf.Bot.(
  make(apiToken)
  |> hears(
       hashtag,
       context => {
         save(context##update##message);
         context |> reply @@ "Heard: " ++ Telegram.Message.format(context##update##message);
       }
     )
  |> startPolling
);
