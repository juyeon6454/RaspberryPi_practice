nhn.deskhome_menu={_sServiceName:null,_sExtenstionType:null,_htEvent:{},_htElement:{},_htInitData:null,_htPage:{mail:"http://mail.naver.com",calendar:"http://calendar.naver.com",memo:"http://memo.naver.com",contact:"http://contact.naver.com",ndrive:"http://mybox.naver.com",office:"http://office.naver.com",moneybook:"http://moneybook.naver.com",keep:"http://${host.keep}"},initialize:function(a){this._sServiceName=a.sServiceName||"naverme";this._sExtenstionType=a.sExtenstionType||"";this._sUserId=a.sUserId;this._htInitData=a.htInitialData||{};this._setElement(a.elContainer);this._initElementAttr();if(jindo.$Element(this._htElement.header).hasClass("{=OPTION_CLASS}")){jindo.$Element(this._htElement.header).addClass("h_"+this._sServiceName+(this._sExtenstionType!=""?"_"+this._sExtenstionType:""))}this._attachEvent();if(this._sServiceName!="mail"){this._loadMailCount()}},_attachEvent:function(){this._htEvent.click=jindo.$Fn(this._onClick,this).attach(this._htElement.header,"click")},_onClick:function(d){var e=d.element;var c=jindo.$Element(e);var b="";var a="GNB.";if(c.hasClass("naver")){b=a+"naver"}else{if(c.hasClass("pwe_home")){b=a+this._sServiceName+"logo"}else{if(c.hasClass("mail")){b=a+"mail"}else{if(c.hasClass("calendar")){b=a+"calendar"}else{if(c.hasClass("memo")){b=a+"memo"}else{if(c.hasClass("contact")){b=a+"contact"}else{if(c.hasClass("ndrive")){b=a+"ndrive"}else{if(c.hasClass("office")){b=a+"office"}else{if(c.hasClass("moneybook")){b=a+"moneybook"}else{if(c.hasClass("keep")){b=a+"keep"}}}}}}}}}}if(b){clickcr(e,b,"","",d.$value())}},_detachEvent:function(){this._htEvent.click.detach(this._getElement("_root",true),"click")},destroy:function(){this._detachEvent();this._sServiceName=null;this._sServiceType=null;this._htElement=null;this._htInitData=null},_initElementAttr:function(){var a="";jindo.$Element(this._htElement.header_title).html(this._getServiceName());switch(this._sServiceName){case"mail":a="http://mail.naver.com";break;case"calendar":a="http://calendar.naver.com";break;case"memo":a="http://memo.naver.com";break;case"contact":a="http://contact.naver.com";break;case"ndrive":a="http://mybox.naver.com";break;case"office":a="http://office.naver.com";break;case"moneybook":a="http://moneybook.naver.com";break;case"keep":a="http://keep.naver.com";break}jindo.$Element(this._htElement.service_link).attr("href",a)},_setElement:function(a){this._htElement.header=jindo.$("header");this._htElement.menu_area=a||jindo.cssquery.getSingle(".gnb_area",jindo.$("header"));this._htElement.service_link=jindo.cssquery.getSingle("a._svc_lnk",this._htElement.header);this._htElement.header_title=jindo.cssquery.getSingle("span._header_tit",this._htElement.header);this._htElement.menu_list=jindo.cssquery.getSingle(".gnb_list_box",this._htElement.menu_area);this._htElement.mail=jindo.cssquery.getSingle("._mail",this._htElement.menu_list);this._htElement.new_mail=jindo.cssquery.getSingle(".article_num",this._htElement.mail);this._htElement.cnt_mail=jindo.cssquery.getSingle("._count",this._htElement.new_mail);this._htElement.calendar=jindo.cssquery.getSingle("._calendar",this._htElement.menu_list);this._htElement.memo=jindo.cssquery.getSingle("._memo",this._htElement.menu_list);this._htElement.contact=jindo.cssquery.getSingle("._contact",this._htElement.menu_list);this._htElement.ndrive=jindo.cssquery.getSingle("._ndrive",this._htElement.menu_list);this._htElement.office=jindo.cssquery.getSingle("._office",this._htElement.menu_list);this._htElement.moneybook=jindo.cssquery.getSingle("._moneybook",this._htElement.menu_list);this._htElement.keep=jindo.cssquery.getSingle("._keep",this._htElement.menu_list)},_getDomainInfo:function(){this._htInitData.htDomainInfo={DESK_URL:"http://desk.naver.com",CONTACT_IMAGE_URL:"http://img.contact.naver.com",CONTACT_URL:"http://contact.naver.com",MAIL_URL:"http://mail.naver.com",NDRIVE_URL:"http://mybox.naver.com",NAVER_OFFICE_VIEWR_URL:"http://word.office.naver.com",OFFICE_VIEWR_URL:"http://docviewer.office.naver.com",NPHOTO_URL:"http://nphoto.naver.com",WEBMSG_URL:"http://webmsg.naver.com",HELP_DESK_URL:"http://help.naver.com",PROFILE_POPUP_URL:"http://contact.naver.com/editMyAddressBook.nhn?addressNo=0&openedSupplement=true"}},getDomain:function(b){if(!this._htInitData||typeof this._htInitData.htDomainInfo=="undefined"){this._getDomainInfo();return false}if(!b||!this._htInitData.htDomainInfo[b]){return false}var a=this._htInitData.htDomainInfo[b];a=/^http:\/\//.test(a)?a:"http://"+a;return a},_setMailCount:function(a){if(this._sServiceName!=="mail"&&a&&a>0&&this._htElement.new_mail){this._htElement.new_mail.style.display="inline";this._htElement.cnt_mail.innerHTML=(a<100)?a:"99+"}else{if(a===0){this._htElement.new_mail.style.display="none"}}},_getServiceName:function(){var a="";switch(this._sServiceName){case"mail":a="메일";break;case"calendar":a="캘린더";break;case"memo":a="메모";break;case"contact":a="주소록";break;case"ndrive":a="MYBOX";break;case"office":a="오피스";break;case"moneybook":a="가계부";break;case"keep":a="KEEP";break}return a},getInfomationForPWE:function(){},setSkinType:function(a){},onResize:function(){},_loadMailCount:function(){var a="__mailCallBack"+new Date().getMilliseconds(),d="https://mail.naver.com/external/mailCount?svc=pnb&callback="+a,c=document.createElement("script"),b=this;c.type="text/javascript";c.src=d;c.id="_PNB_COUNT";window[a]=function(e){var g=(e||{COUNT:-1}).COUNT,f=document.getElementById("_PNB_COUNT");b._setMailCount(g);if(f){document.getElementsByTagName("head")[0].removeChild(f)}delete window[a]};document.getElementsByTagName("head")[0].appendChild(c)}};