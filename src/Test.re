module Http = {
  open Re;
  let space = rep(blank);
  let crlf = str("\r\n");
  let token = rep1 @@ compl([rg('\000', '\031'), set("\127)(<>@,;:\\/[]?={}")]);
  let meth = token;
  let version = {
    let digits = rep1(digit);
    let decimal = seq([digits, opt(seq([char('.'), digits]))]);
    seq([str("HTTP/"), decimal]);
  };
  let uri = rep1(compl([char('\n')]));
  let request_line = [space, group(meth), space, group(uri), group(version), space] |> seq;
  let header = {
    let key = group(rep1(Re.compl([char(':')])));
    let value = group(rep1(Re.compl([char('\n')])));
    seq([space, key, space, char(':'), space, value, space, crlf]);
  };
  let request' = seq([request_line, crlf, rep(header), crlf]);
  module Export = {
    let request = request';
    let request_g = request' |> no_group;
    let requests = request' |> rep1;
    let requests_g = request' |> no_group |> rep1;
  };
};
let sample_txt = {js|"GET / HTTP/1.1
Host: www.reddit.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive

GET /reddit.v_EZwRzV-Ns.css HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/css,*/*;q=0.1
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /reddit-init.en-us.O1zuMqOOQvY.js HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /reddit.en-us.31yAfSoTsfo.js HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /kill.png HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /icon.png HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive

GET /favicon.ico HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive

GET /AMZM4CWd6zstSC8y.jpg HTTP/1.1
Host: b.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /jz1d5Nm0w97-YyNm.jpg HTTP/1.1
Host: b.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /aWGO99I6yOcNUKXB.jpg HTTP/1.1
Host: a.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /rZ_rD5TjrJM0E9Aj.css HTTP/1.1
Host: e.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/css,*/*;q=0.1
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /tmsPwagFzyTvrGRx.jpg HTTP/1.1
Host: a.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /KYgUaLvXCK3TCEJx.jpg HTTP/1.1
Host: a.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /81pzxT5x2ozuEaxX.jpg HTTP/1.1
Host: e.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /MFqCUiUVPO5V8t6x.jpg HTTP/1.1
Host: a.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /TFpYTiAO5aEowokv.jpg HTTP/1.1
Host: e.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /eMWMpmm9APNeNqcF.jpg HTTP/1.1
Host: e.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /S-IpsJrOKuaK9GZ8.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /3V6dj9PDsNnheDXn.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /wQ3-VmNXhv8sg4SJ.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /ixd1C1njpczEWC22.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /nGsQj15VyOHMwmq8.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /zT4yQmDxQLbIxK1b.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /L5e1HcZLv1iu4nrG.jpg HTTP/1.1
Host: f.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /WJFFPxD8X4JO_lIG.jpg HTTP/1.1
Host: f.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /hVMVTDdjuY3bQox5.jpg HTTP/1.1
Host: f.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /rnWf8CjBcyPQs5y_.jpg HTTP/1.1
Host: f.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /gZJL1jNylKbGV4d-.jpg HTTP/1.1
Host: d.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /aNd2zNRLXiMnKUFh.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /droparrowgray.gif HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.redditstatic.com/reddit.v_EZwRzV-Ns.css

GET /sprite-reddit.an0Lnf61Ap4.png HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.redditstatic.com/reddit.v_EZwRzV-Ns.css

GET /ga.js HTTP/1.1
Host: www.google-analytics.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/
If-Modified-Since: Tue, 29 Oct 2013 19:33:51 GMT

GET /reddit/ads.html?sr=-reddit.com&bust2 HTTP/1.1
Host: static.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /pixel/of_destiny.png?v=hOlmDALJCWWdjzfBV4ZxJPmrdCLWB%2Ftq7Z%2Ffp4Q%2FxXbVPPREuMJMVGzKraTuhhNWxCCwi6yFEZg%3D&r=783333388 HTTP/1.1
Host: pixel.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /UNcO-h_QcS9PD-Gn.jpg HTTP/1.1
Host: c.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://e.thumbs.redditmedia.com/rZ_rD5TjrJM0E9Aj.css

GET /welcome-lines.png HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.redditstatic.com/reddit.v_EZwRzV-Ns.css

GET /welcome-upvote.png HTTP/1.1
Host: www.redditstatic.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.redditstatic.com/reddit.v_EZwRzV-Ns.css

GET /__utm.gif?utmwv=5.5.1&utms=1&utmn=720496082&utmhn=www.reddit.com&utme=8(site*srpath*usertype*uitype)9(%20reddit.com*%20reddit.com-GET_listing*guest*web)11(3!2)&utmcs=UTF-8&utmsr=2560x1600&utmvp=1288x792&utmsc=24-bit&utmul=en-us&utmje=1&utmfl=13.0%20r0&utmdt=reddit%3A%20the%20front%20page%20of%20the%20internet&utmhid=2129416330&utmr=-&utmp=%2F&utmht=1400862512705&utmac=UA-12131688-1&utmcc=__utma%3D55650728.585571751.1400862513.1400862513.1400862513.1%3B%2B__utmz%3D55650728.1400862513.1.1.utmcsr%3D(direct)%7Cutmccn%3D(direct)%7Cutmcmd%3D(none)%3B&utmu=qR~ HTTP/1.1
Host: www.google-analytics.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /ImnpOQhbXUPkwceN.png HTTP/1.1
Host: a.thumbs.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /ajax/libs/jquery/1.7.1/jquery.min.js HTTP/1.1
Host: ajax.googleapis.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /__utm.gif?utmwv=5.5.1&utms=2&utmn=1493472678&utmhn=www.reddit.com&utmt=event&utme=5(AdBlock*enabled*false)(0)8(site*srpath*usertype*uitype)9(%20reddit.com*%20reddit.com-GET_listing*guest*web)11(3!2)&utmcs=UTF-8&utmsr=2560x1600&utmvp=1288x792&utmsc=24-bit&utmul=en-us&utmje=1&utmfl=13.0%20r0&utmdt=reddit%3A%20the%20front%20page%20of%20the%20internet&utmhid=2129416330&utmr=-&utmp=%2F&utmht=1400862512708&utmac=UA-12131688-1&utmni=1&utmcc=__utma%3D55650728.585571751.1400862513.1400862513.1400862513.1%3B%2B__utmz%3D55650728.1400862513.1.1.utmcsr%3D(direct)%7Cutmccn%3D(direct)%7Cutmcmd%3D(none)%3B&utmu=6R~ HTTP/1.1
Host: www.google-analytics.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /ados.js?q=43 HTTP/1.1
Host: secure.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /fetch-trackers?callback=jQuery111005268222517967478_1400862512407&ids%5B%5D=t3_25jzeq-t8_k2ii&_=1400862512408 HTTP/1.1
Host: tracker.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /ados?t=1400862512892&request={%22Placements%22:[{%22A%22:5146,%22S%22:24950,%22D%22:%22main%22,%22AT%22:5},{%22A%22:5146,%22S%22:24950,%22D%22:%22sponsorship%22,%22AT%22:8}],%22Keywords%22:%22-reddit.com%22,%22Referrer%22:%22http%3A%2F%2Fwww.reddit.com%2F%22,%22IsAsync%22:true,%22WriteResults%22:true} HTTP/1.1
Host: engine.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /pixel/of_doom.png?id=t3_25jzeq-t8_k2ii&hash=da31d967485cdbd459ce1e9a5dde279fef7fc381&r=1738649500 HTTP/1.1
Host: pixel.redditmedia.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /Extensions/adFeedback.js HTTP/1.1
Host: static.adzrk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: */*
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /Extensions/adFeedback.css HTTP/1.1
Host: static.adzrk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/css,*/*;q=0.1
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /reddit/ads-load.html?bust2 HTTP/1.1
Host: static.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://www.reddit.com/

GET /Advertisers/a774d7d6148046efa89403a8db635a81.jpg HTTP/1.1
Host: static.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /i.gif?e=eyJhdiI6NjIzNTcsImF0Ijo1LCJjbSI6MTE2MzUxLCJjaCI6Nzk4NCwiY3IiOjMzNzAxNSwiZGkiOiI4NmI2Y2UzYWM5NDM0MjhkOTk2ZTg4MjYwZDE5ZTE1YyIsImRtIjoxLCJmYyI6NDE2MTI4LCJmbCI6MjEwNDY0LCJrdyI6Ii1yZWRkaXQuY29tIiwibWsiOiItcmVkZGl0LmNvbSIsIm53Ijo1MTQ2LCJwYyI6MCwicHIiOjIwMzYyLCJydCI6MSwicmYiOiJodHRwOi8vd3d3LnJlZGRpdC5jb20vIiwic3QiOjI0OTUwLCJ1ayI6InVlMS01ZWIwOGFlZWQ5YTc0MDFjOTE5NWNiOTMzZWI3Yzk2NiIsInRzIjoxNDAwODYyNTkzNjQ1fQ&s=lwlbFf2Uywt7zVBFRj_qXXu7msY HTTP/1.1
Host: engine.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2
Cookie: azk=ue1-5eb08aeed9a7401c9195cb933eb7c966

GET /BurstingPipe/adServer.bs?cn=tf&c=19&mc=imp&pli=9994987&PluID=0&ord=1400862593644&rtu=-1 HTTP/1.1
Host: bs.serving-sys.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads.html?sr=-reddit.com&bust2

GET /Advertisers/63cfd0044ffd49c0a71a6626f7a1d8f0.jpg HTTP/1.1
Host: static.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads-load.html?bust2

GET /BurstingPipe/adServer.bs?cn=tf&c=19&mc=imp&pli=9962555&PluID=0&ord=1400862593645&rtu=-1 HTTP/1.1
Host: bs.serving-sys.com
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads-load.html?bust2
Cookie: S_9994987=6754579095859875029; A4=01fmFvgRnI09SF00000; u2=d1263d39-874b-4a89-86cd-a2ab0860ed4e3Zl040

GET /i.gif?e=eyJhdiI6NjIzNTcsImF0Ijo4LCJjbSI6MTE2MzUxLCJjaCI6Nzk4NCwiY3IiOjMzNzAxOCwiZGkiOiI3OTdlZjU3OWQ5NjE0ODdiODYyMGMyMGJkOTE4YzNiMSIsImRtIjoxLCJmYyI6NDE2MTMxLCJmbCI6MjEwNDY0LCJrdyI6Ii1yZWRkaXQuY29tIiwibWsiOiItcmVkZGl0LmNvbSIsIm53Ijo1MTQ2LCJwYyI6MCwicHIiOjIwMzYyLCJydCI6MSwicmYiOiJodHRwOi8vd3d3LnJlZGRpdC5jb20vIiwic3QiOjI0OTUwLCJ1ayI6InVlMS01ZWIwOGFlZWQ5YTc0MDFjOTE5NWNiOTMzZWI3Yzk2NiIsInRzIjoxNDAwODYyNTkzNjQ2fQ&s=OjzxzXAgQksbdQOHNm-bjZcnZPA HTTP/1.1
Host: engine.adzerk.net
User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10.8; rv:15.0) Gecko/20100101 Firefox/15.0.1
Accept: image/png,image/*;q=0.8,*/*;q=0.5
Accept-Language: en-us,en;q=0.5
Accept-Encoding: gzip, deflate
Connection: keep-alive
Referer: http://static.adzerk.net/reddit/ads-load.html?bust2
Cookie: azk=ue1-5eb08aeed9a7401c9195cb933eb7c966

