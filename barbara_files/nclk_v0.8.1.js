!function(e){var t=function(e,t,n,o,l,r,c){i(e,t,n,o,r,c)},n=e.ccsrv||"cc.naver.com",o=e.nsc||"decide.me",l={},r=e.g_allowedOrigin||"",c={};function i(e,n,o,l,r,c){var i,d,a,u=e,s=e;if("nodeType"in e&&e.nodeType>=1)u=window.event||e;else if(e){var f=e.srcElement||e.currentTarget||e.target;f&&(s=t.findLink(f))}return r||(r=""),a=t.gcp(s,u),d=t.gl(n,o,l,a,"",0,t.st,r,c),i=t.l(s,d),t.sd(i),!0}t.vs="0.8.1",t.md="cc",t.pt="https:",t.ec=encodeURIComponent,t.st=1,t.ua={},self!==parent&&r&&(parent.postMessage("getLCSInfo",r),window.addEventListener("message",(function(e){e.origin===r&&(c=JSON.parse(e.data))}),!1)),function(){try{if("undefined"==typeof navigator||!navigator||!navigator.userAgentData)return!1;var e=navigator.userAgentData,n=e.uaList||e.brands,o=["architecture","model","platform","platformVersion","uaFullVersion","fullVersionList"],l=function(e,t){return Object.prototype.toString.call(e).slice(8,-1).toLowerCase()===t.toLowerCase()},r=function(e,n){if(n=n?n+"_":"",l(e,"array"))for(var o=0,r=e.length;o<r;o++)if(l(e[o],"object"))for(var c in e[o])t.ua[n+c+"_"+o]=e[o][c]||""};t.ua.mobile=e.mobile,r(n),navigator.userAgentData.getHighEntropyValues(o).then((function(e){for(var n in o){var l=o[n];"fullVersionList"==l?r(e[l],"full"):t.ua[l]=e[l]||""}}))}catch(e){console.warn(e)}}(),t.findLink=function(e){for(var t=e;t&&"BODY"!==t.tagName&&"HTML"!==t.tagName&&"A"!==t.tagName&&t.parentNode;)t=t.parentNode;return"A"!==t.tagName&&(t=e),t},t.l=function(e,o){var l,r,c;return e&&e.href&&e.getAttribute("href")?(r=e.tagName.toLowerCase(),(c=e.href.toLowerCase())&&0==c.indexOf(t.pt+"//"+n)?l=e.href:c&&0!=c.indexOf(t.pt+"//"+n)&&r&&"img"!=r&&(l=o+"&u="+t.ec(e.href)),l):o+"&u=about%3Ablank"},t.sendByBeacon=function(e){var t=e.split("?");navigator.sendBeacon(t[0],t[1])},t.sendByImage=function(e){var t=(new Date).getTime();(new Image).src=e+"&nt="+t},t.sd=navigator.sendBeacon?t.sendByBeacon:t.sendByImage,t.ggv=function(t){return l[t]||e[t]||""},t.gl=function(l,r,i,d,a,u,s,f,m){var g=t.ggv("g_ssc"),p=t.ggv("g_query"),v=t.ggv("g_pid"),y=t.ggv("g_sid"),w=t.ggv("g_lcsurl")||c.g_lcsurl||window.location.href,h=t.ggv("g_lcssti")||c.g_lcssti||null,_=e.lcs_get_lpid||c.lcs_get_lpid||null;null==u&&(u=1),null==s&&(s=1);var b,L,E=t.pt+"//"+n+"/"+t.md+"?a="+l+"&r="+i+"&i="+r+"&m="+u;for(b in 1==s?(g&&(E+="&ssc="+g),p&&(E+="&q="+t.ec(p)),y&&(E+="&s="+y),m?E+="&p="+m:v?E+="&p="+v:_?E+="&p="+("function"==typeof _?_():_):console.warn("'g_pid / lcs_get_lpid' is not exist.")):(E+="&nsc="+o,console.warn("[DEPRECATED] NSC mode")),f&&(E+="&g="+f),a&&(E+="&u="+t.ec(a)),w&&(E+="&lcsurl="+t.ec(w)),h&&(E+="&lcssti="+h),d&&(E+=d),t.ua)(L=t.ua[b])&&(E+="&ua_"+b+"="+t.ec(L));return E},t.al=function(e,t){var n=window;n.addEventListener?n.addEventListener(e,t,!1):n.attachEvent&&n.attachEvent("on"+e,t)},t.gsbw=function(){var e=document.createElement("p");e.style.width="200px",e.style.height="200px";var t=document.createElement("div");t.style.position="absolute",t.style.top="0px",t.style.left="0px",t.style.visibility="hidden",t.style.width="200px",t.style.height="150px",t.style.overflow="hidden",t.appendChild(e),document.body.appendChild(t);var n=e.offsetWidth;t.style.overflow="scroll";var o=e.offsetWidth;return n==o&&(o=t.clientWidth),document.body.removeChild(t),n-o},t.fp=function(e){var t=curtop=0;try{if(e.offsetParent)do{t+=e.offsetLeft,curtop+=e.offsetTop}while(e=e.offsetParent);else(e.x||e.y)&&(e.x&&(t+=e.x),e.y&&(curtop+=e.y))}catch(e){}return[t,curtop]},t.ws=function(e){e||(e=window);var n=0;if(e.innerWidth){if(n=e.innerWidth,"number"==typeof e.innerWidth){var o=t.gsbw();n=e.innerWidth-o}}else document.documentElement&&document.documentElement.clientWidth?n=document.documentElement.clientWidth:document.body&&(document.body.clientWidth||document.body.clientHeight)&&(n=document.body.clientWidth);return n},t.ci=function(e){document.URL;var t,n=e.parentNode;if(null==n||null==n)return!1;for(;;)if("#document"==n.nodeName.toLowerCase()){t=n.parentWindow?n.parentWindow:n.defaultView;try{return null!=t.frameElement&&null!=t.frameElement&&"iframe"==t.frameElement.nodeName.toLowerCase()&&t.frameElement.id||!1}catch(e){return!1}}else if(null==(n=n.parentNode)||null==n)return!1},t.gcp=function(e,n){var o,l,r,c=-1,i=-1,d=-1,a=-1,u="",s=window.event?window.event:e;n&&(s=n||window.event);try{if(bw=t.ws(window),r=t.ci(e)){var f=t.fp(document.getElementById(r));s.clientX&&null!=s.clientX&&((o=document.body).clientLeft&&o.clientTop?(ifrSx=s.clientX-o.clientLeft,ifrSy=s.clientY-o.clientTop):(ifrSx=s.clientX,ifrSy=s.clientY)),d=f[0]+ifrSx,a=f[1]+ifrSy,document.body&&(document.body.scrollTop||document.body.scrollLeft)?(c=d-(o=document.body).scrollLeft,i=a-o.scrollTop):document.documentElement&&(document.documentElement.scrollTop||document.documentElement.scrollLeft)?(c=d-(l=document.documentElement).scrollLeft,i=a-l.scrollTop):(c=d,i=a)}else s.clientX&&null!=s.clientX&&((o=document.body).clientLeft&&o.clientTop?(c=s.clientX-o.clientLeft,i=s.clientY-o.clientTop):(c=s.clientX,i=s.clientY)),document.body&&(document.body.scrollTop||document.body.scrollLeft)?(d=document.body.scrollLeft+(c<0?0:c),a=document.body.scrollTop+(i<0?0:i)):document.documentElement&&(document.documentElement.scrollTop||document.documentElement.scrollLeft)?(null!=(l=document.documentElement).scrollLeft&&(d=l.scrollLeft+(c<0?0:c)),null!=l.scrollTop&&(a=l.scrollTop+(i<0?0:i))):(d=c<0?0:c,a=i<0?0:i),s.pageX&&(d=s.pageX),s.pageY&&(a=s.pageY)}catch(n){}return-1!=d&&-1!=a&&(u+="&px="+d+"&py="+a),-1!=c&&-1!=i&&(u+="&sx="+c+"&sy="+i),u},e.nclk_proxy=function(n,o,l,r,c,i){var d=e.g_nclk_proxy||"";return d&&n.href&&(n.href=d+t.ec(n.href)),t(n,o,l,r,0,i)},e.nclk=t,e.nclk_v2=i,e.nclk_v2_with_obj=function(e){var t=e||{};t.e&&t.a&&(l.g_ssc=t.g_ssc||"",l.g_query=t.g_query||"",l.g_sid=t.g_sid||"",l.g_pid=t.g_pid||"",l.g_lcsurl=t.g_lcsurl||"",l.g_lcssti=t.g_lcssti||"",i(t.e,t.a,t.i,t.r,t.g,t.pid),l={})}}(window);