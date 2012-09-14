{
	$('document').ready(function() 
	{ 
		//Assign default value to form field #1
		getenv();

	        $("button:first").click(function(){
	          $.post('/cgi-bin/option.cgi',  
	            { 
                	ipaddr: document.networkform.Feld1.value,
                	gatewayip: document.networkform.Feld2.value,
                	netmask: document.networkform.Feld3.value,
                	dhcp: document.networkform.Feld4.checked,
                	dnsip: document.networkform.Feld5.value,
                	dnsip2: document.networkform.Feld6.value,
                	serverip: document.networkform.Feld7.value,
                	hostname: document.networkform.Feld8.value,
	            }, 
	            function(data){
	             //$("#ausgabe").html(data);
			alert("I am rebooting ...");
	            });
	        });
        	$("button:eq(1)").click(function(){
			getenv();
	        });
	        $("button:eq(2)").click(function(){
	          $.post('/cgi-bin/device.cgi',  
	            { 
                	relname1: document.deviceform.Feld1.value,
                	relname2: document.deviceform.Feld2.value,
                	relname3: document.deviceform.Feld3.value,
                	relname4: document.deviceform.Feld4.value,
                	relname5: document.deviceform.Feld5.value,
                	relname6: document.deviceform.Feld6.value,
                	relname7: document.deviceform.Feld7.value,
                	relname8: document.deviceform.Feld8.value,

	            }, 
	            function(data){
	             //$("#ausgabe").html(data);
	            });
	        });

        	$("button:last").click(function(){
			getenv();
	        });
		function getenv(){
			//Assign default value to form field #1
                	$.getJSON('/cgi-bin/uenv.cgi',
				function(data){
                		document.networkform.Feld8.value = data.hostname ;
                		document.networkform.Feld1.value = data.ipaddr ;
                		document.networkform.Feld2.value = data.gatewayip ;
                		document.networkform.Feld3.value = data.netmask ;
                		document.networkform.Feld4.checked = (data.dhcp == 'on') ;
                		document.networkform.Feld5.value = data.dnsip ;
                		document.networkform.Feld6.value = data.dnsip2 ;
                		document.networkform.Feld7.value = data.serverip ;

                		document.deviceform.Feld1.value = data.relname1 ;
                		document.deviceform.Feld2.value = data.relname2 ;
                		document.deviceform.Feld3.value = data.relname3 ;
                		document.deviceform.Feld4.value = data.relname4 ;
				document.deviceform.Feld5.value = data.relname5 ;
                		document.deviceform.Feld6.value = data.relname6 ;
                		document.deviceform.Feld7.value = data.relname7 ;
                		document.deviceform.Feld8.value = data.relname8 ;

			});
		};
	});
	function parseInfo(data)
	{
		// the data parameter is an object, while name and email are the keys from the PHP array
		// you can also use the 'text' function instead of html. The difference is that 'text'
		// displays raw text, even if it contains other HTML elements.
		//$('#info').html(data);
	};
}
