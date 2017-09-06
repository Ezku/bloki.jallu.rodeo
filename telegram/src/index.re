Js.log "hello world";

external username : string = "process.env.TELEGRAM_USERNAME" [@@bs.val];

external apiToken : string = "process.env.TELEGRAM_API_TOKEN" [@@bs.val];

Js.log username;

Js.log apiToken;