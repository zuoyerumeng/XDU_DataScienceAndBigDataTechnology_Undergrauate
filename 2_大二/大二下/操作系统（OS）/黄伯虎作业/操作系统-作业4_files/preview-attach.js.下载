$(document).ready(function() {
	var noDownLoadPath = window.ATTACH__NO_DOWNLOAD_PATH;
	$(".attachNew").each(function(index, element) {
        var element = $(this).children("span:first");
        var objectId = $(element).attr("data");
		//var fileOriName = $(element).text();
		//fileOriName = encodeURIComponent(fileOriName);
		var url = "/ueditorupload/read?objectId=" + objectId;
		if(noDownLoadPath && noDownLoadPath.length > 0){
			url = url.replace('/ueditorupload/read',noDownLoadPath);
		}
		url = encodeURI(url);
		/*
		$(element).parent().click(function() {
			window.open(url, '_blank').location;
		});
		*/
		bindAttachOpenEvent($(element).parent(),url);
	});
	delete window.ATTACH__NO_DOWNLOAD_PATH;
    $(".attachNew img").unbind("click")
	$(".attachUrl span").each(function(index, element) {
		var url = $(this).attr("data");
		url = encodeURI(url);
		/*
		$(this).parent().click(function() {
			window.open(url, '_blank').location;
		});*/
		bindAttachOpenEvent($(this).parent(),url);
	});

	$(".attachZT span").each(function(index, element) {
		var url = $(this).attr("data");
		url = encodeURI(url);
//		$(this).parent().click(function() {
//			window.open(url, '_blank').location;
//		});
		bindAttachOpenEvent($(this).parent(),url);
	});
	
	$(".attach a").each(function(index, element) {
		var url = $(this).attr("href");
		url = encodeURI(url);
		$(this).attr("href", url);
		/*
		$(this).click(function(event) {
			event.preventDefault() ;
			window.open(url, '_blank').location;
		});
		*/
		bindAttachOpenEvent($(this),url);
	});
	

  function bindAttachOpenEvent(element,url){
		$(element).click(function(event) {
			event.preventDefault();
			if(checkAttachIframeOpen(url)){
			  return;
			}
			window.open(url, '_blank').location;
		});
  }
  
  
  function checkAttachIframeOpen(url) {
		try{
			if (window.frameElement && typeof(window.parent.Attach_IframeOpen) == 'function') {
				window.parent.Attach_IframeOpen(url);
				return true;
			}
		}catch (err) {}
		return false;
	}


	window.addEventListener("message", function (event) {
		if (undefined == event) {
			return;
		}
		var data = event.data;
		if (undefined == data) {
			return;
		}
		var type = data.type;
		if (undefined == type || type != "attach") {
			return;
		}
		var name = data.name;
		if (undefined == name) {
			return;
		}
		var content = decodeURIComponent(atob(name));
		var obj = JSON.parse(content);
		var objectid = obj.objectid;
		var dataName = obj.name;
		try{
			dataName = encodeURIComponent(dataName);
		}catch(err){}
		var url = "/ueditorupload/read?objectId=" + objectid + "&fileOriName=" + dataName;
		if (noDownLoadPath && noDownLoadPath.length > 0) {
			url = url.replace('/ueditorupload/read', noDownLoadPath);
		}
		read(url);
	});

	function read(url) {
		
		if(checkAttachIframeOpen(url)){
		    return;
		}
		
		var formId = "virtualReadFormId";
		if (typeof url == "undefined") {
			url = "";
		}
		var form = $('#' + formId);

		if (form.length > 0) {
			form.remove();
		}
		form = $("<form/>").attr("id", formId).attr("action", url).attr("method",
			"POST").attr("target", "_blank");
		form.appendTo($("body"));
		form.submit().remove();
	}
});