GET /subscribe?host_int=1042356184&ns_map=571794054_374233948806,464381511_13349283399&user_id=245722467&nid=1399334269710011966&ts=1400862514 HTTP/1.1
Host: notify8.dropbox.com
Accept-Encoding: identity
Connection: keep-alive
X-Dropbox-Locale: en_US
User-Agent: DropboxDesktopClient/2.7.54 (Macintosh; 10.8; ('i32',); en_US)

"|js};
// let http_requests = Util.readInput("benchmarks/http-requests.txt");

let str_20_zeroes = String.make(20, '0');
Js.log(str_20_zeroes)
let re_20_zeroes = Re.(str(str_20_zeroes));

// let tex_ignore_re =
//   "benchmarks/tex.gitignore"
//   |> Util.readInput
//   |> List.map(
//        ~f=
//          (s) =>
//            switch (String.lsplit2(s, ~on='#')) {
//            | Some((pattern, _comment)) => pattern
//            | None => s
//            }
//      )
//   |> List.filter_map(
//        ~f=
//          (s) =>
//            switch (String.strip(s)) {
//            | "" => None
//            | s => Some(s)
//            }
//      )
//   |> List.map(~f=Re.Glob.glob)
//   |> Re.alt;

// let tex_ignore_filesnames = Util.read_lines("benchmarks/files");

