var viewMarkLock = 0;
function viewMark(obj) {
	var questionId = $(obj).attr("data1");
	var recordId = $(obj).attr("data2");
	var markObj = $("#qb" + questionId);
	var creatorId = $("#creatorId").val();
	var workId = $("#workId").val();
	var classId = $("#classId").val();
	var courseId = $("#courseId").val();
	
	var nameData = [];
	// 拿到所有附件
	var objectId = "";
	$(markObj).find(".attach a").each(function(index, element) {
		var name = $(this).text();
		var oid = $(this).attr("data");
		if (undefined == oid) {
			var url = $(this).attr("href");
			if (undefined != url && url.search("objectId") > -1) {
				oid = url.substr(url.search("objectId") + 9);
			} else {
				oid = "";
			}
		}
		if (undefined == oid || oid.length == 0) {
			return true;
		}
		oid = oid.split("&")[0];
		objectId += (oid + ",");
		
		var item = {};
		item.objectId = oid;
		item.name = name;
		nameData.push(item);
	});

	$(markObj).find(".attachNew").each(function(index, element) {
		var markObj = $(this).children("span:first");
		if (undefined == markObj) {
			return true;
		}
		var name = $(markObj).attr("name");
		var objStr = $(markObj).attr("data");
		if (undefined == objStr || objStr.length == 0) {
			return true;
		}
		var oid = objStr.split("&")[0];
		objectId += (oid + ",");
		
		var item = {};
		item.objectId = oid;
		item.name = name;
		nameData.push(item);
	});
	
	$(markObj).find("img:not(.workAttach img, .attach img, .attachNew img)").each(function() {
		var url = $(this).attr("src");
		var oid = "";
		if(typeof url != "undefined" && url.length > 0) {
			var spt = url.split("/");
			var str = spt[spt.length - 1];
			if (str.indexOf(".") == -1) {
				oid = str;
			} else {
				var s = str.split(".");
				oid = s[0];
			}
		}
		objectId += (oid + ",");
	});

	$(markObj).find(".attach-iframe").each(function(index, element) {
		var oid = $(this).attr("objectid");
		var name = $(this).attr("filename");
		objectId += (oid + ",");

		var item = {};
		item.objectId = oid;
		item.name = name;
		nameData.push(item);
	});

	if (objectId.length == 0) {
		alert("请稍后重试");
		return;
	}
	
	if (viewMarkLock == 1) {
		return;
	}
	viewMarkLock = 1;
	
	$.ajax({
		url : "/work/check-attach",
		type : "get",
		data : {
			"courseId" : courseId,
			"classId" : classId,
			"workId" : workId,
			"objectId" : objectId,
			"questionId" : questionId,
			"recordId" : recordId,
			"fullScore" : 0,
			"score" : 0,
			"stuPersonId" : creatorId,
			"teacherPersonId" : creatorId
		},
		async : false,
		dataType : "json",
		success : function(data) {
			if (data.status) {
				var url = data.url + "&nameData=" + encodeURIComponent(JSON.stringify(nameData));
				window.open(url);
				//window.open(url, "newwindow", "height=" + screen.availHeight + ",width=" + screen.availWidth + ",top=0,left=0,toolbar=no,menubar=no,scrollbars=yes,resizable=no,location=no,status=no");
			} else {
				alert("请稍后重试");
			}
		},
		complete: function() {
			viewMarkLock = 0;
		}
	});
}