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
                	ipprefix: document.networkform.Feld9.value,
                	lowpanprefix: document.networkform.Feld10.value,
                	panid: document.networkform.Feld11.value,
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
                		document.networkform.Feld9.value = data.ipprefix ;
                		document.networkform.Feld10.value = data.lowpanprefix ;
                		document.networkform.Feld11.value = data.panid ;


                		document.deviceform.Feld1.value = data.relname1 ;
                		document.deviceform.Feld2.value = data.relname2 ;
                		document.deviceform.Feld3.value = data.relname3 ;
                		document.deviceform.Feld4.value = data.relname4 ;

			});
		};
	});
}