// let lots_of_a's =
//   String.init(
//     101,
//     ~f=
//       fun
//       | 100 => 'b'
//       | _ => 'a'
//   );

let lots_o_a's_re = Re.(seq([char('a'), opt(char('a')), char('b')]));

let media_type_re = {
  let re = Re.Emacs.re(~case=true, "[ \t]*\\([^ \t;]+\\)");
  Re.(seq([start, re]));
};

/* Taken from https://github.com/rgrinberg/ocaml-uri/blob/903ef1010f9808d6f3f6d9c1fe4b4eabbd76082d/lib/uri.ml*/
let uri_reference = Re.Posix.re("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?");

let uris = [
  "https://google.com",
  "http://yahoo.com/xxx/yyy?query=param&one=two",
  "file:/random_crap"
];

// let benchmarks = [
//   ("20 zeroes", re_20_zeroes, [str_20_zeroes]),
//   ("lots of a's", lots_o_a's_re, [lots_of_a's]),
//   ("media type match", media_type_re, [" foo/bar ; charset=UTF-8"]),
//   ("uri", uri_reference, uris)
// ];

// let exec_bench = (exec, name, re: Re.t, cases) => {
//   let re = Re.compile(re);
//   Bench.Test.create_group(
//     ~name,
//     List.mapi(
//       cases,
//       ~f=
//         (i, case) => {
//           let name = sprintf("case %i", i);
//           Bench.Test.create(~name, () => ignore(exec(re, case)));
//         }
//     )
//   );
// };

