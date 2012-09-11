{
 	$('#home').live('pageinit', function(event) {
		console.log('pageinit triggered.');
      		//alert("This happens");
		//Assign default value to form field #1
                $.ajaxSetup({ cache: false });
		var reload = setInterval(getenv,20000);
		getenv();

		// an anchor element gets clicked
		$('#radio1-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'A',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio1-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'A',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

		$('#radio2-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'B',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio2-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'B',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

		$('#radio3-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'C',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio3-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'C',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

		$('#radio4-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'D',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);

                        reload = setInterval(getenv,20000); 
		});
		$('#radio4-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'D',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

		$('#radio5-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'E',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio5-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'E',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio6-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'F',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

		$('#radio6-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'F',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

		$('#radio7-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'G',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio7-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'G',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio8-choice-1').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'H',
					'Value': myswitch.filter(':checked').val() == "on" ? "true":"true"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});
		$('#radio8-choice-2').change(function() {
                        clearInterval(reload);
    			var myswitch = $(this);
 			$.post('/cgi-bin/dodev.cgi', 
				{ 
					'Feld' : 'H',
					'Value': myswitch.filter(':checked').val() == "on" ? "false":"false"
				}, parseInfo);
                        reload = setInterval(getenv,20000); 
		});

  	});

	function getenv(){
		//Assign default value to form field #1
		//Assign default value to form field #1

                $.getJSON('/cgi-bin/uenv.cgi',
			function(data){
			$('#radio1-choice-1').attr("checked",(data.relay1 == 1)).checkboxradio("refresh");
			$('#radio1-choice-2').attr("checked",(data.relay1 == 0)).checkboxradio("refresh");

			$('#radio2-choice-1').attr("checked",(data.relay2 == 1)).checkboxradio("refresh");
			$('#radio2-choice-2').attr("checked",(data.relay2 == 0)).checkboxradio("refresh");

			$('#radio3-choice-1').attr("checked",(data.relay3 == 1)).checkboxradio("refresh");
			$('#radio3-choice-2').attr("checked",(data.relay3 == 0)).checkboxradio("refresh");

			$('#radio4-choice-1').attr("checked",(data.relay4 == 1)).checkboxradio("refresh");
			$('#radio4-choice-2').attr("checked",(data.relay4 == 0)).checkboxradio("refresh");

			$('#radio5-choice-1').attr("checked",(data.relay5 == 1)).checkboxradio("refresh");
			$('#radio5-choice-2').attr("checked",(data.relay5 == 0)).checkboxradio("refresh");

			$('#radio6-choice-1').attr("checked",(data.relay6 == 1)).checkboxradio("refresh");
			$('#radio6-choice-2').attr("checked",(data.relay6 == 0)).checkboxradio("refresh");

			$('#radio7-choice-1').attr("checked",(data.relay7 == 1)).checkboxradio("refresh");
			$('#radio7-choice-2').attr("checked",(data.relay7 == 0)).checkboxradio("refresh");

			$('#radio8-choice-1').attr("checked",(data.relay8 == 1)).checkboxradio("refresh");
			$('#radio8-choice-2').attr("checked",(data.relay8 == 0)).checkboxradio("refresh");

			$('#stext1').text(data.relname1);
			$('#stext2').text(data.relname2);
			$('#stext3').text(data.relname3);
			$('#stext4').text(data.relname4);
			$('#stext5').text(data.relname5);
			$('#stext6').text(data.relname6);
			$('#stext7').text(data.relname7);
			$('#stext8').text(data.relname8);
		});
	};
	// this function parses the fetched data into the 'info' paragraph
	function parseInfo(data)
	{
		// the data parameter is an object, while name and email are the keys from the PHP array
		// you can also use the 'text' function instead of html. The difference is that 'text'
		// displays raw text, even if it contains other HTML elements.
		//$('#info').html(data);
	};
}