// let exec_bench_many = (exec, name, re, cases) => {
//   let re = Re.compile(re);
//   Bench.Test.create(~name, () => cases |> List.iter(~f=(x) => ignore(exec(re, x))));
// };

let rec read_all_http = (pos, re, reqs) =>
  if (pos >= String.length(reqs)) {
    ();
  } else {
    let g = Re.exec(~pos, re, reqs);
    let (_, pos) = Re.Group.offset(g, 0);
    read_all_http(pos + 1, re, reqs);
  };

let rec drain_gen = (gen) =>
  switch (gen()) {
  | Seq.Nil => ()
  | [@implicit_arity] Cons(_, tail) => drain_gen(tail)
  };

// let benchmarks = {
//   let benches =
//     benchmarks
//     |> List.map(
//          ~f=
//            ((name, re, cases)) =>
//              Bench.Test.create_group(
//                ~name,
//                [
//                  exec_bench(Re.exec, "exec", re, cases),
//                  exec_bench(Re.execp, "execp", re, cases),
//                  exec_bench(Re.exec_opt, "exec_opt", re, cases)
//                ]
//              )
//        );
//   let http_benches = {
//     open Bench;
//     open Http.Export;
//     let manual =
//       [(request, "no group"), (request_g, "group")]
//       |> List.map(
//            ~f=
//              ((re, name)) => {
//                let re = Re.compile(re);
//                Test.create(~name, () => read_all_http(0, re, http_requests));
//              }
//          )
//       |> Test.create_group(~name="manual");
//     let many = {
//       let requests = Re.compile(requests);
//       let requests_g = Re.compile(requests_g);
//       [
//         Test.create(~name="execp no group", () => ignore(Re.execp(requests, http_requests))),
//         Test.create(
//           ~name="all_gen group",
//           () => http_requests |> Re.Seq.all(requests_g) |> drain_gen
//         )
//       ]
//       |> Test.create_group(~name="auto");
//     };
//     Test.create_group(~name="http", [manual, many]);
//   };
//   benches
//   @ [
//     [exec_bench_many(Re.execp, "execp"), exec_bench_many(Re.exec_opt, "exec_opt")]
//     |> List.map(~f=(f) => f(tex_ignore_re, tex_ignore_filesnames))
//     |> Bench.Test.create_group(~name="tex gitignore")
//   ]
//   @ [http_benches];
// };

// let () = Command.run(Bench.make_command(benchmarks));
